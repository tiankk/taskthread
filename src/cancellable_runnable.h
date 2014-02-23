/**
 *    @file:        cancellable_runnable.h
 *    @author:      tiankk <tiankk@gmail.com>
 *    @created:     2014/02/13
 */

#ifndef __CANCELLABLE_RUNABLE_H__
#define __CANCELLABLE_RUNABLE_H__

#include "cancellable_runnable_reference.h"
#include <tchar.h>


namespace tthread
{
    namespace utility
    {
        /**
         *    @brief:  destruct function of HasRefPtrFlag object
         */
        template<typename T>
        struct FlagRefCountedThreadSafeTraits {
            static void Destruct(const T* x)
            {
                const HasRefPtrFlag * p = dynamic_cast<const HasRefPtrFlag*>(x);
                if (p && p->GetRefPtrFlag().get())
                {
                    AutoLockGuard lg(p->GetRefPtrFlag()->lock_);
                    p->GetRefPtrFlag()->Invalidate();
                }
                RefCountedThreadSafe<T, DefaultRefCountedThreadSafeTraits<T> >::DeleteInternal(x);
            }
        };

        /**
         *    @brief:  cancel flag class
         */
        class CancellableRunnable : public RefCountedThreadSafe<CancellableRunnable, FlagRefCountedThreadSafeTraits<CancellableRunnable > >
                                  , public HasRefPtrFlag
        {
        public:
            CancellableRunnable()
                : state_(CANCELLABLE)
            {}

            bool TryCancel()
            {
                switch(state_)
                {
                case CANCELLABLE:
                    InterlockedExchange(reinterpret_cast<volatile LONG*>(&state_), static_cast<LONG>(CANCELED));
    #ifdef _DEBUG
                    OutputDebugString(_T("\n=====try cancel succ====\n"));
    #endif
                case CANCELED:
                    return true;
                default:
    #ifdef _DEBUG
                    OutputDebugString(_T("\n=====try cancel fail===\n"));
    #endif
                    return false;
                }
            }

            CancellableRunnableReference CreateReference()
            {
                return CancellableRunnableReference(GetRefPtrFlag(), this);
            }

            void EnableCancellable()
            {
                InterlockedExchange(reinterpret_cast<volatile LONG*>(&state_), static_cast<LONG>(CANCELLABLE));
            }

            void DisableCancellable()
            {
                InterlockedExchange(reinterpret_cast<volatile LONG*>(&state_), static_cast<LONG>(NOT_CANCELLABLE));
            }

            bool IsCanceled()
            {
                return state_ == CANCELED;
            }

        private:
            enum
            {
                CANCELLABLE,
                NOT_CANCELLABLE,
                CANCELED
            };

            unsigned int state_;
        };
    } // namespace utility
} // namespace tthread

#endif // __CANCELLABLE_RUNABLE_H__
