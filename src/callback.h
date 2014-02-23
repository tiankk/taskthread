#ifndef __CALLBACK_H__
#define __CALLBACK_H__

#include "callback_internal.h"


// /* bind function */
// int Return5() { return 5; }
// tthread::utility::Callback<int(void)> func_cb = tthread::Bind(&Return5);
// LOG(INFO) << func_cb.Run();  // Prints 5.
//
// void PrintHi() { LOG(INFO) << "hi."; }
// tthread::utility::Closure void_func_cb = tthread::Bind(&PrintHi);
// void_func_cb.Run();  // Prints: hi.
//
// /* bind method of reference-counted class */
// class Ref : public tthread::RefCountedThreadSafe<Ref> {
//  public:
//   int Foo() { return 3; }
//   void PrintBye() { LOG(INFO) << "bye."; }
// };
// tthread::ScopedRefPtr<Ref> ref = new Ref();
// tthread::utility::Callback<int(void)> ref_cb = tthread::Bind(&Ref::Foo, ref.get());
// LOG(INFO) << ref_cb.Run();  // Prints out 3.
//
// tthread::utility::Closure void_ref_cb = tthread::Bind(&Ref::PrintBye, ref.get());
// void_ref_cb.Run();  // Prints: bye.
//
// /* bind method
//  *
//  * WARNING: Must be sure object's lifecycle is long enough to run its method.
//  */
// class NoRef {
//  public:
//   int Foo() { return 4; }
//   void PrintWhy() { LOG(INFO) << "why???"; }
// };
// NoRef no_ref;
// tthread::utility::Callback<int(void)> no_ref_cb =
//     tthread::Bind(&NoRef::Foo, tthread::Unretained(&no_ref));
// LOG(INFO) << ref_cb.Run();  // Prints out 4.
//
// tthread::utility::Closure void_no_ref_cb =
//     tthread::Bind(&NoRef::PrintWhy, tthread::Unretained(&no_ref));
// void_no_ref_cb.Run();  // Prints: why???
//
// /* bind reference */
// int Identity(int n) { return n; }
// int value = 1;
// tthread::utility::Callback<int(void)> bound_copy_cb = tthread::Bind(&Identity, value);
// tthread::utility::Callback<int(void)> bound_ref_cb =
//     tthread::Bind(&Identity, tthread::ConstRef(value));
// LOG(INFO) << bound_copy_cb.Run();  // Prints 1.
// LOG(INFO) << bound_ref_cb.Run();  // Prints 1.
// value = 2;
// LOG(INFO) << bound_copy_cb.Run();  // Prints 1.
// LOG(INFO) << bound_ref_cb.Run();  // Prints 2.
//
// /* curry func */
// int Sum(int a, int b, int c) {
//   return a + b + c;
// }
// tthread::utility::Callback<int(int, int)> sum3_cb = tthread::Bind(&Sum, 3);
// LOG(INFO) << sum3_cb.Run(4, 5);  // Prints 12.
//
// tthread::utility::Callback<int(int)> sum7_cb = tthread::Bind(&Sum, 3, 4);
// LOG(INFO) << sum7_cb.Run(10);  // Prints 17.

namespace tthread {
    namespace utility {

        template <typename Sig>
        class Callback;

        namespace internal {
            template <typename Runnable, typename RunType, typename BoundArgsType>
            struct BindState;
        }  // namespace internal

        template <typename R>
        class Callback<R(void)> : public internal::CallbackBase {
        public:
            typedef R(RunType)();

            Callback() : CallbackBase(NULL) { }

            template <typename Runnable, typename RunType, typename BoundArgsType>
            Callback(internal::BindState<Runnable, RunType, BoundArgsType>* bind_state)
                : CallbackBase(bind_state) {

                    PolymorphicInvoke invoke_func =
                        &internal::BindState<Runnable, RunType, BoundArgsType>
                        ::InvokerType::Run;
                    polymorphic_invoke_ = reinterpret_cast<InvokeFuncStorage>(invoke_func);
            }

            bool Equals(const Callback& other) const {
                return CallbackBase::Equals(other);
            }

            R Run() const {
                PolymorphicInvoke f =
                    reinterpret_cast<PolymorphicInvoke>(polymorphic_invoke_);

                return f(bind_state_.get());
            }

        private:
            typedef R(*PolymorphicInvoke)(
                internal::BindStateBase*);

        };

        template <typename R, typename A1>
        class Callback<R(A1)> : public internal::CallbackBase {
        public:
            typedef R(RunType)(A1);

            Callback() : CallbackBase(NULL) { }

            template <typename Runnable, typename RunType, typename BoundArgsType>
            Callback(internal::BindState<Runnable, RunType, BoundArgsType>* bind_state)
                : CallbackBase(bind_state) {

                    PolymorphicInvoke invoke_func =
                        &internal::BindState<Runnable, RunType, BoundArgsType>
                        ::InvokerType::Run;
                    polymorphic_invoke_ = reinterpret_cast<InvokeFuncStorage>(invoke_func);
            }

            bool Equals(const Callback& other) const {
                return CallbackBase::Equals(other);
            }

            R Run(typename internal::CallbackParamTraits<A1>::ForwardType a1) const {
                PolymorphicInvoke f =
                    reinterpret_cast<PolymorphicInvoke>(polymorphic_invoke_);

                return f(bind_state_.get(), internal::CallbackForward(a1));
            }

        private:
            typedef R(*PolymorphicInvoke)(
                internal::BindStateBase*,
                typename internal::CallbackParamTraits<A1>::ForwardType);

        };

        template <typename R, typename A1, typename A2>
        class Callback<R(A1, A2)> : public internal::CallbackBase {
         public:
          typedef R(RunType)(A1, A2);

          Callback() : CallbackBase(NULL) { }

          template <typename Runnable, typename RunType, typename BoundArgsType>
          Callback(internal::BindState<Runnable, RunType, BoundArgsType>* bind_state)
              : CallbackBase(bind_state) {

            PolymorphicInvoke invoke_func =
                &internal::BindState<Runnable, RunType, BoundArgsType>
                    ::InvokerType::Run;
            polymorphic_invoke_ = reinterpret_cast<InvokeFuncStorage>(invoke_func);
          }

          bool Equals(const Callback& other) const {
            return CallbackBase::Equals(other);
          }

          R Run(typename internal::CallbackParamTraits<A1>::ForwardType a1,
                typename internal::CallbackParamTraits<A2>::ForwardType a2) const {
            PolymorphicInvoke f =
                reinterpret_cast<PolymorphicInvoke>(polymorphic_invoke_);

            return f(bind_state_.get(), internal::CallbackForward(a1),
                     internal::CallbackForward(a2));
          }

         private:
          typedef R(*PolymorphicInvoke)(
              internal::BindStateBase*,
                  typename internal::CallbackParamTraits<A1>::ForwardType,
                  typename internal::CallbackParamTraits<A2>::ForwardType);

        };

        template <typename R, typename A1, typename A2, typename A3>
        class Callback<R(A1, A2, A3)> : public internal::CallbackBase {
        public:
            typedef R(RunType)(A1, A2, A3);

            Callback() : CallbackBase(NULL) { }

            template <typename Runnable, typename RunType, typename BoundArgsType>
            Callback(internal::BindState<Runnable, RunType, BoundArgsType>* bind_state)
                : CallbackBase(bind_state) {

                    PolymorphicInvoke invoke_func =
                        &internal::BindState<Runnable, RunType, BoundArgsType>
                        ::InvokerType::Run;
                    polymorphic_invoke_ = reinterpret_cast<InvokeFuncStorage>(invoke_func);
            }

            bool Equals(const Callback& other) const {
                return CallbackBase::Equals(other);
            }

            R Run(typename internal::CallbackParamTraits<A1>::ForwardType a1,
                typename internal::CallbackParamTraits<A2>::ForwardType a2,
                typename internal::CallbackParamTraits<A3>::ForwardType a3) const {
                    PolymorphicInvoke f =
                        reinterpret_cast<PolymorphicInvoke>(polymorphic_invoke_);

                    return f(bind_state_.get(), internal::CallbackForward(a1),
                        internal::CallbackForward(a2),
                        internal::CallbackForward(a3));
            }

        private:
            typedef R(*PolymorphicInvoke)(
                internal::BindStateBase*,
                typename internal::CallbackParamTraits<A1>::ForwardType,
                typename internal::CallbackParamTraits<A2>::ForwardType,
                typename internal::CallbackParamTraits<A3>::ForwardType);

        };

        template <typename R, typename A1, typename A2, typename A3, typename A4>
        class Callback<R(A1, A2, A3, A4)> : public internal::CallbackBase {
        public:
            typedef R(RunType)(A1, A2, A3, A4);

            Callback() : CallbackBase(NULL) { }

            template <typename Runnable, typename RunType, typename BoundArgsType>
            Callback(internal::BindState<Runnable, RunType, BoundArgsType>* bind_state)
                : CallbackBase(bind_state) {

                    PolymorphicInvoke invoke_func =
                        &internal::BindState<Runnable, RunType, BoundArgsType>
                        ::InvokerType::Run;
                    polymorphic_invoke_ = reinterpret_cast<InvokeFuncStorage>(invoke_func);
            }

            bool Equals(const Callback& other) const {
                return CallbackBase::Equals(other);
            }

            R Run(typename internal::CallbackParamTraits<A1>::ForwardType a1,
                typename internal::CallbackParamTraits<A2>::ForwardType a2,
                typename internal::CallbackParamTraits<A3>::ForwardType a3,
                typename internal::CallbackParamTraits<A4>::ForwardType a4) const {
                    PolymorphicInvoke f =
                        reinterpret_cast<PolymorphicInvoke>(polymorphic_invoke_);

                    return f(bind_state_.get(), internal::CallbackForward(a1),
                        internal::CallbackForward(a2),
                        internal::CallbackForward(a3),
                        internal::CallbackForward(a4));
            }

        private:
            typedef R(*PolymorphicInvoke)(
                internal::BindStateBase*,
                typename internal::CallbackParamTraits<A1>::ForwardType,
                typename internal::CallbackParamTraits<A2>::ForwardType,
                typename internal::CallbackParamTraits<A3>::ForwardType,
                typename internal::CallbackParamTraits<A4>::ForwardType);

        };

        template <typename R, typename A1, typename A2, typename A3, typename A4,
        typename A5>
        class Callback<R(A1, A2, A3, A4, A5)> : public internal::CallbackBase {
        public:
            typedef R(RunType)(A1, A2, A3, A4, A5);

            Callback() : CallbackBase(NULL) { }

            template <typename Runnable, typename RunType, typename BoundArgsType>
            Callback(internal::BindState<Runnable, RunType, BoundArgsType>* bind_state)
                : CallbackBase(bind_state) {

                    PolymorphicInvoke invoke_func =
                        &internal::BindState<Runnable, RunType, BoundArgsType>
                        ::InvokerType::Run;
                    polymorphic_invoke_ = reinterpret_cast<InvokeFuncStorage>(invoke_func);
            }

            bool Equals(const Callback& other) const {
                return CallbackBase::Equals(other);
            }

            R Run(typename internal::CallbackParamTraits<A1>::ForwardType a1,
                typename internal::CallbackParamTraits<A2>::ForwardType a2,
                typename internal::CallbackParamTraits<A3>::ForwardType a3,
                typename internal::CallbackParamTraits<A4>::ForwardType a4,
                typename internal::CallbackParamTraits<A5>::ForwardType a5) const {
                    PolymorphicInvoke f =
                        reinterpret_cast<PolymorphicInvoke>(polymorphic_invoke_);

                    return f(bind_state_.get(), internal::CallbackForward(a1),
                        internal::CallbackForward(a2),
                        internal::CallbackForward(a3),
                        internal::CallbackForward(a4),
                        internal::CallbackForward(a5));
            }

        private:
            typedef R(*PolymorphicInvoke)(
                internal::BindStateBase*,
                typename internal::CallbackParamTraits<A1>::ForwardType,
                typename internal::CallbackParamTraits<A2>::ForwardType,
                typename internal::CallbackParamTraits<A3>::ForwardType,
                typename internal::CallbackParamTraits<A4>::ForwardType,
                typename internal::CallbackParamTraits<A5>::ForwardType);

        };

        template <typename R, typename A1, typename A2, typename A3, typename A4,
        typename A5, typename A6>
        class Callback<R(A1, A2, A3, A4, A5, A6)> : public internal::CallbackBase {
        public:
            typedef R(RunType)(A1, A2, A3, A4, A5, A6);

            Callback() : CallbackBase(NULL) { }

            template <typename Runnable, typename RunType, typename BoundArgsType>
            Callback(internal::BindState<Runnable, RunType, BoundArgsType>* bind_state)
                : CallbackBase(bind_state) {

                    PolymorphicInvoke invoke_func =
                        &internal::BindState<Runnable, RunType, BoundArgsType>
                        ::InvokerType::Run;
                    polymorphic_invoke_ = reinterpret_cast<InvokeFuncStorage>(invoke_func);
            }

            bool Equals(const Callback& other) const {
                return CallbackBase::Equals(other);
            }

            R Run(typename internal::CallbackParamTraits<A1>::ForwardType a1,
                typename internal::CallbackParamTraits<A2>::ForwardType a2,
                typename internal::CallbackParamTraits<A3>::ForwardType a3,
                typename internal::CallbackParamTraits<A4>::ForwardType a4,
                typename internal::CallbackParamTraits<A5>::ForwardType a5,
                typename internal::CallbackParamTraits<A6>::ForwardType a6) const {
                    PolymorphicInvoke f =
                        reinterpret_cast<PolymorphicInvoke>(polymorphic_invoke_);

                    return f(bind_state_.get(), internal::CallbackForward(a1),
                        internal::CallbackForward(a2),
                        internal::CallbackForward(a3),
                        internal::CallbackForward(a4),
                        internal::CallbackForward(a5),
                        internal::CallbackForward(a6));
            }

        private:
            typedef R(*PolymorphicInvoke)(
                internal::BindStateBase*,
                typename internal::CallbackParamTraits<A1>::ForwardType,
                typename internal::CallbackParamTraits<A2>::ForwardType,
                typename internal::CallbackParamTraits<A3>::ForwardType,
                typename internal::CallbackParamTraits<A4>::ForwardType,
                typename internal::CallbackParamTraits<A5>::ForwardType,
                typename internal::CallbackParamTraits<A6>::ForwardType);

        };

        template <typename R, typename A1, typename A2, typename A3, typename A4,
        typename A5, typename A6, typename A7>
        class Callback<R(A1, A2, A3, A4, A5, A6, A7)> : public internal::CallbackBase {
        public:
            typedef R(RunType)(A1, A2, A3, A4, A5, A6, A7);

            Callback() : CallbackBase(NULL) { }

            template <typename Runnable, typename RunType, typename BoundArgsType>
            Callback(internal::BindState<Runnable, RunType, BoundArgsType>* bind_state)
                : CallbackBase(bind_state) {

                    PolymorphicInvoke invoke_func =
                        &internal::BindState<Runnable, RunType, BoundArgsType>
                        ::InvokerType::Run;
                    polymorphic_invoke_ = reinterpret_cast<InvokeFuncStorage>(invoke_func);
            }

            bool Equals(const Callback& other) const {
                return CallbackBase::Equals(other);
            }

            R Run(typename internal::CallbackParamTraits<A1>::ForwardType a1,
                typename internal::CallbackParamTraits<A2>::ForwardType a2,
                typename internal::CallbackParamTraits<A3>::ForwardType a3,
                typename internal::CallbackParamTraits<A4>::ForwardType a4,
                typename internal::CallbackParamTraits<A5>::ForwardType a5,
                typename internal::CallbackParamTraits<A6>::ForwardType a6,
                typename internal::CallbackParamTraits<A7>::ForwardType a7) const {
                    PolymorphicInvoke f =
                        reinterpret_cast<PolymorphicInvoke>(polymorphic_invoke_);

                    return f(bind_state_.get(), internal::CallbackForward(a1),
                        internal::CallbackForward(a2),
                        internal::CallbackForward(a3),
                        internal::CallbackForward(a4),
                        internal::CallbackForward(a5),
                        internal::CallbackForward(a6),
                        internal::CallbackForward(a7));
            }

        private:
            typedef R(*PolymorphicInvoke)(
                internal::BindStateBase*,
                typename internal::CallbackParamTraits<A1>::ForwardType,
                typename internal::CallbackParamTraits<A2>::ForwardType,
                typename internal::CallbackParamTraits<A3>::ForwardType,
                typename internal::CallbackParamTraits<A4>::ForwardType,
                typename internal::CallbackParamTraits<A5>::ForwardType,
                typename internal::CallbackParamTraits<A6>::ForwardType,
                typename internal::CallbackParamTraits<A7>::ForwardType);

        };

        typedef Callback<void(void)> Closure;
    } // namespace utility
} // namespace tthread

#endif // __CALLBACK_H__
