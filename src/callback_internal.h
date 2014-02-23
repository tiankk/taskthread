#ifndef __CALLBACK_INTERNAL_H__
#define __CALLBACK_INTERNAL_H__

#include "scoped_ref_ptr.h"
#include "scoped_ptr.h"

namespace tthread {
    namespace utility {
        namespace internal {
            class BindStateBase : public RefCountedThreadSafe<BindStateBase> {
            protected:
                friend class RefCountedThreadSafe<BindStateBase>;
                virtual ~BindStateBase() {}
            };

            class CallbackBase {
            public:
                bool is_null() const;

                void Reset();

            protected:
                typedef void(*InvokeFuncStorage)(void);

                bool Equals(const CallbackBase& other) const;

                explicit CallbackBase(BindStateBase* bind_state);

                ~CallbackBase();

                ScopedRefPtr<BindStateBase> bind_state_;
                InvokeFuncStorage polymorphic_invoke_;
            };

            template <typename T>
            struct CallbackParamTraits {
                typedef const T& ForwardType;
                typedef T StorageType;
            };

            template <typename T>
            struct CallbackParamTraits<T&> {
                typedef T& ForwardType;
                typedef T StorageType;
            };

            template <typename T>
            struct CallbackParamTraits<ScopedPtr<T> > {
                typedef ScopedPtr<T> ForwardType;
                typedef ScopedPtr<T> StorageType;
            };


            template <typename T>
            T& CallbackForward(T& t) { return t; }

            template <typename T>
            ScopedPtr<T> CallbackForward(ScopedPtr<T>& p) { return p.Pass(); }

        }  // namespace internal
    }  // namespace utility
}  // namespace tthread

#endif // __CALLBACK_INTERNAL_H__
