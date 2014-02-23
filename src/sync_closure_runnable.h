/**
 *    @file:        sync_closure_runnable.h
 *    @author:      tiankk <tiankk@gmail.com>
 *    @created:     2014/02/13
 */

#ifndef __SYNC_CLOSURE_RUNNABLE_H__
#define __SYNC_CLOSURE_RUNNABLE_H__

#include "thread_pool.h"
#include "runnable_base.h"

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
        /**
         *    @brief:  synchronous task without return value
         */
        class SyncClosureRunnable : public RunnableBase
                                  , public RefCountedThreadSafe<SyncClosureRunnable>
        {
        public:
            SyncClosureRunnable(Closure func,
                                THREAD_ID run_thread_id,
                                bool emergency_run = false)
                : response_event_handle_(INVALID_HANDLE_VALUE)
                , closure_(func)
                , run_thread_(ThreadPool::GetThread(run_thread_id))
                , emergency_run_(emergency_run)
            {}

            virtual void __Do()
            {
                closure_.Run();
                if (INVALID_HANDLE_VALUE != response_event_handle_)
                {
                    SetEvent(response_event_handle_);
                }
            }

            virtual void Run()
            {
                if (!run_thread_)
                {
                    return;
                }
                response_event_handle_ = CreateEvent(NULL, FALSE, FALSE, NULL);
                if (INVALID_HANDLE_VALUE == response_event_handle_)
                {
                    return;
                }
                if (emergency_run_)
                {
                    run_thread_->PostEmergencyTask(Bind(&SyncClosureRunnable::__Do, this));
                }
                else
                {
                    run_thread_->PostTask(Bind(&SyncClosureRunnable::__Do, this));
                }
                WaitForSingleObject(response_event_handle_, INFINITE);
                CloseHandle(response_event_handle_);
                response_event_handle_ = INVALID_HANDLE_VALUE;
            }

        private:
            TaskThread* run_thread_;
            HANDLE response_event_handle_;
            Closure closure_;
            bool emergency_run_;
        };
    } // namespace utility
} // namespace tthread

#endif // __SYNC_CLOSURE_RUNNABLE_H__
