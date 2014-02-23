#include "runonce_thread_pool.h"
#include <sstream>
#include <string>

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


namespace tthread
{
    namespace utility
    {
        RunOnceThreadPool::~RunOnceThreadPool()
        {
            WaitAll();
            ClearAll();
        }

        void RunOnceThreadPool::ClearAll()
        {
            // clean all TaskThread objects
            lst_.clear();
        }

        void RunOnceThreadPool::WaitAll(unsigned int msec/* = INFINITE*/)
        {
            std::list< ScopedRefPtr<TaskThread> >::iterator it = lst_.begin();
            for (;it != lst_.end(); it++)
            {
                (*it)->Quit();
                (*it)->Wait(msec); // waiting for all the RUNONCE threads quitting
            }
        }

        ScopedRefPtr<TaskThread> RunOnceThreadPool::GetThread()
        {
            AutoLockGuard lg(lock_); // ***********************lock***********************
            std::list< ScopedRefPtr<TaskThread> >::iterator it = lst_.begin();
            for (;it != lst_.end(); it++)
            {
                if ((*it)->IsReadyToRun())
                {
                    return *it;
                }
            }
            std::stringstream strm;
            strm << lst_.size();
            std::string str_id;
            strm >> str_id;
            std::string str_thread_name("runonce_taskthread_");
            str_thread_name += str_id;
            ScopedRefPtr<TaskThread> th = new TaskThread(true, str_thread_name);
            lst_.push_back(th);
            return th;
        }
    } // namespace utility
} // namespace tthread
