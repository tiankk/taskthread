/**
 *    @file:        message_sender_runnable.h
 *    @author:      tiankk <tiankk@gmail.com>
 *    @created:     2014/02/13
 */

#ifndef __MESSAGE_SENDER_RUNNABLE_H__
#define __MESSAGE_SENDER_RUNNABLE_H__

#include "thread_pool.h"
#include "runnable_base.h"
#include "async_runnable_task_callback_interface.h"
#include "async_runnable_msg_callback_interface.h"


namespace tthread
{
    namespace utility
    {
        /**
         *    @brief:  asynchronous message
         */
        class MessageSenderRunnable : public RunnableBase
                                    , public RefCountedThreadSafe<MessageSenderRunnable >
        {
        public:
            MessageSenderRunnable(  const tstring & identifier,
                                    ReturnValue* ret,
                                    IAsyncRunnableCallbackBase* callback,
                                    THREAD_ID response_thread_id = DEFAULT,
                                    bool emergency_response = false)
                : task_callback_(NULL)
                , msg_callback_(NULL)
                , ret_(ret)
                , response_thread_(ThreadPool::GetThread(response_thread_id))
                , notifier_handle_(0)
                , response_message_(0)
                , identifier_(identifier)
                , emergency_response_(emergency_response)
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
                        IAsyncRunnableTaskCallback* p£ßtask_evt = dynamic_cast<IAsyncRunnableTaskCallback*>(callback);
                        if (p£ßtask_evt)
                        {
                            task_callback_ = p£ßtask_evt;
                        }
                    }
                    callback->InsertCallPair(id_, identifier_);
                }
            }

            virtual void __Do(){}

            virtual void Run()
            {
                ret_->id_ = id_;
                if (notifier_handle_ && response_message_)
                {
                    ::PostMessage(notifier_handle_, response_message_, (WPARAM)(void*)ret_, g_Magic_Identifer);
                }
                else if (task_callback_)
                {
                    ScopedRefPtr<ReturnValue> p(ret_);
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
                    ScopedRefPtr<ReturnValue> p(ret_);
                }
            }

        private:
            HWND notifier_handle_;
            UINT response_message_;
            ScopedRefPtr<IAsyncRunnableTaskCallback> task_callback_;
            IAsyncRunnableMsgCallback* msg_callback_;
            ReturnValue* ret_;
            IThreadTask* response_thread_;
            const tstring identifier_;
            bool emergency_response_;
        };
    } // namespace utility
} // namespace tthread

#endif // __MESSAGE_SENDER_RUNNABLE_H__
