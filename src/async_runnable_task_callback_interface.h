/**
 *    @file:        async_runnable_task_callback_interface.h
 *    @author:      tiankk <tiankk@gmail.com>
 *    @created:     2014/02/13
 *    @brief:       Callback class supporting iocp task queue.
 */

#ifndef __ASYNC_RUNNABLE_TASK_CALLBACK_INTERFACE_H__
#define __ASYNC_RUNNABLE_TASK_CALLBACK_INTERFACE_H__

#include "return_value_type.h"
#include "async_runnable_callback_base.h"
#include <map>


namespace tthread
{
    class IAsyncRunnableTaskCallback : public RefCountedThreadSafe<IAsyncRunnableTaskCallback>
                                     , public IAsyncRunnableCallbackBase
    {
    public:
        virtual ~IAsyncRunnableTaskCallback(){};

        void OnComplete(ScopedRefPtr<ReturnValue> ret)
        {
            DispatchTask(ret);
        }
    };
} // namespace tthread

#endif // __ASYNC_RUNNABLE_TASK_CALLBACK_INTERFACE_H__
