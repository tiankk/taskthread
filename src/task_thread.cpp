#include "task_thread.h"
#include "scoped_ptr.h"
#include <process.h>
#include <cassert>

#ifdef _DETECT_MEM_LEAK
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
static struct Dbg_Mem_Leak_Check
{
    Dbg_Mem_Leak_Check()
    {
        _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
    }
} s_Dbg_Mem_Leak_Check;
#endif
#endif  // _DETECT_MEM_LEAK


/// thread name in vc++ threads debug window
/// http://msdn.microsoft.com/en-us/library/xcb2z8hs.aspx
const DWORD MS_VC_EXCEPTION=0x406D1388;

#pragma pack(push,8)
typedef struct tagTHREADNAME_INFO
{
    DWORD dwType;       // Must be 0x1000.
    LPCSTR szName;      // Pointer to name (in user addr space).
    DWORD dwThreadID;   // Thread ID (-1=caller thread).
    DWORD dwFlags;      // Reserved for future use, must be zero.
} THREADNAME_INFO;
#pragma pack(pop)

namespace tthread
{
    namespace utility
    {
        TaskThread::TaskThread(bool run_once/* = false*/, const std::string& debug_name/* = "taskthread"*/)
            : iocp_normal_(0)
            , iocp_emergency_(0)
            , run_once_(run_once)
            , quit_msg_in_queue_(false)
            , emergency_quit_msg_in_queue_(false)
            , cleaning_(false)
            , thread_id_(0)
            , handle_(0)
            , is_ready_to_run_(true)
            , debug_name_(debug_name)
        {
            Start();
        };

        TaskThread::~TaskThread()
        {
            Quit();
            Wait();
        };

        void TaskThread::SetThreadName()
        {
            if (handle_ == 0 || debug_name_.empty())
            {
                return;
            }

            THREADNAME_INFO info;
            info.dwType = 0x1000;
            info.szName = debug_name_.c_str();
            info.dwThreadID = thread_id_;
            info.dwFlags = 0;

            __try
            {
                RaiseException( MS_VC_EXCEPTION, 0, sizeof(info)/sizeof(ULONG_PTR), (ULONG_PTR*)&info );
            }
            __except(EXCEPTION_EXECUTE_HANDLER)
            {
            }
        }

        //////////////////////////////////////////////////////////////////////////
        bool TaskThread::Start()
        {
            assert(handle_ == 0);
            handle_ = (HANDLE)::_beginthreadex(NULL, 0, threadProc, this, 0, &thread_id_);
            SetThreadName();
            return handle_ != 0;
        }

        bool TaskThread::Wait(unsigned int msec)
        {
            if (handle_)
            {
                int ret = ::WaitForSingleObject(handle_, msec);
                if (ret == WAIT_OBJECT_0)
                {
                    ::CloseHandle(handle_);
                    handle_ = 0;
                    return true;
                }
                return false;
            }
            return false;
        }

        void TaskThread::Terminate()
        {
            if (handle_)
            {
                ::TerminateThread(handle_, NULL);
                CloseHandle(handle_);
                handle_ = 0;
            }
        }

        unsigned int TaskThread::GetThreadID() const
        {
            return thread_id_;
        }

        HANDLE TaskThread::GetHandle() const
        {
            return handle_;
        }

        unsigned int TaskThread::threadProc(void* arg)
        {
            assert(arg);
            TaskThread* pThis = (TaskThread*)arg;
            return pThis->run();
        }

        unsigned int TaskThread::run()
        {
            quit_msg_in_queue_ = false;
            emergency_quit_msg_in_queue_ = false;
            for (;;)
            {
                // run task in emergency queue
                EXIT_CODE ex = DoEergencyWork();
                if (EX_RUN_SUCC == ex)
                {
                    continue;
                }
                else if (EX_RUN_FAIL == ex || EX_ERR == ex)
                {// failed, thread quit
                    break;
                }
                else if (EX_TASK_QUEUE_EMPTY == ex)
                {// queue is empty
                    // go to do normal work
                }

                // run task in normal queue
                ex = DoNormalWork();
                if (EX_RUN_SUCC == ex)
                {
                    continue;
                }
                else if (EX_RUN_FAIL == ex || EX_ERR == ex)
                {// failed, thread quit
                    break;
                }
            }
            return 0;
        }

        //////////////////////////////////////////////////////////////////////////

        void TaskThread::PostTask(const Closure& task)
        {
            if (quit_msg_in_queue_ || emergency_quit_msg_in_queue_)
            {// there is quit message in queue, do not accept new tasks.
                return;
            }
            if (run_once_)
            {// this is one runonce thread, does not accept new tasks
                is_ready_to_run_ = false;
            }
            Closure* pt = new Closure(task);
            iocp_normal_.PostStatus(TASK, 0, (OVERLAPPED*)pt);
        }

        void TaskThread::PostEmergencyTask(const Closure& task)
        {
            if (quit_msg_in_queue_ || emergency_quit_msg_in_queue_)
            {// there is quit message in queue, do not accept new tasks.
                return;
            }
            if (run_once_)
            {// this is one runonce thread, does not accept new tasks
                is_ready_to_run_ = false;
            }
            Closure* pt = new Closure(task);
            iocp_emergency_.PostStatus(TASK, 0, (OVERLAPPED*)pt);
            WakeUp();
        }

        void TaskThread::Quit()
        {
            if (quit_msg_in_queue_ || emergency_quit_msg_in_queue_)
            {// there is quit message in queue, do not accept new tasks.
                return;
            }
            if (run_once_)
            {// this is one runonce thread, does not accept new tasks
                is_ready_to_run_ = false;
            }
            iocp_normal_.PostStatus(QUIT, 0, 0);
            quit_msg_in_queue_ = true;
        }

        void TaskThread::EmergencyQuit()
        {
            if (emergency_quit_msg_in_queue_)
            {// there is quit message in emergency queue, do not accept new emergency tasks.
                return;
            }
            Quit();
            iocp_emergency_.PostStatus(QUIT, 0, 0);
            emergency_quit_msg_in_queue_ = true;
        }

        void TaskThread::WakeUp()
        {// wake up thread which was blocked on normal queue
            iocp_normal_.PostStatus(WAKE_UP, 0, 0);
        }

        bool TaskThread::Err(OVERLAPPED* o)
        {// check error code, if queue is empty, return true, otherwise false.
            DWORD dwError = GetLastError();
            if (o != NULL)
            {
                return false;
            }
            else
            {
                if (dwError == WAIT_TIMEOUT)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            return false;
        }

        TaskThread::EXIT_CODE TaskThread::DoEergencyWork()
        {
            if (cleaning_)
            {// waiting for cleaning tasks in normal queue
                return EX_TASK_QUEUE_EMPTY;
            }
            ULONG_PTR CompletionKey;
            DWORD dwNumBytes;
            OVERLAPPED* po = NULL;
            /// get iocp state without blocking thread
            BOOL ret_ok = iocp_emergency_.GetStatus(&CompletionKey, &dwNumBytes, (OVERLAPPED**) &po, 0);
            if (ret_ok)
            {
                if (QUIT == CompletionKey)
                {// received quit message, begin to clean tasks
                    cleaning_ = true;
                    return EX_TASK_QUEUE_EMPTY;
                }
                if (DoWork(CompletionKey, po))
                {
                    return EX_RUN_SUCC;
                }
                else
                {
                    return EX_RUN_FAIL;
                }
            }
            else
            {
                if (Err(po))
                {// queue is empty
                    return EX_TASK_QUEUE_EMPTY;
                }
                else
                {
                    return EX_ERR;
                }
            }
        }

        TaskThread::EXIT_CODE TaskThread::DoNormalWork()
        {
            ULONG_PTR CompletionKey;
            DWORD dwNumBytes;
            OVERLAPPED* po = NULL;
            /// get iocp state
            /// if task queue is empty, thread will be blocked here until new task is coming.
            BOOL ret_ok = iocp_normal_.GetStatus(&CompletionKey, &dwNumBytes, (OVERLAPPED**) &po);
            if (ret_ok)
            {
                if (cleaning_)
                {/// clean tasks
                    switch(CompletionKey)
                    {
                    case QUIT:
                        break;
                    case TASK:
                        {/// recycle memory
                            ScopedPtr<Closure> p(static_cast<Closure*>((void*)po));
                        }
                    case WAKE_UP:
                    default:
                        return EX_RUN_SUCC;
                    }
                }
                if (DoWork(CompletionKey, po))
                {
                    return EX_RUN_SUCC;
                }
                else
                {
                    return EX_RUN_FAIL;
                }
            }
            else
            {
                Err(po);
                return EX_ERR;
            }
        }

        bool TaskThread::DoWork(ULONG_PTR CompletionKey, OVERLAPPED* o)
        {
            switch (CompletionKey)
            {
            case QUIT:
                {
                    return false;
                }
                break;
            case TASK:
                {
                    ScopedPtr<Closure> p(static_cast<Closure*>((void*)o));
                    p->Run();

                    if (run_once_)
                    {/// from now on, runonce thread can accept next task.
                        is_ready_to_run_ = true;
                    }
                }
                break;
            case WAKE_UP:
                // nothing to do, just get up
            default:
                break;
            }

            return true;
        }

        bool TaskThread::IsReadyToRun()
        {/// whether thread can accept next task
            if (!run_once_)
            {
                return TRUE;
            }

            return is_ready_to_run_;
        }
    } // namespace utility
} // namespace tthread
