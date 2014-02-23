#include "cancellable_runnable_reference.h"
#include "cancellable_runnable.h"

namespace tthread
{
    CancellableRunnableReference::CancellableRunnableReference()
        : flag_(NULL)
        , ptr_(NULL)
    {};

    CancellableRunnableReference::CancellableRunnableReference(ScopedRefPtr<utility::RefPtrFlag> flag, utility::CancellableRunnable * ptr)
        : flag_(flag)
        , ptr_(ptr)
    {}

    bool CancellableRunnableReference::TryCancel()
    {
        if (flag_.get())
        {
            utility::AutoLockGuard lg(flag_->lock_);
            return flag_->IsValid() ? ptr_->TryCancel() : false;
        }
        return false;
    }
} // namespace tthread
