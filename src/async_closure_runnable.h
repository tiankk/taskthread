/**
 *    @file:        async_closure_runnable.h
 *    @author:      tiankk <tiankk@gmail.com>
 *    @created:     2014/02/13
 */

#ifndef __ASYNC_CLOSURE_RUNNABLE_H__
#define __ASYNC_CLOSURE_RUNNABLE_H__

#include "thread_pool.h"
#include "runnable_base.h"
#include "cancellable_runnable.h"

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
         *    @brief:  task without callback
         */
        class AsyncClosureRunnable : public RunnableBase
                                   , public RefCountedThreadSafe<AsyncClosureRunnable >
        {
        public:
            AsyncClosureRunnable(   Closure func,
                                    THREAD_ID run_thread_id,
                                    bool emergency_run = false)
                : run_thread_(ThreadPool::GetThread(run_thread_id))
                , closure_(func)
                , emergency_run_(emergency_run)
                , cancellable_(new CancellableRunnable)
            {}

            /**
             *    @brief:        Run task, called by tthread::TaskThread.
             *    @method:       __Do
             *    @return:       void
             */
            virtual void __Do()
            {
                if (cancellable_.get() && cancellable_->IsCanceled())
                {
                    return;
                }
                cancellable_->DisableCancellable();
                closure_.Run();
            }

            /**
             *    @brief:        Commit task.
             *    @method:       Run
             *    @return:       void
             */
            virtual void Run()
            {
                if (run_thread_)
                {
                    if (emergency_run_)
                    {
                        run_thread_->PostEmergencyTask(Bind(&AsyncClosureRunnable::__Do, this));
                    }
                    else
                    {
                        run_thread_->PostTask(Bind(&AsyncClosureRunnable::__Do, this));
                    }
                }
            }

            /**
             *    @brief:        Get reference object used for cancelling task.
             *    @method:       CreateCancellableRunnableReference
             *    @return:       CancellableRunnableReference
             */
            CancellableRunnableReference CreateCancellableRunnableReference()
            {
                if (cancellable_.get())
                {
                    return cancellable_->CreateReference();
                }
                return CancellableRunnableReference();
            }

        private:
            TaskThread* run_thread_;
            Closure closure_;
            long id_;
            bool emergency_run_;
            ScopedRefPtr<CancellableRunnable> cancellable_;
        };
    } // namespace utility
} // namespace tthread

#endif // __ASYNC_CLOSURE_RUNNABLE_H__
