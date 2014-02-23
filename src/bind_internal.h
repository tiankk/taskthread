#ifndef __BIND_INTERNAL_H__
#define __BIND_INTERNAL_H__

#include "bind_helpers.h"
#include "callback_internal.h"


namespace tthread {
    namespace utility {
        template<class T, T v>
        struct IntegralConstant {
            static const T value = v;
            typedef T value_type;
            typedef IntegralConstant<T, v> type;
        };

        template <class T, T v> const T IntegralConstant<T, v>::value;

        typedef IntegralConstant<bool, true> true_type;
        typedef IntegralConstant<bool, false> false_type;

        namespace internal {

            // RunnableAdapter<>
            template <typename Functor>
            class RunnableAdapter;

#ifndef _WIN64
            // __stdcall Function: Param 0.
            template <typename R>
            class RunnableAdapter<R(__stdcall *)()> {
            public:
                typedef R (RunType)();

                explicit RunnableAdapter(R(__stdcall *function)())
                    : func_(function) {
                }

                R Run() {
                    return func_();
                }

            private:
                R (__stdcall *func_)();
            };

            // __stdcall Function: Param 1.
            template <typename R, typename A1>
            class RunnableAdapter<R(__stdcall *)(A1)> {
            public:
                typedef R (RunType)(A1);

                explicit RunnableAdapter(R(__stdcall *function)(A1))
                    : func_(function) {
                }

                R Run(typename CallbackParamTraits<A1>::ForwardType a1) {
                    return func_(a1);
                }

            private:
                R (__stdcall *func_)(A1);
            };

            // __stdcall Function: Param 2.
            template <typename R, typename A1, typename A2>
            class RunnableAdapter<R(__stdcall *)(A1, A2)> {
            public:
                typedef R (RunType)(A1, A2);

                explicit RunnableAdapter(R(__stdcall *function)(A1, A2))
                    : func_(function) {
                }

                R Run(typename CallbackParamTraits<A1>::ForwardType a1,
                    typename CallbackParamTraits<A2>::ForwardType a2) {
                        return func_(a1, a2);
                }

            private:
                R (__stdcall *func_)(A1, A2);
            };

            // __stdcall Function: Param 3.
            template <typename R, typename A1, typename A2, typename A3>
            class RunnableAdapter<R(__stdcall *)(A1, A2, A3)> {
            public:
                typedef R (RunType)(A1, A2, A3);

                explicit RunnableAdapter(R(__stdcall *function)(A1, A2, A3))
                    : function_(function) {
                }

                R Run(typename CallbackParamTraits<A1>::ForwardType a1,
                    typename CallbackParamTraits<A2>::ForwardType a2,
                    typename CallbackParamTraits<A3>::ForwardType a3) {
                        return function_(a1, a2, a3);
                }

            private:
                R (__stdcall *function_)(A1, A2, A3);
            };



            // __stdcall Function: Param 4.
            template <typename R, typename A1, typename A2, typename A3, typename A4>
            class RunnableAdapter<R(__stdcall *)(A1, A2, A3, A4)> {
            public:
                typedef R (RunType)(A1, A2, A3, A4);

                explicit RunnableAdapter(R(__stdcall *function)(A1, A2, A3, A4))
                    : function_(function) {
                }

                R Run(typename CallbackParamTraits<A1>::ForwardType a1,
                    typename CallbackParamTraits<A2>::ForwardType a2,
                    typename CallbackParamTraits<A3>::ForwardType a3,
                    typename CallbackParamTraits<A4>::ForwardType a4) {
                        return function_(a1, a2, a3, a4);
                }

            private:
                R (__stdcall *function_)(A1, A2, A3, A4);
            };


            // __stdcall Function: Param 5.
            template <typename R, typename A1, typename A2, typename A3, typename A4,
                typename A5>
            class RunnableAdapter<R(__stdcall *)(A1, A2, A3, A4, A5)> {
            public:
                typedef R (RunType)(A1, A2, A3, A4, A5);

                explicit RunnableAdapter(R(__stdcall *function)(A1, A2, A3, A4, A5))
                    : function_(function) {
                }

                R Run(typename CallbackParamTraits<A1>::ForwardType a1,
                    typename CallbackParamTraits<A2>::ForwardType a2,
                    typename CallbackParamTraits<A3>::ForwardType a3,
                    typename CallbackParamTraits<A4>::ForwardType a4,
                    typename CallbackParamTraits<A5>::ForwardType a5) {
                        return function_(a1, a2, a3, a4, a5);
                }

            private:
                R (__stdcall *function_)(A1, A2, A3, A4, A5);
            };

            // __stdcall Function: Param 6.
            template <typename R, typename A1, typename A2, typename A3, typename A4,
                typename A5, typename A6>
            class RunnableAdapter<R(__stdcall *)(A1, A2, A3, A4, A5, A6)> {
            public:
                typedef R (RunType)(A1, A2, A3, A4, A5, A6);

                explicit RunnableAdapter(R(__stdcall *function)(A1, A2, A3, A4, A5, A6))
                    : function_(function) {
                }

                R Run(typename CallbackParamTraits<A1>::ForwardType a1,
                    typename CallbackParamTraits<A2>::ForwardType a2,
                    typename CallbackParamTraits<A3>::ForwardType a3,
                    typename CallbackParamTraits<A4>::ForwardType a4,
                    typename CallbackParamTraits<A5>::ForwardType a5,
                    typename CallbackParamTraits<A6>::ForwardType a6) {
                        return function_(a1, a2, a3, a4, a5, a6);
                }

            private:
                R (__stdcall *function_)(A1, A2, A3, A4, A5, A6);
            };

            // __stdcall Function: Param 7.
            template <typename R, typename A1, typename A2, typename A3, typename A4,
                typename A5, typename A6, typename A7>
            class RunnableAdapter<R(__stdcall *)(A1, A2, A3, A4, A5, A6, A7)> {
            public:
                typedef R (RunType)(A1, A2, A3, A4, A5, A6, A7);

                explicit RunnableAdapter(R(__stdcall *function)(A1, A2, A3, A4, A5, A6, A7))
                    : function_(function) {
                }

                R Run(typename CallbackParamTraits<A1>::ForwardType a1,
                    typename CallbackParamTraits<A2>::ForwardType a2,
                    typename CallbackParamTraits<A3>::ForwardType a3,
                    typename CallbackParamTraits<A4>::ForwardType a4,
                    typename CallbackParamTraits<A5>::ForwardType a5,
                    typename CallbackParamTraits<A6>::ForwardType a6,
                    typename CallbackParamTraits<A7>::ForwardType a7) {
                        return function_(a1, a2, a3, a4, a5, a6, a7);
                }

            private:
                R (__stdcall *function_)(A1, A2, A3, A4, A5, A6, A7);
            };
#endif

            // Function: Param 0.
            template <typename R>
            class RunnableAdapter<R(*)()> {
            public:
                typedef R (RunType)();

                explicit RunnableAdapter(R(*function)())
                    : func_(function) {
                }

                R Run() {
                    return func_();
                }

            private:
                R (*func_)();
            };

            // Method: Param 0.
            template <typename R, typename T>
            class RunnableAdapter<R(T::*)()> {
            public:
                typedef R (RunType)(T*);
                typedef true_type IsMethod;

                explicit RunnableAdapter(R(T::*method)())
                    : method_(method) {
                }

                R Run(T* object) {
                    return (object->*method_)();
                }

            private:
                R (T::*method_)();
            };

            // Const Method: Param 0.
            template <typename R, typename T>
            class RunnableAdapter<R(T::*)() const> {
            public:
                typedef R (RunType)(const T*);
                typedef true_type IsMethod;

                explicit RunnableAdapter(R(T::*method)() const)
                    : method_(method) {
                }

                R Run(const T* object) {
                    return (object->*method_)();
                }

            private:
                R (T::*method_)() const;
            };

            // Function: Param 1.
            template <typename R, typename A1>
            class RunnableAdapter<R(*)(A1)> {
            public:
                typedef R (RunType)(A1);

                explicit RunnableAdapter(R(*function)(A1))
                    : func_(function) {
                }

                R Run(typename CallbackParamTraits<A1>::ForwardType a1) {
                    return func_(CallbackForward(a1));
                }

            private:
                R (*func_)(A1);
            };

            // Method: Param 1.
            template <typename R, typename T, typename A1>
            class RunnableAdapter<R(T::*)(A1)> {
            public:
                typedef R (RunType)(T*, A1);
                typedef true_type IsMethod;

                explicit RunnableAdapter(R(T::*method)(A1))
                    : method_(method) {
                }

                R Run(T* object, typename CallbackParamTraits<A1>::ForwardType a1) {
                    return (object->*method_)(CallbackForward(a1));
                }

            private:
                R (T::*method_)(A1);
            };

            // Const Method: Param 1.
            template <typename R, typename T, typename A1>
            class RunnableAdapter<R(T::*)(A1) const> {
            public:
                typedef R (RunType)(const T*, A1);
                typedef true_type IsMethod;

                explicit RunnableAdapter(R(T::*method)(A1) const)
                    : method_(method) {
                }

                R Run(const T* object, typename CallbackParamTraits<A1>::ForwardType a1) {
                    return (object->*method_)(CallbackForward(a1));
                }

            private:
                R (T::*method_)(A1) const;
            };

            // Function: Param 2.
            template <typename R, typename A1, typename A2>
            class RunnableAdapter<R(*)(A1, A2)> {
            public:
                typedef R (RunType)(A1, A2);

                explicit RunnableAdapter(R(*function)(A1, A2))
                    : func_(function) {
                }

                R Run(typename CallbackParamTraits<A1>::ForwardType a1,
                    typename CallbackParamTraits<A2>::ForwardType a2) {
                        return func_(CallbackForward(a1), CallbackForward(a2));
                }

            private:
                R (*func_)(A1, A2);
            };

            // Method: Param 2.
            template <typename R, typename T, typename A1, typename A2>
            class RunnableAdapter<R(T::*)(A1, A2)> {
            public:
                typedef R (RunType)(T*, A1, A2);
                typedef true_type IsMethod;

                explicit RunnableAdapter(R(T::*method)(A1, A2))
                    : method_(method) {
                }

                R Run(T* object, typename CallbackParamTraits<A1>::ForwardType a1,
                    typename CallbackParamTraits<A2>::ForwardType a2) {
                        return (object->*method_)(CallbackForward(a1), CallbackForward(a2));
                }

            private:
                R (T::*method_)(A1, A2);
            };

            // Const Method: Param 2.
            template <typename R, typename T, typename A1, typename A2>
            class RunnableAdapter<R(T::*)(A1, A2) const> {
            public:
                typedef R (RunType)(const T*, A1, A2);
                typedef true_type IsMethod;

                explicit RunnableAdapter(R(T::*method)(A1, A2) const)
                    : method_(method) {
                }

                R Run(const T* object, typename CallbackParamTraits<A1>::ForwardType a1,
                    typename CallbackParamTraits<A2>::ForwardType a2) {
                        return (object->*method_)(CallbackForward(a1), CallbackForward(a2));
                }

            private:
                R (T::*method_)(A1, A2) const;
            };

            // Function: Param 3.
            template <typename R, typename A1, typename A2, typename A3>
            class RunnableAdapter<R(*)(A1, A2, A3)> {
            public:
                typedef R (RunType)(A1, A2, A3);

                explicit RunnableAdapter(R(*function)(A1, A2, A3))
                    : function_(function) {
                }

                R Run(typename CallbackParamTraits<A1>::ForwardType a1,
                    typename CallbackParamTraits<A2>::ForwardType a2,
                    typename CallbackParamTraits<A3>::ForwardType a3) {
                        return function_(CallbackForward(a1), CallbackForward(a2),
                            CallbackForward(a3));
                }

            private:
                R (*function_)(A1, A2, A3);
            };

            // Method: Param 3.
            template <typename R, typename T, typename A1, typename A2, typename A3>
            class RunnableAdapter<R(T::*)(A1, A2, A3)> {
            public:
                typedef R (RunType)(T*, A1, A2, A3);
                typedef true_type IsMethod;

                explicit RunnableAdapter(R(T::*method)(A1, A2, A3))
                    : method_(method) {
                }

                R Run(T* object, typename CallbackParamTraits<A1>::ForwardType a1,
                    typename CallbackParamTraits<A2>::ForwardType a2,
                    typename CallbackParamTraits<A3>::ForwardType a3) {
                        return (object->*method_)(CallbackForward(a1), CallbackForward(a2),
                            CallbackForward(a3));
                }

            private:
                R (T::*method_)(A1, A2, A3);
            };

            // Const Method: Param 3.
            template <typename R, typename T, typename A1, typename A2, typename A3>
            class RunnableAdapter<R(T::*)(A1, A2, A3) const> {
            public:
                typedef R (RunType)(const T*, A1, A2, A3);
                typedef true_type IsMethod;

                explicit RunnableAdapter(R(T::*method)(A1, A2, A3) const)
                    : method_(method) {
                }

                R Run(const T* object, typename CallbackParamTraits<A1>::ForwardType a1,
                    typename CallbackParamTraits<A2>::ForwardType a2,
                    typename CallbackParamTraits<A3>::ForwardType a3) {
                        return (object->*method_)(CallbackForward(a1), CallbackForward(a2),
                            CallbackForward(a3));
                }

            private:
                R (T::*method_)(A1, A2, A3) const;
            };

            // Function: Param 4.
            template <typename R, typename A1, typename A2, typename A3, typename A4>
            class RunnableAdapter<R(*)(A1, A2, A3, A4)> {
            public:
                typedef R (RunType)(A1, A2, A3, A4);

                explicit RunnableAdapter(R(*function)(A1, A2, A3, A4))
                    : function_(function) {
                }

                R Run(typename CallbackParamTraits<A1>::ForwardType a1,
                    typename CallbackParamTraits<A2>::ForwardType a2,
                    typename CallbackParamTraits<A3>::ForwardType a3,
                    typename CallbackParamTraits<A4>::ForwardType a4) {
                        return function_(CallbackForward(a1), CallbackForward(a2),
                            CallbackForward(a3), CallbackForward(a4));
                }

            private:
                R (*function_)(A1, A2, A3, A4);
            };

            // Method: Param 4.
            template <typename R, typename T, typename A1, typename A2, typename A3,
                typename A4>
            class RunnableAdapter<R(T::*)(A1, A2, A3, A4)> {
            public:
                typedef R (RunType)(T*, A1, A2, A3, A4);
                typedef true_type IsMethod;

                explicit RunnableAdapter(R(T::*method)(A1, A2, A3, A4))
                    : method_(method) {
                }

                R Run(T* object, typename CallbackParamTraits<A1>::ForwardType a1,
                    typename CallbackParamTraits<A2>::ForwardType a2,
                    typename CallbackParamTraits<A3>::ForwardType a3,
                    typename CallbackParamTraits<A4>::ForwardType a4) {
                        return (object->*method_)(CallbackForward(a1), CallbackForward(a2),
                            CallbackForward(a3), CallbackForward(a4));
                }

            private:
                R (T::*method_)(A1, A2, A3, A4);
            };

            // Const Method: Param 4.
            template <typename R, typename T, typename A1, typename A2, typename A3,
                typename A4>
            class RunnableAdapter<R(T::*)(A1, A2, A3, A4) const> {
            public:
                typedef R (RunType)(const T*, A1, A2, A3, A4);
                typedef true_type IsMethod;

                explicit RunnableAdapter(R(T::*method)(A1, A2, A3, A4) const)
                    : method_(method) {
                }

                R Run(const T* object, typename CallbackParamTraits<A1>::ForwardType a1,
                    typename CallbackParamTraits<A2>::ForwardType a2,
                    typename CallbackParamTraits<A3>::ForwardType a3,
                    typename CallbackParamTraits<A4>::ForwardType a4) {
                        return (object->*method_)(CallbackForward(a1), CallbackForward(a2),
                            CallbackForward(a3), CallbackForward(a4));
                }

            private:
                R (T::*method_)(A1, A2, A3, A4) const;
            };

            // Function: Param 5.
            template <typename R, typename A1, typename A2, typename A3, typename A4,
                typename A5>
            class RunnableAdapter<R(*)(A1, A2, A3, A4, A5)> {
            public:
                typedef R (RunType)(A1, A2, A3, A4, A5);

                explicit RunnableAdapter(R(*function)(A1, A2, A3, A4, A5))
                    : function_(function) {
                }

                R Run(typename CallbackParamTraits<A1>::ForwardType a1,
                    typename CallbackParamTraits<A2>::ForwardType a2,
                    typename CallbackParamTraits<A3>::ForwardType a3,
                    typename CallbackParamTraits<A4>::ForwardType a4,
                    typename CallbackParamTraits<A5>::ForwardType a5) {
                        return function_(CallbackForward(a1), CallbackForward(a2),
                            CallbackForward(a3), CallbackForward(a4), CallbackForward(a5));
                }

            private:
                R (*function_)(A1, A2, A3, A4, A5);
            };

            // Method: Param 5.
            template <typename R, typename T, typename A1, typename A2, typename A3,
                typename A4, typename A5>
            class RunnableAdapter<R(T::*)(A1, A2, A3, A4, A5)> {
            public:
                typedef R (RunType)(T*, A1, A2, A3, A4, A5);
                typedef true_type IsMethod;

                explicit RunnableAdapter(R(T::*method)(A1, A2, A3, A4, A5))
                    : method_(method) {
                }

                R Run(T* object, typename CallbackParamTraits<A1>::ForwardType a1,
                    typename CallbackParamTraits<A2>::ForwardType a2,
                    typename CallbackParamTraits<A3>::ForwardType a3,
                    typename CallbackParamTraits<A4>::ForwardType a4,
                    typename CallbackParamTraits<A5>::ForwardType a5) {
                        return (object->*method_)(CallbackForward(a1), CallbackForward(a2),
                            CallbackForward(a3), CallbackForward(a4), CallbackForward(a5));
                }

            private:
                R (T::*method_)(A1, A2, A3, A4, A5);
            };

            // Const Method: Param 5.
            template <typename R, typename T, typename A1, typename A2, typename A3,
                typename A4, typename A5>
            class RunnableAdapter<R(T::*)(A1, A2, A3, A4, A5) const> {
            public:
                typedef R (RunType)(const T*, A1, A2, A3, A4, A5);
                typedef true_type IsMethod;

                explicit RunnableAdapter(R(T::*method)(A1, A2, A3, A4, A5) const)
                    : method_(method) {
                }

                R Run(const T* object, typename CallbackParamTraits<A1>::ForwardType a1,
                    typename CallbackParamTraits<A2>::ForwardType a2,
                    typename CallbackParamTraits<A3>::ForwardType a3,
                    typename CallbackParamTraits<A4>::ForwardType a4,
                    typename CallbackParamTraits<A5>::ForwardType a5) {
                        return (object->*method_)(CallbackForward(a1), CallbackForward(a2),
                            CallbackForward(a3), CallbackForward(a4), CallbackForward(a5));
                }

            private:
                R (T::*method_)(A1, A2, A3, A4, A5) const;
            };

            // Function: Param 6.
            template <typename R, typename A1, typename A2, typename A3, typename A4,
                typename A5, typename A6>
            class RunnableAdapter<R(*)(A1, A2, A3, A4, A5, A6)> {
            public:
                typedef R (RunType)(A1, A2, A3, A4, A5, A6);

                explicit RunnableAdapter(R(*function)(A1, A2, A3, A4, A5, A6))
                    : function_(function) {
                }

                R Run(typename CallbackParamTraits<A1>::ForwardType a1,
                    typename CallbackParamTraits<A2>::ForwardType a2,
                    typename CallbackParamTraits<A3>::ForwardType a3,
                    typename CallbackParamTraits<A4>::ForwardType a4,
                    typename CallbackParamTraits<A5>::ForwardType a5,
                    typename CallbackParamTraits<A6>::ForwardType a6) {
                        return function_(CallbackForward(a1), CallbackForward(a2),
                            CallbackForward(a3), CallbackForward(a4), CallbackForward(a5),
                            CallbackForward(a6));
                }

            private:
                R (*function_)(A1, A2, A3, A4, A5, A6);
            };

            // Method: Param 6.
            template <typename R, typename T, typename A1, typename A2, typename A3,
                typename A4, typename A5, typename A6>
            class RunnableAdapter<R(T::*)(A1, A2, A3, A4, A5, A6)> {
            public:
                typedef R (RunType)(T*, A1, A2, A3, A4, A5, A6);
                typedef true_type IsMethod;

                explicit RunnableAdapter(R(T::*method)(A1, A2, A3, A4, A5, A6))
                    : method_(method) {
                }

                R Run(T* object, typename CallbackParamTraits<A1>::ForwardType a1,
                    typename CallbackParamTraits<A2>::ForwardType a2,
                    typename CallbackParamTraits<A3>::ForwardType a3,
                    typename CallbackParamTraits<A4>::ForwardType a4,
                    typename CallbackParamTraits<A5>::ForwardType a5,
                    typename CallbackParamTraits<A6>::ForwardType a6) {
                        return (object->*method_)(CallbackForward(a1), CallbackForward(a2),
                            CallbackForward(a3), CallbackForward(a4), CallbackForward(a5),
                            CallbackForward(a6));
                }

            private:
                R (T::*method_)(A1, A2, A3, A4, A5, A6);
            };

            // Const Method: Param 6.
            template <typename R, typename T, typename A1, typename A2, typename A3,
                typename A4, typename A5, typename A6>
            class RunnableAdapter<R(T::*)(A1, A2, A3, A4, A5, A6) const> {
            public:
                typedef R (RunType)(const T*, A1, A2, A3, A4, A5, A6);
                typedef true_type IsMethod;

                explicit RunnableAdapter(R(T::*method)(A1, A2, A3, A4, A5, A6) const)
                    : method_(method) {
                }

                R Run(const T* object, typename CallbackParamTraits<A1>::ForwardType a1,
                    typename CallbackParamTraits<A2>::ForwardType a2,
                    typename CallbackParamTraits<A3>::ForwardType a3,
                    typename CallbackParamTraits<A4>::ForwardType a4,
                    typename CallbackParamTraits<A5>::ForwardType a5,
                    typename CallbackParamTraits<A6>::ForwardType a6) {
                        return (object->*method_)(CallbackForward(a1), CallbackForward(a2),
                            CallbackForward(a3), CallbackForward(a4), CallbackForward(a5),
                            CallbackForward(a6));
                }

            private:
                R (T::*method_)(A1, A2, A3, A4, A5, A6) const;
            };

            // Function: Param 7.
            template <typename R, typename A1, typename A2, typename A3, typename A4,
                typename A5, typename A6, typename A7>
            class RunnableAdapter<R(*)(A1, A2, A3, A4, A5, A6, A7)> {
            public:
                typedef R (RunType)(A1, A2, A3, A4, A5, A6, A7);

                explicit RunnableAdapter(R(*function)(A1, A2, A3, A4, A5, A6, A7))
                    : function_(function) {
                }

                R Run(typename CallbackParamTraits<A1>::ForwardType a1,
                    typename CallbackParamTraits<A2>::ForwardType a2,
                    typename CallbackParamTraits<A3>::ForwardType a3,
                    typename CallbackParamTraits<A4>::ForwardType a4,
                    typename CallbackParamTraits<A5>::ForwardType a5,
                    typename CallbackParamTraits<A6>::ForwardType a6,
                    typename CallbackParamTraits<A7>::ForwardType a7) {
                        return function_(CallbackForward(a1), CallbackForward(a2),
                            CallbackForward(a3), CallbackForward(a4), CallbackForward(a5),
                            CallbackForward(a6), CallbackForward(a7));
                }

            private:
                R (*function_)(A1, A2, A3, A4, A5, A6, A7);
            };

            // Method: Param 7.
            template <typename R, typename T, typename A1, typename A2, typename A3,
                typename A4, typename A5, typename A6, typename A7>
            class RunnableAdapter<R(T::*)(A1, A2, A3, A4, A5, A6, A7)> {
            public:
                typedef R (RunType)(T*, A1, A2, A3, A4, A5, A6, A7);
                typedef true_type IsMethod;

                explicit RunnableAdapter(R(T::*method)(A1, A2, A3, A4, A5, A6, A7))
                    : method_(method) {
                }

                R Run(T* object, typename CallbackParamTraits<A1>::ForwardType a1,
                    typename CallbackParamTraits<A2>::ForwardType a2,
                    typename CallbackParamTraits<A3>::ForwardType a3,
                    typename CallbackParamTraits<A4>::ForwardType a4,
                    typename CallbackParamTraits<A5>::ForwardType a5,
                    typename CallbackParamTraits<A6>::ForwardType a6,
                    typename CallbackParamTraits<A7>::ForwardType a7) {
                        return (object->*method_)(CallbackForward(a1), CallbackForward(a2),
                            CallbackForward(a3), CallbackForward(a4), CallbackForward(a5),
                            CallbackForward(a6), CallbackForward(a7));
                }

            private:
                R (T::*method_)(A1, A2, A3, A4, A5, A6, A7);
            };

            // Const Method: Param 7.
            template <typename R, typename T, typename A1, typename A2, typename A3,
                typename A4, typename A5, typename A6, typename A7>
            class RunnableAdapter<R(T::*)(A1, A2, A3, A4, A5, A6, A7) const> {
            public:
                typedef R (RunType)(const T*, A1, A2, A3, A4, A5, A6, A7);
                typedef true_type IsMethod;

                explicit RunnableAdapter(R(T::*method)(A1, A2, A3, A4, A5, A6, A7) const)
                    : method_(method) {
                }

                R Run(const T* object, typename CallbackParamTraits<A1>::ForwardType a1,
                    typename CallbackParamTraits<A2>::ForwardType a2,
                    typename CallbackParamTraits<A3>::ForwardType a3,
                    typename CallbackParamTraits<A4>::ForwardType a4,
                    typename CallbackParamTraits<A5>::ForwardType a5,
                    typename CallbackParamTraits<A6>::ForwardType a6,
                    typename CallbackParamTraits<A7>::ForwardType a7) {
                        return (object->*method_)(CallbackForward(a1), CallbackForward(a2),
                            CallbackForward(a3), CallbackForward(a4), CallbackForward(a5),
                            CallbackForward(a6), CallbackForward(a7));
                }

            private:
                R (T::*method_)(A1, A2, A3, A4, A5, A6, A7) const;
            };


            // ForceVoidReturn<>
            template <typename Sig>
            struct ForceVoidReturn;

            template <typename R>
            struct ForceVoidReturn<R()> {
                typedef void(RunType)();
            };

            template <typename R, typename A1>
            struct ForceVoidReturn<R(A1)> {
                typedef void(RunType)(A1);
            };

            template <typename R, typename A1, typename A2>
            struct ForceVoidReturn<R(A1, A2)> {
                typedef void(RunType)(A1, A2);
            };

            template <typename R, typename A1, typename A2, typename A3>
            struct ForceVoidReturn<R(A1, A2, A3)> {
                typedef void(RunType)(A1, A2, A3);
            };

            template <typename R, typename A1, typename A2, typename A3, typename A4>
            struct ForceVoidReturn<R(A1, A2, A3, A4)> {
                typedef void(RunType)(A1, A2, A3, A4);
            };

            template <typename R, typename A1, typename A2, typename A3, typename A4,
                typename A5>
            struct ForceVoidReturn<R(A1, A2, A3, A4, A5)> {
                typedef void(RunType)(A1, A2, A3, A4, A5);
            };

            template <typename R, typename A1, typename A2, typename A3, typename A4,
                typename A5, typename A6>
            struct ForceVoidReturn<R(A1, A2, A3, A4, A5, A6)> {
                typedef void(RunType)(A1, A2, A3, A4, A5, A6);
            };

            template <typename R, typename A1, typename A2, typename A3, typename A4,
                typename A5, typename A6, typename A7>
            struct ForceVoidReturn<R(A1, A2, A3, A4, A5, A6, A7)> {
                typedef void(RunType)(A1, A2, A3, A4, A5, A6, A7);
            };

            // FunctorTraits<>
            template <typename T>
            struct FunctorTraits {
                typedef RunnableAdapter<T> RunnableType;
                typedef typename RunnableType::RunType RunType;
            };

            template <typename T>
            struct FunctorTraits<IgnoreResultHelper<T> > {
                typedef typename FunctorTraits<T>::RunnableType RunnableType;
                typedef typename ForceVoidReturn<typename RunnableType::RunType>::RunType RunType;
            };

            template <typename T>
            struct FunctorTraits<Callback<T> > {
                typedef Callback<T> RunnableType;
                typedef typename Callback<T>::RunType RunType;
            };


            // MakeRunnable<>
            template <typename T>
            typename FunctorTraits<T>::RunnableType MakeRunnable(const T& t) {
                return RunnableAdapter<T>(t);
            }

            template <typename T>
            typename FunctorTraits<T>::RunnableType MakeRunnable(const IgnoreResultHelper<T>& t) {
                return MakeRunnable(t.func_tor);
            }

            template <typename T>
            const typename FunctorTraits<Callback<T> >::RunnableType& MakeRunnable(const Callback<T>& t) {
                return t;
            }


            // InvokeHelper<>
            template <typename ReturnType, typename Runnable,
                typename ArgsType>
            struct InvokeHelper;

            template <typename ReturnType, typename Runnable>
            struct InvokeHelper<ReturnType, Runnable, void()>  {
                static ReturnType MakeItSo(Runnable runnable) {
                    return runnable.Run();
                }
            };

            template <typename Runnable>
            struct InvokeHelper<void, Runnable, void()>  {
                static void MakeItSo(Runnable runnable) {
                    runnable.Run();
                }
            };

            template <typename ReturnType, typename Runnable,typename A1>
            struct InvokeHelper<ReturnType, Runnable, void(A1)>  {
                static ReturnType MakeItSo(Runnable runnable, A1 a1) {
                    return runnable.Run(CallbackForward(a1));
                }
            };

            template <typename Runnable,typename A1>
            struct InvokeHelper<void, Runnable, void(A1)>  {
                static void MakeItSo(Runnable runnable, A1 a1) {
                    runnable.Run(CallbackForward(a1));
                }
            };

            template <typename ReturnType, typename Runnable,typename A1, typename A2>
            struct InvokeHelper<ReturnType, Runnable, void(A1, A2)>  {
                static ReturnType MakeItSo(Runnable runnable, A1 a1, A2 a2) {
                    return runnable.Run(CallbackForward(a1), CallbackForward(a2));
                }
            };

            template <typename Runnable,typename A1, typename A2>
            struct InvokeHelper<void, Runnable, void(A1, A2)>  {
                static void MakeItSo(Runnable runnable, A1 a1, A2 a2) {
                    runnable.Run(CallbackForward(a1), CallbackForward(a2));
                }
            };

            template <typename ReturnType, typename Runnable,typename A1, typename A2,
                typename A3>
            struct InvokeHelper<ReturnType, Runnable,
                void(A1, A2, A3)>  {
                    static ReturnType MakeItSo(Runnable runnable, A1 a1, A2 a2, A3 a3) {
                        return runnable.Run(CallbackForward(a1), CallbackForward(a2),
                            CallbackForward(a3));
                    }
            };

            template <typename Runnable,typename A1, typename A2, typename A3>
            struct InvokeHelper<void, Runnable,
                void(A1, A2, A3)>  {
                    static void MakeItSo(Runnable runnable, A1 a1, A2 a2, A3 a3) {
                        runnable.Run(CallbackForward(a1), CallbackForward(a2), CallbackForward(a3));
                    }
            };

            template <typename ReturnType, typename Runnable,typename A1, typename A2,
                typename A3, typename A4>
            struct InvokeHelper<ReturnType, Runnable,
                void(A1, A2, A3, A4)>  {
                    static ReturnType MakeItSo(Runnable runnable, A1 a1, A2 a2, A3 a3, A4 a4) {
                        return runnable.Run(CallbackForward(a1), CallbackForward(a2),
                            CallbackForward(a3), CallbackForward(a4));
                    }
            };

            template <typename Runnable,typename A1, typename A2, typename A3, typename A4>
            struct InvokeHelper<void, Runnable,
                void(A1, A2, A3, A4)>  {
                    static void MakeItSo(Runnable runnable, A1 a1, A2 a2, A3 a3, A4 a4) {
                        runnable.Run(CallbackForward(a1), CallbackForward(a2), CallbackForward(a3),
                            CallbackForward(a4));
                    }
            };

            template <typename ReturnType, typename Runnable,typename A1, typename A2,
                typename A3, typename A4, typename A5>
            struct InvokeHelper<ReturnType, Runnable,
                void(A1, A2, A3, A4, A5)>  {
                    static ReturnType MakeItSo(Runnable runnable, A1 a1, A2 a2, A3 a3, A4 a4,
                        A5 a5) {
                            return runnable.Run(CallbackForward(a1), CallbackForward(a2),
                                CallbackForward(a3), CallbackForward(a4), CallbackForward(a5));
                    }
            };

            template <typename Runnable,typename A1, typename A2, typename A3, typename A4,
                typename A5>
            struct InvokeHelper<void, Runnable,
                void(A1, A2, A3, A4, A5)>  {
                    static void MakeItSo(Runnable runnable, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) {
                        runnable.Run(CallbackForward(a1), CallbackForward(a2), CallbackForward(a3),
                            CallbackForward(a4), CallbackForward(a5));
                    }
            };

            template <typename ReturnType, typename Runnable,typename A1, typename A2,
                typename A3, typename A4, typename A5, typename A6>
            struct InvokeHelper<ReturnType, Runnable,
                void(A1, A2, A3, A4, A5, A6)>  {
                    static ReturnType MakeItSo(Runnable runnable, A1 a1, A2 a2, A3 a3, A4 a4,
                        A5 a5, A6 a6) {
                            return runnable.Run(CallbackForward(a1), CallbackForward(a2),
                                CallbackForward(a3), CallbackForward(a4), CallbackForward(a5),
                                CallbackForward(a6));
                    }
            };

            template <typename Runnable,typename A1, typename A2, typename A3, typename A4,
                typename A5, typename A6>
            struct InvokeHelper<void, Runnable,
                void(A1, A2, A3, A4, A5, A6)>  {
                    static void MakeItSo(Runnable runnable, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5,
                        A6 a6) {
                            runnable.Run(CallbackForward(a1), CallbackForward(a2), CallbackForward(a3),
                                CallbackForward(a4), CallbackForward(a5), CallbackForward(a6));
                    }
            };

            template <typename ReturnType, typename Runnable,typename A1, typename A2,
                typename A3, typename A4, typename A5, typename A6, typename A7>
            struct InvokeHelper<ReturnType, Runnable,
                void(A1, A2, A3, A4, A5, A6, A7)>  {
                    static ReturnType MakeItSo(Runnable runnable, A1 a1, A2 a2, A3 a3, A4 a4,
                        A5 a5, A6 a6, A7 a7) {
                            return runnable.Run(CallbackForward(a1), CallbackForward(a2),
                                CallbackForward(a3), CallbackForward(a4), CallbackForward(a5),
                                CallbackForward(a6), CallbackForward(a7));
                    }
            };

            template <typename Runnable,typename A1, typename A2, typename A3, typename A4,
                typename A5, typename A6, typename A7>
            struct InvokeHelper<void, Runnable,
                void(A1, A2, A3, A4, A5, A6, A7)>  {
                    static void MakeItSo(Runnable runnable, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5,
                        A6 a6, A7 a7) {
                            runnable.Run(CallbackForward(a1), CallbackForward(a2), CallbackForward(a3),
                                CallbackForward(a4), CallbackForward(a5), CallbackForward(a6),
                                CallbackForward(a7));
                    }
            };

            // Invoker<>
            template <int NumBound, typename Storage, typename RunType>
            struct Invoker;

            // Param 0 -> 0.
            template <typename StorageType, typename R>
            struct Invoker<0, StorageType, R()> {
                typedef R(RunType)(BindStateBase*);

                typedef R(UnboundRunType)();

                static R Run(BindStateBase* base) {
                    StorageType* storage = static_cast<StorageType*>(base);

                    return InvokeHelper<R,
                        typename StorageType::RunnableType,
                        void()>
                        ::MakeItSo(storage->runnable_);
                }
            };

            // Param 1 -> 1.
            template <typename StorageType, typename R,typename X1>
            struct Invoker<0, StorageType, R(X1)> {
                typedef R(RunType)(BindStateBase*,
                    typename CallbackParamTraits<X1>::ForwardType);

                typedef R(UnboundRunType)(X1);

                static R Run(BindStateBase* base,
                    typename CallbackParamTraits<X1>::ForwardType x1) {
                        StorageType* storage = static_cast<StorageType*>(base);

                        return InvokeHelper<R, typename StorageType::RunnableType,
                            void(typename CallbackParamTraits<X1>::ForwardType x1)>
                            ::MakeItSo(storage->runnable_, CallbackForward(x1));
                }
            };

            // Param 1 -> 0.
            template <typename StorageType, typename R,typename X1>
            struct Invoker<1, StorageType, R(X1)> {
                typedef R(RunType)(BindStateBase*);

                typedef R(UnboundRunType)();

                static R Run(BindStateBase* base) {
                    StorageType* storage = static_cast<StorageType*>(base);

                    typedef typename StorageType::Bound1UnwrapTraits Bound1UnwrapTraits;

                    typename Bound1UnwrapTraits::ForwardType x1 =
                        Bound1UnwrapTraits::Unwrap(storage->p1_);
                    return InvokeHelper<R, typename StorageType::RunnableType,
                        void(typename Bound1UnwrapTraits::ForwardType)>
                        ::MakeItSo(storage->runnable_, CallbackForward(x1));
                }
            };

            // Param 2 -> 2.
            template <typename StorageType, typename R,typename X1, typename X2>
            struct Invoker<0, StorageType, R(X1, X2)> {
                typedef R(RunType)(BindStateBase*,
                    typename CallbackParamTraits<X1>::ForwardType,
                    typename CallbackParamTraits<X2>::ForwardType);

                typedef R(UnboundRunType)(X1, X2);

                static R Run(BindStateBase* base,
                    typename CallbackParamTraits<X1>::ForwardType x1,
                    typename CallbackParamTraits<X2>::ForwardType x2) {
                        StorageType* storage = static_cast<StorageType*>(base);

                        return InvokeHelper<R, typename StorageType::RunnableType,
                            void(typename CallbackParamTraits<X1>::ForwardType x1,
                            typename CallbackParamTraits<X2>::ForwardType x2)>
                            ::MakeItSo(storage->runnable_, CallbackForward(x1),
                            CallbackForward(x2));
                }
            };

            // Param 2 -> 1.
            template <typename StorageType, typename R,typename X1, typename X2>
            struct Invoker<1, StorageType, R(X1, X2)> {
                typedef R(RunType)(BindStateBase*,
                    typename CallbackParamTraits<X2>::ForwardType);

                typedef R(UnboundRunType)(X2);

                static R Run(BindStateBase* base,
                    typename CallbackParamTraits<X2>::ForwardType x2) {
                        StorageType* storage = static_cast<StorageType*>(base);

                        typedef typename StorageType::Bound1UnwrapTraits Bound1UnwrapTraits;

                        typename Bound1UnwrapTraits::ForwardType x1 =
                            Bound1UnwrapTraits::Unwrap(storage->p1_);
                        return InvokeHelper<R, typename StorageType::RunnableType,
                            void(typename Bound1UnwrapTraits::ForwardType,
                            typename CallbackParamTraits<X2>::ForwardType x2)>
                            ::MakeItSo(storage->runnable_, CallbackForward(x1),
                            CallbackForward(x2));
                }
            };

            // Param 2 -> 0.
            template <typename StorageType, typename R,typename X1, typename X2>
            struct Invoker<2, StorageType, R(X1, X2)> {
                typedef R(RunType)(BindStateBase*);

                typedef R(UnboundRunType)();

                static R Run(BindStateBase* base) {
                    StorageType* storage = static_cast<StorageType*>(base);

                    typedef typename StorageType::Bound1UnwrapTraits Bound1UnwrapTraits;
                    typedef typename StorageType::Bound2UnwrapTraits Bound2UnwrapTraits;

                    typename Bound1UnwrapTraits::ForwardType x1 =
                        Bound1UnwrapTraits::Unwrap(storage->p1_);
                    typename Bound2UnwrapTraits::ForwardType x2 =
                        Bound2UnwrapTraits::Unwrap(storage->p2_);
                    return InvokeHelper<R, typename StorageType::RunnableType,
                        void(typename Bound1UnwrapTraits::ForwardType,
                        typename Bound2UnwrapTraits::ForwardType)>
                        ::MakeItSo(storage->runnable_, CallbackForward(x1),
                        CallbackForward(x2));
                }
            };

            // Param 3 -> 3.
            template <typename StorageType, typename R,typename X1, typename X2,
                typename X3>
            struct Invoker<0, StorageType, R(X1, X2, X3)> {
                typedef R(RunType)(BindStateBase*,
                    typename CallbackParamTraits<X1>::ForwardType,
                    typename CallbackParamTraits<X2>::ForwardType,
                    typename CallbackParamTraits<X3>::ForwardType);

                typedef R(UnboundRunType)(X1, X2, X3);

                static R Run(BindStateBase* base,
                    typename CallbackParamTraits<X1>::ForwardType x1,
                    typename CallbackParamTraits<X2>::ForwardType x2,
                    typename CallbackParamTraits<X3>::ForwardType x3) {
                        StorageType* storage = static_cast<StorageType*>(base);

                        return InvokeHelper<R, typename StorageType::RunnableType,
                            void(typename CallbackParamTraits<X1>::ForwardType x1,
                            typename CallbackParamTraits<X2>::ForwardType x2,
                            typename CallbackParamTraits<X3>::ForwardType x3)>
                            ::MakeItSo(storage->runnable_, CallbackForward(x1),
                            CallbackForward(x2), CallbackForward(x3));
                }
            };

            // Param 3 -> 2.
            template <typename StorageType, typename R,typename X1, typename X2,
                typename X3>
            struct Invoker<1, StorageType, R(X1, X2, X3)> {
                typedef R(RunType)(BindStateBase*,
                    typename CallbackParamTraits<X2>::ForwardType,
                    typename CallbackParamTraits<X3>::ForwardType);

                typedef R(UnboundRunType)(X2, X3);

                static R Run(BindStateBase* base,
                    typename CallbackParamTraits<X2>::ForwardType x2,
                    typename CallbackParamTraits<X3>::ForwardType x3) {
                        StorageType* storage = static_cast<StorageType*>(base);

                        typedef typename StorageType::Bound1UnwrapTraits Bound1UnwrapTraits;

                        typename Bound1UnwrapTraits::ForwardType x1 =
                            Bound1UnwrapTraits::Unwrap(storage->p1_);
                        return InvokeHelper<R, typename StorageType::RunnableType,
                            void(typename Bound1UnwrapTraits::ForwardType,
                            typename CallbackParamTraits<X2>::ForwardType x2,
                            typename CallbackParamTraits<X3>::ForwardType x3)>
                            ::MakeItSo(storage->runnable_, CallbackForward(x1),
                            CallbackForward(x2), CallbackForward(x3));
                }
            };

            // Param 3 -> 1.
            template <typename StorageType, typename R,typename X1, typename X2,
                typename X3>
            struct Invoker<2, StorageType, R(X1, X2, X3)> {
                typedef R(RunType)(BindStateBase*,
                    typename CallbackParamTraits<X3>::ForwardType);

                typedef R(UnboundRunType)(X3);

                static R Run(BindStateBase* base,
                    typename CallbackParamTraits<X3>::ForwardType x3) {
                        StorageType* storage = static_cast<StorageType*>(base);

                        typedef typename StorageType::Bound1UnwrapTraits Bound1UnwrapTraits;
                        typedef typename StorageType::Bound2UnwrapTraits Bound2UnwrapTraits;

                        typename Bound1UnwrapTraits::ForwardType x1 =
                            Bound1UnwrapTraits::Unwrap(storage->p1_);
                        typename Bound2UnwrapTraits::ForwardType x2 =
                            Bound2UnwrapTraits::Unwrap(storage->p2_);
                        return InvokeHelper<R, typename StorageType::RunnableType,
                            void(typename Bound1UnwrapTraits::ForwardType,
                            typename Bound2UnwrapTraits::ForwardType,
                            typename CallbackParamTraits<X3>::ForwardType x3)>
                            ::MakeItSo(storage->runnable_, CallbackForward(x1),
                            CallbackForward(x2), CallbackForward(x3));
                }
            };

            // Param 3 -> 0.
            template <typename StorageType, typename R,typename X1, typename X2,
                typename X3>
            struct Invoker<3, StorageType, R(X1, X2, X3)> {
                typedef R(RunType)(BindStateBase*);

                typedef R(UnboundRunType)();

                static R Run(BindStateBase* base) {
                    StorageType* storage = static_cast<StorageType*>(base);

                    typedef typename StorageType::Bound1UnwrapTraits Bound1UnwrapTraits;
                    typedef typename StorageType::Bound2UnwrapTraits Bound2UnwrapTraits;
                    typedef typename StorageType::Bound3UnwrapTraits Bound3UnwrapTraits;

                    typename Bound1UnwrapTraits::ForwardType x1 =
                        Bound1UnwrapTraits::Unwrap(storage->p1_);
                    typename Bound2UnwrapTraits::ForwardType x2 =
                        Bound2UnwrapTraits::Unwrap(storage->p2_);
                    typename Bound3UnwrapTraits::ForwardType x3 =
                        Bound3UnwrapTraits::Unwrap(storage->p3_);
                    return InvokeHelper<R, typename StorageType::RunnableType,
                        void(typename Bound1UnwrapTraits::ForwardType,
                        typename Bound2UnwrapTraits::ForwardType,
                        typename Bound3UnwrapTraits::ForwardType)>
                        ::MakeItSo(storage->runnable_, CallbackForward(x1),
                        CallbackForward(x2), CallbackForward(x3));
                }
            };

            // Param 4 -> 4.
            template <typename StorageType, typename R,typename X1, typename X2,
                typename X3, typename X4>
            struct Invoker<0, StorageType, R(X1, X2, X3, X4)> {
                typedef R(RunType)(BindStateBase*,
                    typename CallbackParamTraits<X1>::ForwardType,
                    typename CallbackParamTraits<X2>::ForwardType,
                    typename CallbackParamTraits<X3>::ForwardType,
                    typename CallbackParamTraits<X4>::ForwardType);

                typedef R(UnboundRunType)(X1, X2, X3, X4);

                static R Run(BindStateBase* base,
                    typename CallbackParamTraits<X1>::ForwardType x1,
                    typename CallbackParamTraits<X2>::ForwardType x2,
                    typename CallbackParamTraits<X3>::ForwardType x3,
                    typename CallbackParamTraits<X4>::ForwardType x4) {
                        StorageType* storage = static_cast<StorageType*>(base);

                        return InvokeHelper<R, typename StorageType::RunnableType,
                            void(typename CallbackParamTraits<X1>::ForwardType x1,
                            typename CallbackParamTraits<X2>::ForwardType x2,
                            typename CallbackParamTraits<X3>::ForwardType x3,
                            typename CallbackParamTraits<X4>::ForwardType x4)>
                            ::MakeItSo(storage->runnable_, CallbackForward(x1),
                            CallbackForward(x2), CallbackForward(x3),
                            CallbackForward(x4));
                }
            };

            // Param 4 -> 3.
            template <typename StorageType, typename R,typename X1, typename X2,
                typename X3, typename X4>
            struct Invoker<1, StorageType, R(X1, X2, X3, X4)> {
                typedef R(RunType)(BindStateBase*,
                    typename CallbackParamTraits<X2>::ForwardType,
                    typename CallbackParamTraits<X3>::ForwardType,
                    typename CallbackParamTraits<X4>::ForwardType);

                typedef R(UnboundRunType)(X2, X3, X4);

                static R Run(BindStateBase* base,
                    typename CallbackParamTraits<X2>::ForwardType x2,
                    typename CallbackParamTraits<X3>::ForwardType x3,
                    typename CallbackParamTraits<X4>::ForwardType x4) {
                        StorageType* storage = static_cast<StorageType*>(base);

                        typedef typename StorageType::Bound1UnwrapTraits Bound1UnwrapTraits;

                        typename Bound1UnwrapTraits::ForwardType x1 =
                            Bound1UnwrapTraits::Unwrap(storage->p1_);
                        return InvokeHelper<R,
                            typename StorageType::RunnableType,
                            void(typename Bound1UnwrapTraits::ForwardType,
                            typename CallbackParamTraits<X2>::ForwardType x2,
                            typename CallbackParamTraits<X3>::ForwardType x3,
                            typename CallbackParamTraits<X4>::ForwardType x4)>
                            ::MakeItSo(storage->runnable_, CallbackForward(x1),
                            CallbackForward(x2), CallbackForward(x3),
                            CallbackForward(x4));
                }
            };

            // Param 4 -> 2.
            template <typename StorageType, typename R,typename X1, typename X2,
                typename X3, typename X4>
            struct Invoker<2, StorageType, R(X1, X2, X3, X4)> {
                typedef R(RunType)(BindStateBase*,
                    typename CallbackParamTraits<X3>::ForwardType,
                    typename CallbackParamTraits<X4>::ForwardType);

                typedef R(UnboundRunType)(X3, X4);

                static R Run(BindStateBase* base,
                    typename CallbackParamTraits<X3>::ForwardType x3,
                    typename CallbackParamTraits<X4>::ForwardType x4) {
                        StorageType* storage = static_cast<StorageType*>(base);

                        typedef typename StorageType::Bound1UnwrapTraits Bound1UnwrapTraits;
                        typedef typename StorageType::Bound2UnwrapTraits Bound2UnwrapTraits;

                        typename Bound1UnwrapTraits::ForwardType x1 =
                            Bound1UnwrapTraits::Unwrap(storage->p1_);
                        typename Bound2UnwrapTraits::ForwardType x2 =
                            Bound2UnwrapTraits::Unwrap(storage->p2_);
                        return InvokeHelper<R,
                            typename StorageType::RunnableType,
                            void(typename Bound1UnwrapTraits::ForwardType,
                            typename Bound2UnwrapTraits::ForwardType,
                            typename CallbackParamTraits<X3>::ForwardType x3,
                            typename CallbackParamTraits<X4>::ForwardType x4)>
                            ::MakeItSo(storage->runnable_, CallbackForward(x1),
                            CallbackForward(x2), CallbackForward(x3),
                            CallbackForward(x4));
                }
            };

            // Param 4 -> 1.
            template <typename StorageType, typename R,typename X1, typename X2,
                typename X3, typename X4>
            struct Invoker<3, StorageType, R(X1, X2, X3, X4)> {
                typedef R(RunType)(BindStateBase*,
                    typename CallbackParamTraits<X4>::ForwardType);

                typedef R(UnboundRunType)(X4);

                static R Run(BindStateBase* base,
                    typename CallbackParamTraits<X4>::ForwardType x4) {
                        StorageType* storage = static_cast<StorageType*>(base);

                        typedef typename StorageType::Bound1UnwrapTraits Bound1UnwrapTraits;
                        typedef typename StorageType::Bound2UnwrapTraits Bound2UnwrapTraits;
                        typedef typename StorageType::Bound3UnwrapTraits Bound3UnwrapTraits;

                        typename Bound1UnwrapTraits::ForwardType x1 =
                            Bound1UnwrapTraits::Unwrap(storage->p1_);
                        typename Bound2UnwrapTraits::ForwardType x2 =
                            Bound2UnwrapTraits::Unwrap(storage->p2_);
                        typename Bound3UnwrapTraits::ForwardType x3 =
                            Bound3UnwrapTraits::Unwrap(storage->p3_);
                        return InvokeHelper<R,
                            typename StorageType::RunnableType,
                            void(typename Bound1UnwrapTraits::ForwardType,
                            typename Bound2UnwrapTraits::ForwardType,
                            typename Bound3UnwrapTraits::ForwardType,
                            typename CallbackParamTraits<X4>::ForwardType x4)>
                            ::MakeItSo(storage->runnable_, CallbackForward(x1),
                            CallbackForward(x2), CallbackForward(x3),
                            CallbackForward(x4));
                }
            };

            // Param 4 -> 0.
            template <typename StorageType, typename R,typename X1, typename X2,
                typename X3, typename X4>
            struct Invoker<4, StorageType, R(X1, X2, X3, X4)> {
                typedef R(RunType)(BindStateBase*);

                typedef R(UnboundRunType)();

                static R Run(BindStateBase* base) {
                    StorageType* storage = static_cast<StorageType*>(base);

                    typedef typename StorageType::Bound1UnwrapTraits Bound1UnwrapTraits;
                    typedef typename StorageType::Bound2UnwrapTraits Bound2UnwrapTraits;
                    typedef typename StorageType::Bound3UnwrapTraits Bound3UnwrapTraits;
                    typedef typename StorageType::Bound4UnwrapTraits Bound4UnwrapTraits;

                    typename Bound1UnwrapTraits::ForwardType x1 =
                        Bound1UnwrapTraits::Unwrap(storage->p1_);
                    typename Bound2UnwrapTraits::ForwardType x2 =
                        Bound2UnwrapTraits::Unwrap(storage->p2_);
                    typename Bound3UnwrapTraits::ForwardType x3 =
                        Bound3UnwrapTraits::Unwrap(storage->p3_);
                    typename Bound4UnwrapTraits::ForwardType x4 =
                        Bound4UnwrapTraits::Unwrap(storage->p4_);
                    return InvokeHelper<R,
                        typename StorageType::RunnableType,
                        void(typename Bound1UnwrapTraits::ForwardType,
                        typename Bound2UnwrapTraits::ForwardType,
                        typename Bound3UnwrapTraits::ForwardType,
                        typename Bound4UnwrapTraits::ForwardType)>
                        ::MakeItSo(storage->runnable_, CallbackForward(x1),
                        CallbackForward(x2), CallbackForward(x3),
                        CallbackForward(x4));
                }
            };

            // Param 5 -> 5.
            template <typename StorageType, typename R,typename X1, typename X2,
                typename X3, typename X4, typename X5>
            struct Invoker<0, StorageType, R(X1, X2, X3, X4, X5)> {
                typedef R(RunType)(BindStateBase*,
                    typename CallbackParamTraits<X1>::ForwardType,
                    typename CallbackParamTraits<X2>::ForwardType,
                    typename CallbackParamTraits<X3>::ForwardType,
                    typename CallbackParamTraits<X4>::ForwardType,
                    typename CallbackParamTraits<X5>::ForwardType);

                typedef R(UnboundRunType)(X1, X2, X3, X4, X5);

                static R Run(BindStateBase* base,
                    typename CallbackParamTraits<X1>::ForwardType x1,
                    typename CallbackParamTraits<X2>::ForwardType x2,
                    typename CallbackParamTraits<X3>::ForwardType x3,
                    typename CallbackParamTraits<X4>::ForwardType x4,
                    typename CallbackParamTraits<X5>::ForwardType x5) {
                        StorageType* storage = static_cast<StorageType*>(base);

                        return InvokeHelper<R,
                            typename StorageType::RunnableType,
                            void(typename CallbackParamTraits<X1>::ForwardType x1,
                            typename CallbackParamTraits<X2>::ForwardType x2,
                            typename CallbackParamTraits<X3>::ForwardType x3,
                            typename CallbackParamTraits<X4>::ForwardType x4,
                            typename CallbackParamTraits<X5>::ForwardType x5)>
                            ::MakeItSo(storage->runnable_, CallbackForward(x1),
                            CallbackForward(x2), CallbackForward(x3),
                            CallbackForward(x4), CallbackForward(x5));
                }
            };

            // Param 5 -> 4.
            template <typename StorageType, typename R,typename X1, typename X2,
                typename X3, typename X4, typename X5>
            struct Invoker<1, StorageType, R(X1, X2, X3, X4, X5)> {
                typedef R(RunType)(BindStateBase*,
                    typename CallbackParamTraits<X2>::ForwardType,
                    typename CallbackParamTraits<X3>::ForwardType,
                    typename CallbackParamTraits<X4>::ForwardType,
                    typename CallbackParamTraits<X5>::ForwardType);

                typedef R(UnboundRunType)(X2, X3, X4, X5);

                static R Run(BindStateBase* base,
                    typename CallbackParamTraits<X2>::ForwardType x2,
                    typename CallbackParamTraits<X3>::ForwardType x3,
                    typename CallbackParamTraits<X4>::ForwardType x4,
                    typename CallbackParamTraits<X5>::ForwardType x5) {
                        StorageType* storage = static_cast<StorageType*>(base);

                        typedef typename StorageType::Bound1UnwrapTraits Bound1UnwrapTraits;

                        typename Bound1UnwrapTraits::ForwardType x1 =
                            Bound1UnwrapTraits::Unwrap(storage->p1_);
                        return InvokeHelper<R,
                            typename StorageType::RunnableType,
                            void(typename Bound1UnwrapTraits::ForwardType,
                            typename CallbackParamTraits<X2>::ForwardType x2,
                            typename CallbackParamTraits<X3>::ForwardType x3,
                            typename CallbackParamTraits<X4>::ForwardType x4,
                            typename CallbackParamTraits<X5>::ForwardType x5)>
                            ::MakeItSo(storage->runnable_, CallbackForward(x1),
                            CallbackForward(x2), CallbackForward(x3),
                            CallbackForward(x4), CallbackForward(x5));
                }
            };

            // Param 5 -> 3.
            template <typename StorageType, typename R,typename X1, typename X2,
                typename X3, typename X4, typename X5>
            struct Invoker<2, StorageType, R(X1, X2, X3, X4, X5)> {
                typedef R(RunType)(BindStateBase*,
                    typename CallbackParamTraits<X3>::ForwardType,
                    typename CallbackParamTraits<X4>::ForwardType,
                    typename CallbackParamTraits<X5>::ForwardType);

                typedef R(UnboundRunType)(X3, X4, X5);

                static R Run(BindStateBase* base,
                    typename CallbackParamTraits<X3>::ForwardType x3,
                    typename CallbackParamTraits<X4>::ForwardType x4,
                    typename CallbackParamTraits<X5>::ForwardType x5) {
                        StorageType* storage = static_cast<StorageType*>(base);

                        typedef typename StorageType::Bound1UnwrapTraits Bound1UnwrapTraits;
                        typedef typename StorageType::Bound2UnwrapTraits Bound2UnwrapTraits;

                        typename Bound1UnwrapTraits::ForwardType x1 =
                            Bound1UnwrapTraits::Unwrap(storage->p1_);
                        typename Bound2UnwrapTraits::ForwardType x2 =
                            Bound2UnwrapTraits::Unwrap(storage->p2_);
                        return InvokeHelper<R,
                            typename StorageType::RunnableType,
                            void(typename Bound1UnwrapTraits::ForwardType,
                            typename Bound2UnwrapTraits::ForwardType,
                            typename CallbackParamTraits<X3>::ForwardType x3,
                            typename CallbackParamTraits<X4>::ForwardType x4,
                            typename CallbackParamTraits<X5>::ForwardType x5)>
                            ::MakeItSo(storage->runnable_, CallbackForward(x1),
                            CallbackForward(x2), CallbackForward(x3),
                            CallbackForward(x4), CallbackForward(x5));
                }
            };

            // Param 5 -> 2.
            template <typename StorageType, typename R,typename X1, typename X2,
                typename X3, typename X4, typename X5>
            struct Invoker<3, StorageType, R(X1, X2, X3, X4, X5)> {
                typedef R(RunType)(BindStateBase*,
                    typename CallbackParamTraits<X4>::ForwardType,
                    typename CallbackParamTraits<X5>::ForwardType);

                typedef R(UnboundRunType)(X4, X5);

                static R Run(BindStateBase* base,
                    typename CallbackParamTraits<X4>::ForwardType x4,
                    typename CallbackParamTraits<X5>::ForwardType x5) {
                        StorageType* storage = static_cast<StorageType*>(base);

                        typedef typename StorageType::Bound1UnwrapTraits Bound1UnwrapTraits;
                        typedef typename StorageType::Bound2UnwrapTraits Bound2UnwrapTraits;
                        typedef typename StorageType::Bound3UnwrapTraits Bound3UnwrapTraits;

                        typename Bound1UnwrapTraits::ForwardType x1 =
                            Bound1UnwrapTraits::Unwrap(storage->p1_);
                        typename Bound2UnwrapTraits::ForwardType x2 =
                            Bound2UnwrapTraits::Unwrap(storage->p2_);
                        typename Bound3UnwrapTraits::ForwardType x3 =
                            Bound3UnwrapTraits::Unwrap(storage->p3_);
                        return InvokeHelper<R,
                            typename StorageType::RunnableType,
                            void(typename Bound1UnwrapTraits::ForwardType,
                            typename Bound2UnwrapTraits::ForwardType,
                            typename Bound3UnwrapTraits::ForwardType,
                            typename CallbackParamTraits<X4>::ForwardType x4,
                            typename CallbackParamTraits<X5>::ForwardType x5)>
                            ::MakeItSo(storage->runnable_, CallbackForward(x1),
                            CallbackForward(x2), CallbackForward(x3),
                            CallbackForward(x4), CallbackForward(x5));
                }
            };

            // Param 5 -> 1.
            template <typename StorageType, typename R,typename X1, typename X2,
                typename X3, typename X4, typename X5>
            struct Invoker<4, StorageType, R(X1, X2, X3, X4, X5)> {
                typedef R(RunType)(BindStateBase*,
                    typename CallbackParamTraits<X5>::ForwardType);

                typedef R(UnboundRunType)(X5);

                static R Run(BindStateBase* base,
                    typename CallbackParamTraits<X5>::ForwardType x5) {
                        StorageType* storage = static_cast<StorageType*>(base);

                        typedef typename StorageType::Bound1UnwrapTraits Bound1UnwrapTraits;
                        typedef typename StorageType::Bound2UnwrapTraits Bound2UnwrapTraits;
                        typedef typename StorageType::Bound3UnwrapTraits Bound3UnwrapTraits;
                        typedef typename StorageType::Bound4UnwrapTraits Bound4UnwrapTraits;

                        typename Bound1UnwrapTraits::ForwardType x1 =
                            Bound1UnwrapTraits::Unwrap(storage->p1_);
                        typename Bound2UnwrapTraits::ForwardType x2 =
                            Bound2UnwrapTraits::Unwrap(storage->p2_);
                        typename Bound3UnwrapTraits::ForwardType x3 =
                            Bound3UnwrapTraits::Unwrap(storage->p3_);
                        typename Bound4UnwrapTraits::ForwardType x4 =
                            Bound4UnwrapTraits::Unwrap(storage->p4_);
                        return InvokeHelper<R,
                            typename StorageType::RunnableType,
                            void(typename Bound1UnwrapTraits::ForwardType,
                            typename Bound2UnwrapTraits::ForwardType,
                            typename Bound3UnwrapTraits::ForwardType,
                            typename Bound4UnwrapTraits::ForwardType,
                            typename CallbackParamTraits<X5>::ForwardType x5)>
                            ::MakeItSo(storage->runnable_, CallbackForward(x1),
                            CallbackForward(x2), CallbackForward(x3),
                            CallbackForward(x4), CallbackForward(x5));
                }
            };

            // Param 5 -> 0.
            template <typename StorageType, typename R,typename X1, typename X2,
                typename X3, typename X4, typename X5>
            struct Invoker<5, StorageType, R(X1, X2, X3, X4, X5)> {
                typedef R(RunType)(BindStateBase*);

                typedef R(UnboundRunType)();

                static R Run(BindStateBase* base) {
                    StorageType* storage = static_cast<StorageType*>(base);

                    typedef typename StorageType::Bound1UnwrapTraits Bound1UnwrapTraits;
                    typedef typename StorageType::Bound2UnwrapTraits Bound2UnwrapTraits;
                    typedef typename StorageType::Bound3UnwrapTraits Bound3UnwrapTraits;
                    typedef typename StorageType::Bound4UnwrapTraits Bound4UnwrapTraits;
                    typedef typename StorageType::Bound5UnwrapTraits Bound5UnwrapTraits;

                    typename Bound1UnwrapTraits::ForwardType x1 =
                        Bound1UnwrapTraits::Unwrap(storage->p1_);
                    typename Bound2UnwrapTraits::ForwardType x2 =
                        Bound2UnwrapTraits::Unwrap(storage->p2_);
                    typename Bound3UnwrapTraits::ForwardType x3 =
                        Bound3UnwrapTraits::Unwrap(storage->p3_);
                    typename Bound4UnwrapTraits::ForwardType x4 =
                        Bound4UnwrapTraits::Unwrap(storage->p4_);
                    typename Bound5UnwrapTraits::ForwardType x5 =
                        Bound5UnwrapTraits::Unwrap(storage->p5_);
                    return InvokeHelper<R,
                        typename StorageType::RunnableType,
                        void(typename Bound1UnwrapTraits::ForwardType,
                        typename Bound2UnwrapTraits::ForwardType,
                        typename Bound3UnwrapTraits::ForwardType,
                        typename Bound4UnwrapTraits::ForwardType,
                        typename Bound5UnwrapTraits::ForwardType)>
                        ::MakeItSo(storage->runnable_, CallbackForward(x1),
                        CallbackForward(x2), CallbackForward(x3),
                        CallbackForward(x4), CallbackForward(x5));
                }
            };

            // Param 6 -> 6.
            template <typename StorageType, typename R,typename X1, typename X2,
                typename X3, typename X4, typename X5, typename X6>
            struct Invoker<0, StorageType, R(X1, X2, X3, X4, X5, X6)> {
                typedef R(RunType)(BindStateBase*,
                    typename CallbackParamTraits<X1>::ForwardType,
                    typename CallbackParamTraits<X2>::ForwardType,
                    typename CallbackParamTraits<X3>::ForwardType,
                    typename CallbackParamTraits<X4>::ForwardType,
                    typename CallbackParamTraits<X5>::ForwardType,
                    typename CallbackParamTraits<X6>::ForwardType);

                typedef R(UnboundRunType)(X1, X2, X3, X4, X5, X6);

                static R Run(BindStateBase* base,
                    typename CallbackParamTraits<X1>::ForwardType x1,
                    typename CallbackParamTraits<X2>::ForwardType x2,
                    typename CallbackParamTraits<X3>::ForwardType x3,
                    typename CallbackParamTraits<X4>::ForwardType x4,
                    typename CallbackParamTraits<X5>::ForwardType x5,
                    typename CallbackParamTraits<X6>::ForwardType x6) {
                        StorageType* storage = static_cast<StorageType*>(base);

                        return InvokeHelper<R,
                            typename StorageType::RunnableType,
                            void(typename CallbackParamTraits<X1>::ForwardType x1,
                            typename CallbackParamTraits<X2>::ForwardType x2,
                            typename CallbackParamTraits<X3>::ForwardType x3,
                            typename CallbackParamTraits<X4>::ForwardType x4,
                            typename CallbackParamTraits<X5>::ForwardType x5,
                            typename CallbackParamTraits<X6>::ForwardType x6)>
                            ::MakeItSo(storage->runnable_, CallbackForward(x1),
                            CallbackForward(x2), CallbackForward(x3),
                            CallbackForward(x4), CallbackForward(x5),
                            CallbackForward(x6));
                }
            };

            // Param 6 -> 5.
            template <typename StorageType, typename R,typename X1, typename X2,
                typename X3, typename X4, typename X5, typename X6>
            struct Invoker<1, StorageType, R(X1, X2, X3, X4, X5, X6)> {
                typedef R(RunType)(BindStateBase*,
                    typename CallbackParamTraits<X2>::ForwardType,
                    typename CallbackParamTraits<X3>::ForwardType,
                    typename CallbackParamTraits<X4>::ForwardType,
                    typename CallbackParamTraits<X5>::ForwardType,
                    typename CallbackParamTraits<X6>::ForwardType);

                typedef R(UnboundRunType)(X2, X3, X4, X5, X6);

                static R Run(BindStateBase* base,
                    typename CallbackParamTraits<X2>::ForwardType x2,
                    typename CallbackParamTraits<X3>::ForwardType x3,
                    typename CallbackParamTraits<X4>::ForwardType x4,
                    typename CallbackParamTraits<X5>::ForwardType x5,
                    typename CallbackParamTraits<X6>::ForwardType x6) {
                        StorageType* storage = static_cast<StorageType*>(base);

                        typedef typename StorageType::Bound1UnwrapTraits Bound1UnwrapTraits;

                        typename Bound1UnwrapTraits::ForwardType x1 =
                            Bound1UnwrapTraits::Unwrap(storage->p1_);
                        return InvokeHelper<R,
                            typename StorageType::RunnableType,
                            void(typename Bound1UnwrapTraits::ForwardType,
                            typename CallbackParamTraits<X2>::ForwardType x2,
                            typename CallbackParamTraits<X3>::ForwardType x3,
                            typename CallbackParamTraits<X4>::ForwardType x4,
                            typename CallbackParamTraits<X5>::ForwardType x5,
                            typename CallbackParamTraits<X6>::ForwardType x6)>
                            ::MakeItSo(storage->runnable_, CallbackForward(x1),
                            CallbackForward(x2), CallbackForward(x3),
                            CallbackForward(x4), CallbackForward(x5),
                            CallbackForward(x6));
                }
            };

            // Param 6 -> 4.
            template <typename StorageType, typename R,typename X1, typename X2,
                typename X3, typename X4, typename X5, typename X6>
            struct Invoker<2, StorageType, R(X1, X2, X3, X4, X5, X6)> {
                typedef R(RunType)(BindStateBase*,
                    typename CallbackParamTraits<X3>::ForwardType,
                    typename CallbackParamTraits<X4>::ForwardType,
                    typename CallbackParamTraits<X5>::ForwardType,
                    typename CallbackParamTraits<X6>::ForwardType);

                typedef R(UnboundRunType)(X3, X4, X5, X6);

                static R Run(BindStateBase* base,
                    typename CallbackParamTraits<X3>::ForwardType x3,
                    typename CallbackParamTraits<X4>::ForwardType x4,
                    typename CallbackParamTraits<X5>::ForwardType x5,
                    typename CallbackParamTraits<X6>::ForwardType x6) {
                        StorageType* storage = static_cast<StorageType*>(base);

                        typedef typename StorageType::Bound1UnwrapTraits Bound1UnwrapTraits;
                        typedef typename StorageType::Bound2UnwrapTraits Bound2UnwrapTraits;

                        typename Bound1UnwrapTraits::ForwardType x1 =
                            Bound1UnwrapTraits::Unwrap(storage->p1_);
                        typename Bound2UnwrapTraits::ForwardType x2 =
                            Bound2UnwrapTraits::Unwrap(storage->p2_);
                        return InvokeHelper<R,
                            typename StorageType::RunnableType,
                            void(typename Bound1UnwrapTraits::ForwardType,
                            typename Bound2UnwrapTraits::ForwardType,
                            typename CallbackParamTraits<X3>::ForwardType x3,
                            typename CallbackParamTraits<X4>::ForwardType x4,
                            typename CallbackParamTraits<X5>::ForwardType x5,
                            typename CallbackParamTraits<X6>::ForwardType x6)>
                            ::MakeItSo(storage->runnable_, CallbackForward(x1),
                            CallbackForward(x2), CallbackForward(x3),
                            CallbackForward(x4), CallbackForward(x5),
                            CallbackForward(x6));
                }
            };

            // Param 6 -> 3.
            template <typename StorageType, typename R,typename X1, typename X2,
                typename X3, typename X4, typename X5, typename X6>
            struct Invoker<3, StorageType, R(X1, X2, X3, X4, X5, X6)> {
                typedef R(RunType)(BindStateBase*,
                    typename CallbackParamTraits<X4>::ForwardType,
                    typename CallbackParamTraits<X5>::ForwardType,
                    typename CallbackParamTraits<X6>::ForwardType);

                typedef R(UnboundRunType)(X4, X5, X6);

                static R Run(BindStateBase* base,
                    typename CallbackParamTraits<X4>::ForwardType x4,
                    typename CallbackParamTraits<X5>::ForwardType x5,
                    typename CallbackParamTraits<X6>::ForwardType x6) {
                        StorageType* storage = static_cast<StorageType*>(base);

                        typedef typename StorageType::Bound1UnwrapTraits Bound1UnwrapTraits;
                        typedef typename StorageType::Bound2UnwrapTraits Bound2UnwrapTraits;
                        typedef typename StorageType::Bound3UnwrapTraits Bound3UnwrapTraits;

                        typename Bound1UnwrapTraits::ForwardType x1 =
                            Bound1UnwrapTraits::Unwrap(storage->p1_);
                        typename Bound2UnwrapTraits::ForwardType x2 =
                            Bound2UnwrapTraits::Unwrap(storage->p2_);
                        typename Bound3UnwrapTraits::ForwardType x3 =
                            Bound3UnwrapTraits::Unwrap(storage->p3_);
                        return InvokeHelper<R,
                            typename StorageType::RunnableType,
                            void(typename Bound1UnwrapTraits::ForwardType,
                            typename Bound2UnwrapTraits::ForwardType,
                            typename Bound3UnwrapTraits::ForwardType,
                            typename CallbackParamTraits<X4>::ForwardType x4,
                            typename CallbackParamTraits<X5>::ForwardType x5,
                            typename CallbackParamTraits<X6>::ForwardType x6)>
                            ::MakeItSo(storage->runnable_, CallbackForward(x1),
                            CallbackForward(x2), CallbackForward(x3),
                            CallbackForward(x4), CallbackForward(x5),
                            CallbackForward(x6));
                }
            };

            // Param 6 -> 2.
            template <typename StorageType, typename R,typename X1, typename X2,
                typename X3, typename X4, typename X5, typename X6>
            struct Invoker<4, StorageType, R(X1, X2, X3, X4, X5, X6)> {
                typedef R(RunType)(BindStateBase*,
                    typename CallbackParamTraits<X5>::ForwardType,
                    typename CallbackParamTraits<X6>::ForwardType);

                typedef R(UnboundRunType)(X5, X6);

                static R Run(BindStateBase* base,
                    typename CallbackParamTraits<X5>::ForwardType x5,
                    typename CallbackParamTraits<X6>::ForwardType x6) {
                        StorageType* storage = static_cast<StorageType*>(base);

                        typedef typename StorageType::Bound1UnwrapTraits Bound1UnwrapTraits;
                        typedef typename StorageType::Bound2UnwrapTraits Bound2UnwrapTraits;
                        typedef typename StorageType::Bound3UnwrapTraits Bound3UnwrapTraits;
                        typedef typename StorageType::Bound4UnwrapTraits Bound4UnwrapTraits;

                        typename Bound1UnwrapTraits::ForwardType x1 =
                            Bound1UnwrapTraits::Unwrap(storage->p1_);
                        typename Bound2UnwrapTraits::ForwardType x2 =
                            Bound2UnwrapTraits::Unwrap(storage->p2_);
                        typename Bound3UnwrapTraits::ForwardType x3 =
                            Bound3UnwrapTraits::Unwrap(storage->p3_);
                        typename Bound4UnwrapTraits::ForwardType x4 =
                            Bound4UnwrapTraits::Unwrap(storage->p4_);
                        return InvokeHelper<R,
                            typename StorageType::RunnableType,
                            void(typename Bound1UnwrapTraits::ForwardType,
                            typename Bound2UnwrapTraits::ForwardType,
                            typename Bound3UnwrapTraits::ForwardType,
                            typename Bound4UnwrapTraits::ForwardType,
                            typename CallbackParamTraits<X5>::ForwardType x5,
                            typename CallbackParamTraits<X6>::ForwardType x6)>
                            ::MakeItSo(storage->runnable_, CallbackForward(x1),
                            CallbackForward(x2), CallbackForward(x3),
                            CallbackForward(x4), CallbackForward(x5),
                            CallbackForward(x6));
                }
            };

            // Param 6 -> 1.
            template <typename StorageType, typename R,typename X1, typename X2,
                typename X3, typename X4, typename X5, typename X6>
            struct Invoker<5, StorageType, R(X1, X2, X3, X4, X5, X6)> {
                typedef R(RunType)(BindStateBase*,
                    typename CallbackParamTraits<X6>::ForwardType);

                typedef R(UnboundRunType)(X6);

                static R Run(BindStateBase* base,
                    typename CallbackParamTraits<X6>::ForwardType x6) {
                        StorageType* storage = static_cast<StorageType*>(base);

                        typedef typename StorageType::Bound1UnwrapTraits Bound1UnwrapTraits;
                        typedef typename StorageType::Bound2UnwrapTraits Bound2UnwrapTraits;
                        typedef typename StorageType::Bound3UnwrapTraits Bound3UnwrapTraits;
                        typedef typename StorageType::Bound4UnwrapTraits Bound4UnwrapTraits;
                        typedef typename StorageType::Bound5UnwrapTraits Bound5UnwrapTraits;

                        typename Bound1UnwrapTraits::ForwardType x1 =
                            Bound1UnwrapTraits::Unwrap(storage->p1_);
                        typename Bound2UnwrapTraits::ForwardType x2 =
                            Bound2UnwrapTraits::Unwrap(storage->p2_);
                        typename Bound3UnwrapTraits::ForwardType x3 =
                            Bound3UnwrapTraits::Unwrap(storage->p3_);
                        typename Bound4UnwrapTraits::ForwardType x4 =
                            Bound4UnwrapTraits::Unwrap(storage->p4_);
                        typename Bound5UnwrapTraits::ForwardType x5 =
                            Bound5UnwrapTraits::Unwrap(storage->p5_);
                        return InvokeHelper<R,
                            typename StorageType::RunnableType,
                            void(typename Bound1UnwrapTraits::ForwardType,
                            typename Bound2UnwrapTraits::ForwardType,
                            typename Bound3UnwrapTraits::ForwardType,
                            typename Bound4UnwrapTraits::ForwardType,
                            typename Bound5UnwrapTraits::ForwardType,
                            typename CallbackParamTraits<X6>::ForwardType x6)>
                            ::MakeItSo(storage->runnable_, CallbackForward(x1),
                            CallbackForward(x2), CallbackForward(x3),
                            CallbackForward(x4), CallbackForward(x5),
                            CallbackForward(x6));
                }
            };

            // Param 6 -> 0.
            template <typename StorageType, typename R,typename X1, typename X2,
                typename X3, typename X4, typename X5, typename X6>
            struct Invoker<6, StorageType, R(X1, X2, X3, X4, X5, X6)> {
                typedef R(RunType)(BindStateBase*);

                typedef R(UnboundRunType)();

                static R Run(BindStateBase* base) {
                    StorageType* storage = static_cast<StorageType*>(base);

                    typedef typename StorageType::Bound1UnwrapTraits Bound1UnwrapTraits;
                    typedef typename StorageType::Bound2UnwrapTraits Bound2UnwrapTraits;
                    typedef typename StorageType::Bound3UnwrapTraits Bound3UnwrapTraits;
                    typedef typename StorageType::Bound4UnwrapTraits Bound4UnwrapTraits;
                    typedef typename StorageType::Bound5UnwrapTraits Bound5UnwrapTraits;
                    typedef typename StorageType::Bound6UnwrapTraits Bound6UnwrapTraits;

                    typename Bound1UnwrapTraits::ForwardType x1 =
                        Bound1UnwrapTraits::Unwrap(storage->p1_);
                    typename Bound2UnwrapTraits::ForwardType x2 =
                        Bound2UnwrapTraits::Unwrap(storage->p2_);
                    typename Bound3UnwrapTraits::ForwardType x3 =
                        Bound3UnwrapTraits::Unwrap(storage->p3_);
                    typename Bound4UnwrapTraits::ForwardType x4 =
                        Bound4UnwrapTraits::Unwrap(storage->p4_);
                    typename Bound5UnwrapTraits::ForwardType x5 =
                        Bound5UnwrapTraits::Unwrap(storage->p5_);
                    typename Bound6UnwrapTraits::ForwardType x6 =
                        Bound6UnwrapTraits::Unwrap(storage->p6_);
                    return InvokeHelper<R,
                        typename StorageType::RunnableType,
                        void(typename Bound1UnwrapTraits::ForwardType,
                        typename Bound2UnwrapTraits::ForwardType,
                        typename Bound3UnwrapTraits::ForwardType,
                        typename Bound4UnwrapTraits::ForwardType,
                        typename Bound5UnwrapTraits::ForwardType,
                        typename Bound6UnwrapTraits::ForwardType)>
                        ::MakeItSo(storage->runnable_, CallbackForward(x1),
                        CallbackForward(x2), CallbackForward(x3),
                        CallbackForward(x4), CallbackForward(x5),
                        CallbackForward(x6));
                }
            };

            // Param 7 -> 7.
            template <typename StorageType, typename R,typename X1, typename X2,
                typename X3, typename X4, typename X5, typename X6, typename X7>
            struct Invoker<0, StorageType, R(X1, X2, X3, X4, X5, X6, X7)> {
                typedef R(RunType)(BindStateBase*,
                    typename CallbackParamTraits<X1>::ForwardType,
                    typename CallbackParamTraits<X2>::ForwardType,
                    typename CallbackParamTraits<X3>::ForwardType,
                    typename CallbackParamTraits<X4>::ForwardType,
                    typename CallbackParamTraits<X5>::ForwardType,
                    typename CallbackParamTraits<X6>::ForwardType,
                    typename CallbackParamTraits<X7>::ForwardType);

                typedef R(UnboundRunType)(X1, X2, X3, X4, X5, X6, X7);

                static R Run(BindStateBase* base,
                    typename CallbackParamTraits<X1>::ForwardType x1,
                    typename CallbackParamTraits<X2>::ForwardType x2,
                    typename CallbackParamTraits<X3>::ForwardType x3,
                    typename CallbackParamTraits<X4>::ForwardType x4,
                    typename CallbackParamTraits<X5>::ForwardType x5,
                    typename CallbackParamTraits<X6>::ForwardType x6,
                    typename CallbackParamTraits<X7>::ForwardType x7) {
                        StorageType* storage = static_cast<StorageType*>(base);

                        return InvokeHelper<R,
                            typename StorageType::RunnableType,
                            void(typename CallbackParamTraits<X1>::ForwardType x1,
                            typename CallbackParamTraits<X2>::ForwardType x2,
                            typename CallbackParamTraits<X3>::ForwardType x3,
                            typename CallbackParamTraits<X4>::ForwardType x4,
                            typename CallbackParamTraits<X5>::ForwardType x5,
                            typename CallbackParamTraits<X6>::ForwardType x6,
                            typename CallbackParamTraits<X7>::ForwardType x7)>
                            ::MakeItSo(storage->runnable_, CallbackForward(x1),
                            CallbackForward(x2), CallbackForward(x3),
                            CallbackForward(x4), CallbackForward(x5),
                            CallbackForward(x6), CallbackForward(x7));
                }
            };

            // Param 7 -> 6.
            template <typename StorageType, typename R,typename X1, typename X2,
                typename X3, typename X4, typename X5, typename X6, typename X7>
            struct Invoker<1, StorageType, R(X1, X2, X3, X4, X5, X6, X7)> {
                typedef R(RunType)(BindStateBase*,
                    typename CallbackParamTraits<X2>::ForwardType,
                    typename CallbackParamTraits<X3>::ForwardType,
                    typename CallbackParamTraits<X4>::ForwardType,
                    typename CallbackParamTraits<X5>::ForwardType,
                    typename CallbackParamTraits<X6>::ForwardType,
                    typename CallbackParamTraits<X7>::ForwardType);

                typedef R(UnboundRunType)(X2, X3, X4, X5, X6, X7);

                static R Run(BindStateBase* base,
                    typename CallbackParamTraits<X2>::ForwardType x2,
                    typename CallbackParamTraits<X3>::ForwardType x3,
                    typename CallbackParamTraits<X4>::ForwardType x4,
                    typename CallbackParamTraits<X5>::ForwardType x5,
                    typename CallbackParamTraits<X6>::ForwardType x6,
                    typename CallbackParamTraits<X7>::ForwardType x7) {
                        StorageType* storage = static_cast<StorageType*>(base);

                        typedef typename StorageType::Bound1UnwrapTraits Bound1UnwrapTraits;

                        typename Bound1UnwrapTraits::ForwardType x1 =
                            Bound1UnwrapTraits::Unwrap(storage->p1_);
                        return InvokeHelper<R,
                            typename StorageType::RunnableType,
                            void(typename Bound1UnwrapTraits::ForwardType,
                            typename CallbackParamTraits<X2>::ForwardType x2,
                            typename CallbackParamTraits<X3>::ForwardType x3,
                            typename CallbackParamTraits<X4>::ForwardType x4,
                            typename CallbackParamTraits<X5>::ForwardType x5,
                            typename CallbackParamTraits<X6>::ForwardType x6,
                            typename CallbackParamTraits<X7>::ForwardType x7)>
                            ::MakeItSo(storage->runnable_, CallbackForward(x1),
                            CallbackForward(x2), CallbackForward(x3),
                            CallbackForward(x4), CallbackForward(x5),
                            CallbackForward(x6), CallbackForward(x7));
                }
            };

            // Param 7 -> 5.
            template <typename StorageType, typename R,typename X1, typename X2,
                typename X3, typename X4, typename X5, typename X6, typename X7>
            struct Invoker<2, StorageType, R(X1, X2, X3, X4, X5, X6, X7)> {
                typedef R(RunType)(BindStateBase*,
                    typename CallbackParamTraits<X3>::ForwardType,
                    typename CallbackParamTraits<X4>::ForwardType,
                    typename CallbackParamTraits<X5>::ForwardType,
                    typename CallbackParamTraits<X6>::ForwardType,
                    typename CallbackParamTraits<X7>::ForwardType);

                typedef R(UnboundRunType)(X3, X4, X5, X6, X7);

                static R Run(BindStateBase* base,
                    typename CallbackParamTraits<X3>::ForwardType x3,
                    typename CallbackParamTraits<X4>::ForwardType x4,
                    typename CallbackParamTraits<X5>::ForwardType x5,
                    typename CallbackParamTraits<X6>::ForwardType x6,
                    typename CallbackParamTraits<X7>::ForwardType x7) {
                        StorageType* storage = static_cast<StorageType*>(base);

                        typedef typename StorageType::Bound1UnwrapTraits Bound1UnwrapTraits;
                        typedef typename StorageType::Bound2UnwrapTraits Bound2UnwrapTraits;

                        typename Bound1UnwrapTraits::ForwardType x1 =
                            Bound1UnwrapTraits::Unwrap(storage->p1_);
                        typename Bound2UnwrapTraits::ForwardType x2 =
                            Bound2UnwrapTraits::Unwrap(storage->p2_);
                        return InvokeHelper<R,
                            typename StorageType::RunnableType,
                            void(typename Bound1UnwrapTraits::ForwardType,
                            typename Bound2UnwrapTraits::ForwardType,
                            typename CallbackParamTraits<X3>::ForwardType x3,
                            typename CallbackParamTraits<X4>::ForwardType x4,
                            typename CallbackParamTraits<X5>::ForwardType x5,
                            typename CallbackParamTraits<X6>::ForwardType x6,
                            typename CallbackParamTraits<X7>::ForwardType x7)>
                            ::MakeItSo(storage->runnable_, CallbackForward(x1),
                            CallbackForward(x2), CallbackForward(x3),
                            CallbackForward(x4), CallbackForward(x5),
                            CallbackForward(x6), CallbackForward(x7));
                }
            };

            // Param 7 -> 4.
            template <typename StorageType, typename R,typename X1, typename X2,
                typename X3, typename X4, typename X5, typename X6, typename X7>
            struct Invoker<3, StorageType, R(X1, X2, X3, X4, X5, X6, X7)> {
                typedef R(RunType)(BindStateBase*,
                    typename CallbackParamTraits<X4>::ForwardType,
                    typename CallbackParamTraits<X5>::ForwardType,
                    typename CallbackParamTraits<X6>::ForwardType,
                    typename CallbackParamTraits<X7>::ForwardType);

                typedef R(UnboundRunType)(X4, X5, X6, X7);

                static R Run(BindStateBase* base,
                    typename CallbackParamTraits<X4>::ForwardType x4,
                    typename CallbackParamTraits<X5>::ForwardType x5,
                    typename CallbackParamTraits<X6>::ForwardType x6,
                    typename CallbackParamTraits<X7>::ForwardType x7) {
                        StorageType* storage = static_cast<StorageType*>(base);

                        typedef typename StorageType::Bound1UnwrapTraits Bound1UnwrapTraits;
                        typedef typename StorageType::Bound2UnwrapTraits Bound2UnwrapTraits;
                        typedef typename StorageType::Bound3UnwrapTraits Bound3UnwrapTraits;

                        typename Bound1UnwrapTraits::ForwardType x1 =
                            Bound1UnwrapTraits::Unwrap(storage->p1_);
                        typename Bound2UnwrapTraits::ForwardType x2 =
                            Bound2UnwrapTraits::Unwrap(storage->p2_);
                        typename Bound3UnwrapTraits::ForwardType x3 =
                            Bound3UnwrapTraits::Unwrap(storage->p3_);
                        return InvokeHelper<R,
                            typename StorageType::RunnableType,
                            void(typename Bound1UnwrapTraits::ForwardType,
                            typename Bound2UnwrapTraits::ForwardType,
                            typename Bound3UnwrapTraits::ForwardType,
                            typename CallbackParamTraits<X4>::ForwardType x4,
                            typename CallbackParamTraits<X5>::ForwardType x5,
                            typename CallbackParamTraits<X6>::ForwardType x6,
                            typename CallbackParamTraits<X7>::ForwardType x7)>
                            ::MakeItSo(storage->runnable_, CallbackForward(x1),
                            CallbackForward(x2), CallbackForward(x3),
                            CallbackForward(x4), CallbackForward(x5),
                            CallbackForward(x6), CallbackForward(x7));
                }
            };

            // Param 7 -> 3.
            template <typename StorageType, typename R,typename X1, typename X2,
                typename X3, typename X4, typename X5, typename X6, typename X7>
            struct Invoker<4, StorageType, R(X1, X2, X3, X4, X5, X6, X7)> {
                typedef R(RunType)(BindStateBase*,
                    typename CallbackParamTraits<X5>::ForwardType,
                    typename CallbackParamTraits<X6>::ForwardType,
                    typename CallbackParamTraits<X7>::ForwardType);

                typedef R(UnboundRunType)(X5, X6, X7);

                static R Run(BindStateBase* base,
                    typename CallbackParamTraits<X5>::ForwardType x5,
                    typename CallbackParamTraits<X6>::ForwardType x6,
                    typename CallbackParamTraits<X7>::ForwardType x7) {
                        StorageType* storage = static_cast<StorageType*>(base);

                        typedef typename StorageType::Bound1UnwrapTraits Bound1UnwrapTraits;
                        typedef typename StorageType::Bound2UnwrapTraits Bound2UnwrapTraits;
                        typedef typename StorageType::Bound3UnwrapTraits Bound3UnwrapTraits;
                        typedef typename StorageType::Bound4UnwrapTraits Bound4UnwrapTraits;

                        typename Bound1UnwrapTraits::ForwardType x1 =
                            Bound1UnwrapTraits::Unwrap(storage->p1_);
                        typename Bound2UnwrapTraits::ForwardType x2 =
                            Bound2UnwrapTraits::Unwrap(storage->p2_);
                        typename Bound3UnwrapTraits::ForwardType x3 =
                            Bound3UnwrapTraits::Unwrap(storage->p3_);
                        typename Bound4UnwrapTraits::ForwardType x4 =
                            Bound4UnwrapTraits::Unwrap(storage->p4_);
                        return InvokeHelper<R,
                            typename StorageType::RunnableType,
                            void(typename Bound1UnwrapTraits::ForwardType,
                            typename Bound2UnwrapTraits::ForwardType,
                            typename Bound3UnwrapTraits::ForwardType,
                            typename Bound4UnwrapTraits::ForwardType,
                            typename CallbackParamTraits<X5>::ForwardType x5,
                            typename CallbackParamTraits<X6>::ForwardType x6,
                            typename CallbackParamTraits<X7>::ForwardType x7)>
                            ::MakeItSo(storage->runnable_, CallbackForward(x1),
                            CallbackForward(x2), CallbackForward(x3),
                            CallbackForward(x4), CallbackForward(x5),
                            CallbackForward(x6), CallbackForward(x7));
                }
            };

            // Param 7 -> 2.
            template <typename StorageType, typename R,typename X1, typename X2,
                typename X3, typename X4, typename X5, typename X6, typename X7>
            struct Invoker<5, StorageType, R(X1, X2, X3, X4, X5, X6, X7)> {
                typedef R(RunType)(BindStateBase*,
                    typename CallbackParamTraits<X6>::ForwardType,
                    typename CallbackParamTraits<X7>::ForwardType);

                typedef R(UnboundRunType)(X6, X7);

                static R Run(BindStateBase* base,
                    typename CallbackParamTraits<X6>::ForwardType x6,
                    typename CallbackParamTraits<X7>::ForwardType x7) {
                        StorageType* storage = static_cast<StorageType*>(base);

                        typedef typename StorageType::Bound1UnwrapTraits Bound1UnwrapTraits;
                        typedef typename StorageType::Bound2UnwrapTraits Bound2UnwrapTraits;
                        typedef typename StorageType::Bound3UnwrapTraits Bound3UnwrapTraits;
                        typedef typename StorageType::Bound4UnwrapTraits Bound4UnwrapTraits;
                        typedef typename StorageType::Bound5UnwrapTraits Bound5UnwrapTraits;

                        typename Bound1UnwrapTraits::ForwardType x1 =
                            Bound1UnwrapTraits::Unwrap(storage->p1_);
                        typename Bound2UnwrapTraits::ForwardType x2 =
                            Bound2UnwrapTraits::Unwrap(storage->p2_);
                        typename Bound3UnwrapTraits::ForwardType x3 =
                            Bound3UnwrapTraits::Unwrap(storage->p3_);
                        typename Bound4UnwrapTraits::ForwardType x4 =
                            Bound4UnwrapTraits::Unwrap(storage->p4_);
                        typename Bound5UnwrapTraits::ForwardType x5 =
                            Bound5UnwrapTraits::Unwrap(storage->p5_);
                        return InvokeHelper<R,
                            typename StorageType::RunnableType,
                            void(typename Bound1UnwrapTraits::ForwardType,
                            typename Bound2UnwrapTraits::ForwardType,
                            typename Bound3UnwrapTraits::ForwardType,
                            typename Bound4UnwrapTraits::ForwardType,
                            typename Bound5UnwrapTraits::ForwardType,
                            typename CallbackParamTraits<X6>::ForwardType x6,
                            typename CallbackParamTraits<X7>::ForwardType x7)>
                            ::MakeItSo(storage->runnable_, CallbackForward(x1),
                            CallbackForward(x2), CallbackForward(x3),
                            CallbackForward(x4), CallbackForward(x5),
                            CallbackForward(x6), CallbackForward(x7));
                }
            };

            // Param 7 -> 1.
            template <typename StorageType, typename R,typename X1, typename X2,
                typename X3, typename X4, typename X5, typename X6, typename X7>
            struct Invoker<6, StorageType, R(X1, X2, X3, X4, X5, X6, X7)> {
                typedef R(RunType)(BindStateBase*,
                    typename CallbackParamTraits<X7>::ForwardType);

                typedef R(UnboundRunType)(X7);

                static R Run(BindStateBase* base,
                    typename CallbackParamTraits<X7>::ForwardType x7) {
                        StorageType* storage = static_cast<StorageType*>(base);

                        typedef typename StorageType::Bound1UnwrapTraits Bound1UnwrapTraits;
                        typedef typename StorageType::Bound2UnwrapTraits Bound2UnwrapTraits;
                        typedef typename StorageType::Bound3UnwrapTraits Bound3UnwrapTraits;
                        typedef typename StorageType::Bound4UnwrapTraits Bound4UnwrapTraits;
                        typedef typename StorageType::Bound5UnwrapTraits Bound5UnwrapTraits;
                        typedef typename StorageType::Bound6UnwrapTraits Bound6UnwrapTraits;

                        typename Bound1UnwrapTraits::ForwardType x1 =
                            Bound1UnwrapTraits::Unwrap(storage->p1_);
                        typename Bound2UnwrapTraits::ForwardType x2 =
                            Bound2UnwrapTraits::Unwrap(storage->p2_);
                        typename Bound3UnwrapTraits::ForwardType x3 =
                            Bound3UnwrapTraits::Unwrap(storage->p3_);
                        typename Bound4UnwrapTraits::ForwardType x4 =
                            Bound4UnwrapTraits::Unwrap(storage->p4_);
                        typename Bound5UnwrapTraits::ForwardType x5 =
                            Bound5UnwrapTraits::Unwrap(storage->p5_);
                        typename Bound6UnwrapTraits::ForwardType x6 =
                            Bound6UnwrapTraits::Unwrap(storage->p6_);
                        return InvokeHelper<R,
                            typename StorageType::RunnableType,
                            void(typename Bound1UnwrapTraits::ForwardType,
                            typename Bound2UnwrapTraits::ForwardType,
                            typename Bound3UnwrapTraits::ForwardType,
                            typename Bound4UnwrapTraits::ForwardType,
                            typename Bound5UnwrapTraits::ForwardType,
                            typename Bound6UnwrapTraits::ForwardType,
                            typename CallbackParamTraits<X7>::ForwardType x7)>
                            ::MakeItSo(storage->runnable_, CallbackForward(x1),
                            CallbackForward(x2), CallbackForward(x3),
                            CallbackForward(x4), CallbackForward(x5),
                            CallbackForward(x6), CallbackForward(x7));
                }
            };

            // Param 7 -> 0.
            template <typename StorageType, typename R,typename X1, typename X2,
                typename X3, typename X4, typename X5, typename X6, typename X7>
            struct Invoker<7, StorageType, R(X1, X2, X3, X4, X5, X6, X7)> {
                typedef R(RunType)(BindStateBase*);

                typedef R(UnboundRunType)();

                static R Run(BindStateBase* base) {
                    StorageType* storage = static_cast<StorageType*>(base);

                    typedef typename StorageType::Bound1UnwrapTraits Bound1UnwrapTraits;
                    typedef typename StorageType::Bound2UnwrapTraits Bound2UnwrapTraits;
                    typedef typename StorageType::Bound3UnwrapTraits Bound3UnwrapTraits;
                    typedef typename StorageType::Bound4UnwrapTraits Bound4UnwrapTraits;
                    typedef typename StorageType::Bound5UnwrapTraits Bound5UnwrapTraits;
                    typedef typename StorageType::Bound6UnwrapTraits Bound6UnwrapTraits;
                    typedef typename StorageType::Bound7UnwrapTraits Bound7UnwrapTraits;

                    typename Bound1UnwrapTraits::ForwardType x1 =
                        Bound1UnwrapTraits::Unwrap(storage->p1_);
                    typename Bound2UnwrapTraits::ForwardType x2 =
                        Bound2UnwrapTraits::Unwrap(storage->p2_);
                    typename Bound3UnwrapTraits::ForwardType x3 =
                        Bound3UnwrapTraits::Unwrap(storage->p3_);
                    typename Bound4UnwrapTraits::ForwardType x4 =
                        Bound4UnwrapTraits::Unwrap(storage->p4_);
                    typename Bound5UnwrapTraits::ForwardType x5 =
                        Bound5UnwrapTraits::Unwrap(storage->p5_);
                    typename Bound6UnwrapTraits::ForwardType x6 =
                        Bound6UnwrapTraits::Unwrap(storage->p6_);
                    typename Bound7UnwrapTraits::ForwardType x7 =
                        Bound7UnwrapTraits::Unwrap(storage->p7_);
                    return InvokeHelper<R,
                        typename StorageType::RunnableType,
                        void(typename Bound1UnwrapTraits::ForwardType,
                        typename Bound2UnwrapTraits::ForwardType,
                        typename Bound3UnwrapTraits::ForwardType,
                        typename Bound4UnwrapTraits::ForwardType,
                        typename Bound5UnwrapTraits::ForwardType,
                        typename Bound6UnwrapTraits::ForwardType,
                        typename Bound7UnwrapTraits::ForwardType)>
                        ::MakeItSo(storage->runnable_, CallbackForward(x1),
                        CallbackForward(x2), CallbackForward(x3),
                        CallbackForward(x4), CallbackForward(x5),
                        CallbackForward(x6), CallbackForward(x7));
                }
            };


            // BindState<>
            template <typename Runnable, typename RunType, typename BoundArgsType>
            struct BindState;

            template <typename Runnable, typename RunType>
            struct BindState<Runnable, RunType, void()> : public BindStateBase {
                typedef Runnable RunnableType;

                typedef Invoker<0, BindState, RunType> InvokerType;
                typedef typename InvokerType::UnboundRunType UnboundRunType;
                explicit BindState(const Runnable& runnable)
                    : runnable_(runnable) {
                }

                virtual ~BindState() {  }

                RunnableType runnable_;
            };

            template <typename Runnable, typename RunType, typename P1>
            struct BindState<Runnable, RunType, void(P1)> : public BindStateBase {
                typedef Runnable RunnableType;
                typedef Invoker<1, BindState, RunType> InvokerType;
                typedef typename InvokerType::UnboundRunType UnboundRunType;

                typedef UnwrapTraits<P1> Bound1UnwrapTraits;

                BindState(const Runnable& runnable, const P1& p1)
                    : runnable_(runnable),
                    p1_(p1) {
                        MaybeRefcount<HasIsMethodTag<Runnable>::value, P1>::AddRef(p1_);
                }

                virtual ~BindState() {    MaybeRefcount<HasIsMethodTag<Runnable>::value, P1>::Release(p1_);  }

                RunnableType runnable_;
                P1 p1_;
            };

            template <typename Runnable, typename RunType, typename P1, typename P2>
            struct BindState<Runnable, RunType, void(P1, P2)> : public BindStateBase {
                typedef Runnable RunnableType;
                typedef Invoker<2, BindState, RunType> InvokerType;
                typedef typename InvokerType::UnboundRunType UnboundRunType;

                typedef UnwrapTraits<P1> Bound1UnwrapTraits;
                typedef UnwrapTraits<P2> Bound2UnwrapTraits;

                BindState(const Runnable& runnable, const P1& p1, const P2& p2)
                    : runnable_(runnable),
                    p1_(p1),
                    p2_(p2) {
                        MaybeRefcount<HasIsMethodTag<Runnable>::value, P1>::AddRef(p1_);
                }

                virtual ~BindState() {    MaybeRefcount<HasIsMethodTag<Runnable>::value, P1>::Release(p1_);  }

                RunnableType runnable_;
                P1 p1_;
                P2 p2_;
            };

            template <typename Runnable, typename RunType, typename P1, typename P2,
                typename P3>
            struct BindState<Runnable, RunType, void(P1, P2, P3)> : public BindStateBase {
                typedef Runnable RunnableType;
                typedef Invoker<3, BindState, RunType> InvokerType;
                typedef typename InvokerType::UnboundRunType UnboundRunType;

                typedef UnwrapTraits<P1> Bound1UnwrapTraits;
                typedef UnwrapTraits<P2> Bound2UnwrapTraits;
                typedef UnwrapTraits<P3> Bound3UnwrapTraits;

                BindState(const Runnable& runnable, const P1& p1, const P2& p2, const P3& p3)
                    : runnable_(runnable),
                    p1_(p1),
                    p2_(p2),
                    p3_(p3) {
                        MaybeRefcount<HasIsMethodTag<Runnable>::value, P1>::AddRef(p1_);
                }

                virtual ~BindState() {    MaybeRefcount<HasIsMethodTag<Runnable>::value,
                    P1>::Release(p1_);  }

                RunnableType runnable_;
                P1 p1_;
                P2 p2_;
                P3 p3_;
            };

            template <typename Runnable, typename RunType, typename P1, typename P2,
                typename P3, typename P4>
            struct BindState<Runnable, RunType, void(P1, P2, P3,
                P4)> : public BindStateBase {
                    typedef Runnable RunnableType;
                    typedef Invoker<4, BindState, RunType> InvokerType;
                    typedef typename InvokerType::UnboundRunType UnboundRunType;

                    typedef UnwrapTraits<P1> Bound1UnwrapTraits;
                    typedef UnwrapTraits<P2> Bound2UnwrapTraits;
                    typedef UnwrapTraits<P3> Bound3UnwrapTraits;
                    typedef UnwrapTraits<P4> Bound4UnwrapTraits;

                    BindState(const Runnable& runnable, const P1& p1, const P2& p2, const P3& p3,
                        const P4& p4)
                        : runnable_(runnable),
                        p1_(p1),
                        p2_(p2),
                        p3_(p3),
                        p4_(p4) {
                            MaybeRefcount<HasIsMethodTag<Runnable>::value, P1>::AddRef(p1_);
                    }

                    virtual ~BindState() {    MaybeRefcount<HasIsMethodTag<Runnable>::value,
                        P1>::Release(p1_);  }

                    RunnableType runnable_;
                    P1 p1_;
                    P2 p2_;
                    P3 p3_;
                    P4 p4_;
            };

            template <typename Runnable, typename RunType, typename P1, typename P2,
                typename P3, typename P4, typename P5>
            struct BindState<Runnable, RunType, void(P1, P2, P3, P4,
                P5)> : public BindStateBase {
                    typedef Runnable RunnableType;
                    typedef Invoker<5, BindState, RunType> InvokerType;
                    typedef typename InvokerType::UnboundRunType UnboundRunType;

                    typedef UnwrapTraits<P1> Bound1UnwrapTraits;
                    typedef UnwrapTraits<P2> Bound2UnwrapTraits;
                    typedef UnwrapTraits<P3> Bound3UnwrapTraits;
                    typedef UnwrapTraits<P4> Bound4UnwrapTraits;
                    typedef UnwrapTraits<P5> Bound5UnwrapTraits;

                    BindState(const Runnable& runnable, const P1& p1, const P2& p2, const P3& p3,
                        const P4& p4, const P5& p5)
                        : runnable_(runnable),
                        p1_(p1),
                        p2_(p2),
                        p3_(p3),
                        p4_(p4),
                        p5_(p5) {
                            MaybeRefcount<HasIsMethodTag<Runnable>::value, P1>::AddRef(p1_);
                    }

                    virtual ~BindState() {    MaybeRefcount<HasIsMethodTag<Runnable>::value,
                        P1>::Release(p1_);  }

                    RunnableType runnable_;
                    P1 p1_;
                    P2 p2_;
                    P3 p3_;
                    P4 p4_;
                    P5 p5_;
            };

            template <typename Runnable, typename RunType, typename P1, typename P2,
                typename P3, typename P4, typename P5, typename P6>
            struct BindState<Runnable, RunType, void(P1, P2, P3, P4, P5,
                P6)> : public BindStateBase {
                    typedef Runnable RunnableType;
                    typedef Invoker<6, BindState, RunType> InvokerType;
                    typedef typename InvokerType::UnboundRunType UnboundRunType;

                    typedef UnwrapTraits<P1> Bound1UnwrapTraits;
                    typedef UnwrapTraits<P2> Bound2UnwrapTraits;
                    typedef UnwrapTraits<P3> Bound3UnwrapTraits;
                    typedef UnwrapTraits<P4> Bound4UnwrapTraits;
                    typedef UnwrapTraits<P5> Bound5UnwrapTraits;
                    typedef UnwrapTraits<P6> Bound6UnwrapTraits;

                    BindState(const Runnable& runnable, const P1& p1, const P2& p2, const P3& p3,
                        const P4& p4, const P5& p5, const P6& p6)
                        : runnable_(runnable),
                        p1_(p1),
                        p2_(p2),
                        p3_(p3),
                        p4_(p4),
                        p5_(p5),
                        p6_(p6) {
                            MaybeRefcount<HasIsMethodTag<Runnable>::value, P1>::AddRef(p1_);
                    }

                    virtual ~BindState() {    MaybeRefcount<HasIsMethodTag<Runnable>::value,
                        P1>::Release(p1_);  }

                    RunnableType runnable_;
                    P1 p1_;
                    P2 p2_;
                    P3 p3_;
                    P4 p4_;
                    P5 p5_;
                    P6 p6_;
            };

            template <typename Runnable, typename RunType, typename P1, typename P2,
                typename P3, typename P4, typename P5, typename P6, typename P7>
            struct BindState<Runnable, RunType, void(P1, P2, P3, P4, P5, P6,
                P7)> : public BindStateBase {
                    typedef Runnable RunnableType;
                    typedef Invoker<7, BindState, RunType> InvokerType;
                    typedef typename InvokerType::UnboundRunType UnboundRunType;

                    typedef UnwrapTraits<P1> Bound1UnwrapTraits;
                    typedef UnwrapTraits<P2> Bound2UnwrapTraits;
                    typedef UnwrapTraits<P3> Bound3UnwrapTraits;
                    typedef UnwrapTraits<P4> Bound4UnwrapTraits;
                    typedef UnwrapTraits<P5> Bound5UnwrapTraits;
                    typedef UnwrapTraits<P6> Bound6UnwrapTraits;
                    typedef UnwrapTraits<P7> Bound7UnwrapTraits;

                    BindState(const Runnable& runnable, const P1& p1, const P2& p2, const P3& p3,
                        const P4& p4, const P5& p5, const P6& p6, const P7& p7)
                        : runnable_(runnable),
                        p1_(p1),
                        p2_(p2),
                        p3_(p3),
                        p4_(p4),
                        p5_(p5),
                        p6_(p6),
                        p7_(p7) {
                            MaybeRefcount<HasIsMethodTag<Runnable>::value, P1>::AddRef(p1_);
                    }

                    virtual ~BindState() {    MaybeRefcount<HasIsMethodTag<Runnable>::value,
                        P1>::Release(p1_);  }

                    RunnableType runnable_;
                    P1 p1_;
                    P2 p2_;
                    P3 p3_;
                    P4 p4_;
                    P5 p5_;
                    P6 p6_;
                    P7 p7_;
            };

        } // namespace internal
    } // namespace utility
} // namespace tthread

#endif // __BIND_INTERNAL_H__
