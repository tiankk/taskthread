#include "task_thread_export.h"
#include "thread_pool.h"
#include "async_closure_runnable.h"
#include "sync_closure_runnable.h"

namespace tthread
{
    void AsyncTask( utility::Closure task,
                    THREAD_ID run_thread_id,
                    bool emergency_run/* = false*/,
                    CancellableRunnableReference * cancellable_ref/* = NULL*/)
    {
        ScopedRefPtr<utility::AsyncClosureRunnable> pRunnable(new utility::AsyncClosureRunnable(task, run_thread_id, emergency_run));
        if (cancellable_ref != NULL)
        {
            *cancellable_ref = pRunnable->CreateCancellableRunnableReference();
        }
        pRunnable->Run();
    }

    void AsyncMessage(  const tstring & identifier,
                        ReturnValue* ret,
                        IAsyncRunnableCallbackBase* callback,
                        THREAD_ID response_thread_id/* = DEFAULT*/,
                        bool emergency_response/* = false*/)
    {
        ScopedRefPtr<utility::MessageSenderRunnable> pRunnable(new utility::MessageSenderRunnable(identifier, ret, callback, response_thread_id, emergency_response));
        pRunnable->Run();
    }

    void SyncTask(  utility::Closure task,
                    THREAD_ID run_thread_id,
                    bool emergency_run/* = false*/)
    {
        ScopedRefPtr<utility::SyncClosureRunnable> pRunnable(new utility::SyncClosureRunnable(task, run_thread_id, emergency_run));
        pRunnable->Run();
    }

    void SafeQuit()
    {
        utility::ThreadPool::QuitStaticThread();
        utility::ThreadPool::WaitAll();
    }

    void SafeEmergencyQuit()
    {
        utility::ThreadPool::EmergencyQuitStaticThread();
        utility::ThreadPool::WaitAll();
    }
} // namespace tthread
