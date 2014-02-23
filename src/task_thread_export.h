/**
 *    @file:        task_thread_export.h
 *    @author:      tiankk <tiankk@gmail.com>
 *    @created:     2014/02/13
 *    @brief:       taskthread interfaces
 */

#ifndef __TASK_THREAD_EXPORT_H__
#define __TASK_THREAD_EXPORT_H__

#include "bind.h"
#include "const_define.h"
#include "async_task_runnable.h"
#include "sync_task_runnable.h"
#include "message_sender_runnable.h"
#include "cancellable_runnable_reference.h"


namespace tthread
{
    /**
     *    @brief:        Commit one asynchronous task without callback.
     *    @method:       AsyncTask
     *    @param:        utility::Closure task          void(void) task built by ttrhead::Bind()
     *    @param:        THREAD_ID run_thread_id        id of thread running the task
     *    @param:        bool emergency_run             whether commit task to the emergency queue
     *    @param:        CancellableRunnableReference * cancellable_ref     object used for cancelling task
     *    @return:       void
     */
    void AsyncTask( utility::Closure task,
                    THREAD_ID run_thread_id,
                    bool emergency_run = false,
                    CancellableRunnableReference* cancellable_ref = NULL);

    /**
     *    @brief:        Commit one asynchronous task with callback.
     *    @method:       AsyncTask
     *    @param:        const tstring & identifier                         logic identifier, used in callback function
     *    @param:        utility::Callback<void(ReturnValueType*)> task     void(ReturnValueType*) task built by tthread::Bind()
     *    @param:        THREAD_ID run_thread_id                            id of thread running the task
     *    @param:        IAsyncRunnableCallbackBase * callback              callback object pointer
     *    @param:        THREAD_ID response_thread_id                       id of thread running callback function(effect only callback object is IAsyncRunnableTaskCallback)
     *    @param:        bool emergency_run                                 whether commit task to the emergency queue
     *    @param:        bool emergency_response                            whether commit callback-task to the emergency queue(effect only callback object is IAsyncRunnableTaskCallback)
     *    @param:        CancellableRunnableReference * cancellable_ref     object used for cancelling task
     *    @return:       void
     */
    template <typename ReturnValueType>
    void AsyncTask( const tstring & identifier,
                    utility::Callback<void(ReturnValueType*)> task,
                    THREAD_ID run_thread_id,
                    IAsyncRunnableCallbackBase* callback,
                    THREAD_ID response_thread_id = DEFAULT,
                    bool emergency_run = false,
                    bool emergency_response = false,
                    CancellableRunnableReference* cancellable_ref = NULL)
    {
        ScopedRefPtr<utility::AsyncTaskRunnable<ReturnValueType> > pRunnable(new utility::AsyncTaskRunnable<ReturnValueType>(identifier, task, run_thread_id, callback, \
                                                                                                           response_thread_id, emergency_run, emergency_response));
        if (cancellable_ref != NULL)
        {
            *cancellable_ref = pRunnable->CreateCancellableRunnableReference();
        }
        pRunnable->Run();
    }

    /**
     *    @brief:        Commit one message(tthread::ReturnVlaue object) to callback function.
     *    @method:       AsyncMessage
     *    @param:        const tstring & identifier                 logic identifier decide with logic block will be invoke
     *    @param:        ReturnValue * ret                          message
     *    @param:        IAsyncRunnableCallbackBase * callback      callbak object who receive the messages
     *    @param:        THREAD_ID response_thread_id               id of thread running callback function(effect only callback object is IAsyncRunnableTaskCallback)
     *    @param:        bool emergency_response                    whether commit callback-task to the emergency queue(effect only callback object is IAsyncRunnableTaskCallback)
     *    @return:       void
     */
    void AsyncMessage(  const tstring & identifier,
                        ReturnValue* ret,
                        IAsyncRunnableCallbackBase* callback,
                        THREAD_ID response_thread_id = DEFAULT,
                        bool emergency_response = false);

    /**
     *    @brief:        Commit one synchronous task without return value.
     *    @method:       SyncTask
     *    @param:        utility::Closure task      void(void) task built by ttrhead::Bind()
     *    @param:        THREAD_ID run_thread_id    id of thread running the task
     *    @param:        bool emergency_run         whether commit task to the emergency queue
     *    @return:       void
     */
    void SyncTask(  utility::Closure task,
                    THREAD_ID run_thread_id,
                    bool emergency_run = false);

    /**
     *    @brief:        Commit one synchronous task with return value.
     *    @method:       SyncTask
     *    @param:        utility::Callback<void(ReturnValueType*)> task     void(ReturnValueType*) task built by tthread::Bind()
     *    @param:        THREAD_ID run_thread_id                            id of thread running the task
     *    @param:        bool emergency_run                                 id of thread running the task
     *    @return:       ScopedRefPtr<ReturnValueType>                      return value
     */
    template <typename ReturnValueType>
    ScopedRefPtr<ReturnValueType> SyncTask( utility::Callback<void(ReturnValueType*)> task,
                                            THREAD_ID run_thread_id,
                                            bool emergency_run = false)
    {
        ScopedRefPtr<utility::SyncTaskRunnable<ReturnValueType> > pRunnable(new utility::SyncTaskRunnable<ReturnValueType>(task, run_thread_id, emergency_run));
        pRunnable->Run();
        return pRunnable->GetReturnValue();
    }

    /**
     *    @brief:        Safe quit after all tasks in queue have been run.
     *    @method:       SafeQuit
     *    @return:       void
     */
    void SafeQuit();

    /**
     *    @brief:        Safe quit without running tasks in queue.
     *    @method:       SafeEmergencyQuit
     *    @return:       void
     */
    void SafeEmergencyQuit();
} // namespace tthread

#endif // __TASK_THREAD_EXPORT_H__
