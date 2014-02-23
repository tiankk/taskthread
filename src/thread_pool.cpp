#include "thread_pool.h"


namespace tthread
{
    namespace utility
    {
        ScopedRefPtr<StaticThreadPool> ThreadPool::static_pool_ = new StaticThreadPool;
        ScopedRefPtr<RunOnceThreadPool> ThreadPool::runonce_pool_ = new RunOnceThreadPool;
        ScopedRefPtr<NotifierPool> ThreadPool::notifier_pool_ = new NotifierPool;
    } // namespace utility
} // namespace tthread
