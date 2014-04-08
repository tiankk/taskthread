/**
 *    @file:        async_task_runnable.h
 *    @author:      tiankk <tiankk@gmail.com>
 *    @created:     2014/02/13
 */

#ifndef __ASYNC_TASK_RUNNABLE_H__
#define __ASYNC_TASK_RUNNABLE_H__

#include "thread_pool.h"
#include "runnable_base.h"
#include "cancellable_runnable.h"
#include "async_runnable_task_callback_interface.h"
#include "async_runnable_msg_callback_interface.h"

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
         *    @brief:  task with callback
         */
        template <typename ReturnValueType>
        class AsyncTaskRunnable : public RunnableBase
                                , public RefCountedThreadSafe<AsyncTaskRunnable<ReturnValueType>>
        {
        public:
            AsyncTaskRunnable(  const tstring & identifier,
                                Callback<void(ReturnValueType*)> func,
                                THREAD_ID run_thread_id,
                                IAsyncRunnableCallbackBase* callback,
                                THREAD_ID response_thread_id = DEFAULT,
                                bool emergency_run = false,
                                bool emergency_response = false)
                : task_callback_(NULL)
                , msg_callback_(NULL)
                , ret_(NULL)
                , func_(func)
                , run_thread_(ThreadPool::GetThread(run_thread_id))
                , response_thread_(ThreadPool::GetThread(response_thread_id))
                , notifier_handle_(0)
                , response_message_(0)
                , identifier_(identifier)
                , emergency_run_(emergency_run)
                , emergency_response_(emergency_response)
                , cancellable_(new CancellableRunnable)
            {
                if (callback)
                {
                    IAsyncRunnableMsgCallback* p_msg_evt = dynamic_cast<IAsyncRunnableMsgCallback*>(callback);
                    if (p_msg_evt)
                    {
                        msg_callback_ = p_msg_evt;
                        msg_callback_->GetCallBackHwndAndMsg(notifier_handle_, response_message_);
                    }
                    else
                    {
                        IAsyncRunnableTaskCallback* p_task_evt = dynamic_cast<IAsyncRunnableTaskCallback*>(callback);
                        if (p_task_evt)
                        {
                            task_callback_ = p_task_evt;
                        }
                    }
                    callback->InsertCallPair(id_, identifier_);
                }
            }

            /**
             *    @brief:        run task, called by tthread::TaskThread
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

                ret_ = new ReturnValueType;
                ret_->id_ = id_;
                func_.Run(ret_);
                if (notifier_handle_ && response_message_)
                {
                    ::PostMessage(notifier_handle_, response_message_, (WPARAM)(void*)ret_, g_Magic_Identifer);
                }
                else if (task_callback_)
                {
                    ScopedRefPtr<ReturnValueType> p(ret_);
                    if (response_thread_)
                    {
                        if (emergency_response_)
                        {
                            response_thread_->PostEmergencyTask(Bind(&IAsyncRunnableTaskCallback::OnComplete, task_callback_, p));
                        }
                        else
                        {
                            response_thread_->PostTask(Bind(&IAsyncRunnableTaskCallback::OnComplete, task_callback_, p));
                        }
                    }
                }
                else
                {/// recycle return value
                    ScopedRefPtr<ReturnValueType> p(ret_);
                }
            }

            /**
             *    @brief:        commit task
             *    @method:       Run
             *    @return:       void
             */
            virtual void Run()
            {
                if (!run_thread_)
                {
                    return;
                }
                if (emergency_run_)
                {
                    run_thread_->PostEmergencyTask(Bind(&AsyncTaskRunnable<ReturnValueType>::__Do, this));
                }
                else
                {
                    run_thread_->PostTask(Bind(&AsyncTaskRunnable<ReturnValueType>::__Do, this));
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
            /// window handle receives callback messages
            HWND notifier_handle_;

            /// window message used for triggering callback function
            UINT response_message_;

            /// smart pointer of callback object supporting iocp task queue
            /// recycle automatically
            ScopedRefPtr<IAsyncRunnableTaskCallback> task_callback_;

            /// pointer of callback object supporting windows-message-loop
            /// do not recycle
            IAsyncRunnableMsgCallback* msg_callback_;

            /// return value pointer
            ReturnValueType* ret_;

            /// pointer of run thread object
            IThreadTask* run_thread_;

            /// pointer of response thread object
            IThreadTask* response_thread_;

            /// task
            Callback<void(ReturnValueType*)> func_;

            /// logic identifier
            const tstring identifier_;

            /// whether commit task to emergency queue
            bool emergency_run_;

            /// whether commit callback-task to the emergency queue(effect only callback object is IAsyncRunnableTaskCallback)
            bool emergency_response_;

            /// object used for cancelling task
            ScopedRefPtr<CancellableRunnable> cancellable_;
        };
    } // namespace utility
} // namespace tthread

#endif // __ASYNC_TASK_RUNNABLE_H__
