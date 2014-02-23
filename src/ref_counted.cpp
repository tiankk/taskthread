#include "ref_counted.h"

namespace tthread {
    namespace utility {
        namespace internal {
            bool RefCountedThreadSafeBase::HasOneRef() const
            {
                return AtomicRefCountIsOne(&const_cast<RefCountedThreadSafeBase*>(this)->refcount_);
            }

            RefCountedThreadSafeBase::RefCountedThreadSafeBase() : refcount_(0)
            {
            }

            RefCountedThreadSafeBase::~RefCountedThreadSafeBase()
            {
            }

            void RefCountedThreadSafeBase::AddRef() const
            {
                AtomicRefCountInc(&refcount_);
            }

            bool RefCountedThreadSafeBase::Release() const
            {
                if (!AtomicRefCountDec(&refcount_))
                {
                    return true;
                }
                return false;
            }
        }  // namespace internal
    }  // namespace utility
} // namespace tthread
