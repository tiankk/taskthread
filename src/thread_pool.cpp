#include "thread_pool.h"


namespace tthread
{
    namespace utility
    {
            TaskThread* ThreadPool::GetThread(THREAD_ID id)
            {
                if (id == RUNONCE)
                {
                    return runonce_pool_->GetThread();
                }
                return static_pool_->GetThread(id);
            }

            TaskThread* ThreadPool::GetStaticThread(THREAD_ID id)
            {
                return static_pool_->GetThread(id);
            }

            TaskThread* ThreadPool::GetRunOnceThread()
            {
                return runonce_pool_->GetThread();
            }

            void ThreadPool::RegisterMsgReceiver(IMsgReceiver* msg_evt, HWND& wnd, UINT& msg, unsigned int id/* = 0*/)
            {
                notifier_pool_->Register(msg_evt, wnd, msg, id);
            }

            void ThreadPool::UnRegisterMsgReceiver(IMsgReceiver* msg_evt)
            {
                notifier_pool_->UnRegister(msg_evt);
            }

            void ThreadPool::QuitStaticThread()
            {
                static_pool_->QuitAll();
            }

            void ThreadPool::EmergencyQuitStaticThread()
            {
                static_pool_->EmergencyQuitAll();
            }

            void ThreadPool::WaitAll(unsigned int msec/* = INFINITE*/)
            {
                static_pool_->WaitAll(msec);
                runonce_pool_->WaitAll(msec);
            }

        ScopedRefPtr<StaticThreadPool> ThreadPool::static_pool_ = new StaticThreadPool;
        ScopedRefPtr<RunOnceThreadPool> ThreadPool::runonce_pool_ = new RunOnceThreadPool;
        ScopedRefPtr<NotifierPool> ThreadPool::notifier_pool_ = new NotifierPool;
    } // namespace utility
} // namespace tthread
