/**
 *    @file:        async_runnable_msg_callback_interface.h
 *    @author:      tiankk <tiankk@gmail.com>
 *    @created:     2014/02/13
 *    @brief:       Callback class supporting windows message loop.
 */

#ifndef __ASYNC_RUNNABLE_MSG_CALLBACK_INTERFACE_H__
#define __ASYNC_RUNNABLE_MSG_CALLBACK_INTERFACE_H__

#include "return_value_type.h"
#include "async_runnable_callback_base.h"
#include "msg_receiver_interface.h"
#include "thread_pool.h"
#include <map>


namespace tthread
{
    /**
     *    @biref:   The thread which the instance of this class created in,
     *              is the one which callback function will be run in.
     */
    class IAsyncRunnableMsgCallback : public IAsyncRunnableCallbackBase
                                    , public utility::IMsgReceiver
    {
    public:
        IAsyncRunnableMsgCallback()
        : hwnd_notifier_(NULL)
        , response_msg_(0)
        {
            utility::ThreadPool::RegisterMsgReceiver(this, hwnd_notifier_, response_msg_);
        };
        virtual ~IAsyncRunnableMsgCallback()
        {
            utility::ThreadPool::UnRegisterMsgReceiver(this);
        };

        void OnMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
        {
            UNREFERENCED_PARAMETER(lParam);
            UNREFERENCED_PARAMETER(uMsg);
            ScopedRefPtr<ReturnValue> ret((ReturnValue*)wParam);
            DispatchTask(ret);
        }

        void GetCallBackHwndAndMsg(HWND& hwndNotifier, UINT& uMsg)
        {
            hwndNotifier = hwnd_notifier_;
            uMsg = response_msg_;
        }

    private:
        HWND hwnd_notifier_;
        UINT response_msg_;
    };
}

#endif // __ASYNC_RUNNABLE_MSG_CALLBACK_INTERFACE_H__
