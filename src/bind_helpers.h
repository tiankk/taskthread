#ifndef __BIND_HELPERS_H__
#define __BIND_HELPERS_H__

#include "callback.h"


namespace tthread {
    namespace utility {
        namespace internal {

            // Check if class has IsMethod type
            template <typename T>
            class HasIsMethodTag {
                typedef char Yes[1];
                typedef char No[2];

                template <typename U>
                static Yes& Check(typename U::IsMethod*);

                template <typename U>
                static No& Check(...);

            public:
                static const bool value = sizeof(Check<T>(0)) == sizeof(Yes);
            };

            template <typename T>
            class UnretainedWrapper {
            public:
                explicit UnretainedWrapper(T* o) : ptr_(o) {}
                T* get() const { return ptr_; }
            private:
                T* ptr_;
            };

            template <typename T>
            class ConstRefWrapper {
            public:
                explicit ConstRefWrapper(const T& o) : ptr_(&o) {}
                const T& get() const { return *ptr_; }
            private:
                const T* ptr_;
            };

            template <typename T>
            struct IgnoreResultHelper {
                explicit IgnoreResultHelper(T functor) : functor_(functor) {}

                T functor_;
            };

            template <typename T>
            struct IgnoreResultHelper<Callback<T> > {
                explicit IgnoreResultHelper(const Callback<T>& functor) : functor_(functor) {}

                const Callback<T>& functor_;
            };

            template <typename T>
            struct UnwrapTraits {
                typedef const T& ForwardType;
                static ForwardType Unwrap(const T& o) { return o; }
            };

            template <typename T>
            struct UnwrapTraits<UnretainedWrapper<T> > {
                typedef T* ForwardType;
                static ForwardType Unwrap(UnretainedWrapper<T> unretained) {
                    return unretained.get();
                }
            };

            template <typename T>
            struct UnwrapTraits<ConstRefWrapper<T> > {
                typedef const T& ForwardType;
                static ForwardType Unwrap(ConstRefWrapper<T> const_ref) {
                    return const_ref.get();
                }
            };

            template <typename T>
            struct UnwrapTraits<ScopedRefPtr<T> > {
                typedef T* ForwardType;
                static ForwardType Unwrap(const ScopedRefPtr<T>& o) { return o.get(); }
            };

            template <bool is_method, typename T>
            struct MaybeRefcount;

            template <typename T>
            struct MaybeRefcount<false, T> {
                static void AddRef(const T&) {}
                static void Release(const T&) {}
            };

            template <typename T>
            struct MaybeRefcount<true, T> {
                static void AddRef(const T&) {}
                static void Release(const T&) {}
            };

            template <typename T>
            struct MaybeRefcount<true, T*> {
                static void AddRef(T* o) { o->AddRef(); }
                static void Release(T* o) { o->Release(); }
            };

            template <typename T>
            struct MaybeRefcount<true, ScopedRefPtr<T> > {
                static void AddRef(const ScopedRefPtr<T>& /*o*/) {}
                static void Release(const ScopedRefPtr<T>& /*o*/) {}
            };

            template <typename T>
            struct MaybeRefcount<true, const T*> {
                static void AddRef(const T* o) { o->AddRef(); }
                static void Release(const T* o) { o->Release(); }
            };
        }  // namespace internal
    } // namespace utility

    template <typename T>
    static inline utility::internal::UnretainedWrapper<T> Unretained(T* o) {
        return utility::internal::UnretainedWrapper<T>(o);
    }

    template <typename T>
    static inline utility::internal::ConstRefWrapper<T> ConstRef(const T& o) {
        return utility::internal::ConstRefWrapper<T>(o);
    }

    template <typename T>
    static inline utility::internal::IgnoreResultHelper<T> IgnoreResult(T data) {
        return utility::internal::IgnoreResultHelper<T>(data);
    }

    template <typename T>
    static inline utility::internal::IgnoreResultHelper<utility::Callback<T> >
        IgnoreResult(const utility::Callback<T>& data) {
            return utility::internal::IgnoreResultHelper<utility::Callback<T> >(data);
    }
} // namespace tthread

#endif // __BIND_HELPERS_H__
