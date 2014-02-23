#ifndef __BIND_H__
#define __BIND_H__

#include "bind_internal.h"
#include "callback_internal.h"

#ifdef _DETECT_MEM_LEAK
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
static struct Dbg_Mem_Leak_Check
{
    Dbg_Mem_Leak_Check()
    {
        _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
    }
} s_Dbg_Mem_Leak_Check;
#endif
#endif  // _DETECT_MEM_LEAK


namespace tthread {
    template <typename Functor>
    utility::Callback<
        typename utility::internal::BindState<
        typename utility::internal::FunctorTraits<Functor>::RunnableType,
        typename utility::internal::FunctorTraits<Functor>::RunType,
        void()>
        ::UnboundRunType>
        Bind(Functor functor) {
            typedef typename utility::internal::FunctorTraits<Functor>::RunnableType RunnableType;
            typedef typename utility::internal::FunctorTraits<Functor>::RunType RunType;

            typedef utility::internal::BindState<RunnableType, RunType, void()> BindState;

            return utility::Callback<typename BindState::UnboundRunType>(
                new BindState(utility::internal::MakeRunnable(functor)));
    }

    template <typename Functor, typename P1>
    utility::Callback<
        typename utility::internal::BindState<
        typename utility::internal::FunctorTraits<Functor>::RunnableType,
        typename utility::internal::FunctorTraits<Functor>::RunType,
        void(typename utility::internal::CallbackParamTraits<P1>::StorageType)>
        ::UnboundRunType>
        Bind(Functor functor, const P1& p1) {
            typedef typename utility::internal::FunctorTraits<Functor>::RunnableType RunnableType;
            typedef typename utility::internal::FunctorTraits<Functor>::RunType RunType;

            typedef utility::internal::BindState<RunnableType, RunType,
                void(typename utility::internal::CallbackParamTraits<P1>::StorageType)> BindState;

            return utility::Callback<typename BindState::UnboundRunType>(
                new BindState(utility::internal::MakeRunnable(functor), p1));
    }

    template <typename Functor, typename P1, typename P2>
    utility::Callback<
        typename utility::internal::BindState<
        typename utility::internal::FunctorTraits<Functor>::RunnableType,
        typename utility::internal::FunctorTraits<Functor>::RunType,
        void(typename utility::internal::CallbackParamTraits<P1>::StorageType,
        typename utility::internal::CallbackParamTraits<P2>::StorageType)>
        ::UnboundRunType>
        Bind(Functor functor, const P1& p1, const P2& p2) {
            typedef typename utility::internal::FunctorTraits<Functor>::RunnableType RunnableType;
            typedef typename utility::internal::FunctorTraits<Functor>::RunType RunType;

            typedef utility::internal::BindState<RunnableType, RunType,
                void(typename utility::internal::CallbackParamTraits<P1>::StorageType,
                typename utility::internal::CallbackParamTraits<P2>::StorageType)> BindState;


            return utility::Callback<typename BindState::UnboundRunType>(new BindState(utility::internal::MakeRunnable(functor), p1, p2));
    }

    template <typename Functor, typename P1, typename P2, typename P3>
    utility::Callback<
        typename utility::internal::BindState<
        typename utility::internal::FunctorTraits<Functor>::RunnableType,
        typename utility::internal::FunctorTraits<Functor>::RunType,
        void(typename utility::internal::CallbackParamTraits<P1>::StorageType,
        typename utility::internal::CallbackParamTraits<P2>::StorageType,
        typename utility::internal::CallbackParamTraits<P3>::StorageType)>
        ::UnboundRunType>
        Bind(Functor functor, const P1& p1, const P2& p2, const P3& p3) {
            typedef typename utility::internal::FunctorTraits<Functor>::RunnableType RunnableType;
            typedef typename utility::internal::FunctorTraits<Functor>::RunType RunType;

            typedef utility::internal::BindState<RunnableType, RunType,
                void(typename utility::internal::CallbackParamTraits<P1>::StorageType,
                typename utility::internal::CallbackParamTraits<P2>::StorageType,
                typename utility::internal::CallbackParamTraits<P3>::StorageType)> BindState;


            return utility::Callback<typename BindState::UnboundRunType>(
                new BindState(utility::internal::MakeRunnable(functor), p1, p2, p3));
    }

    template <typename Functor, typename P1, typename P2, typename P3, typename P4>
    utility::Callback<
        typename utility::internal::BindState<
        typename utility::internal::FunctorTraits<Functor>::RunnableType,
        typename utility::internal::FunctorTraits<Functor>::RunType,
        void(typename utility::internal::CallbackParamTraits<P1>::StorageType,
        typename utility::internal::CallbackParamTraits<P2>::StorageType,
        typename utility::internal::CallbackParamTraits<P3>::StorageType,
        typename utility::internal::CallbackParamTraits<P4>::StorageType)>
        ::UnboundRunType>
        Bind(Functor functor, const P1& p1, const P2& p2, const P3& p3, const P4& p4) {
            typedef typename utility::internal::FunctorTraits<Functor>::RunnableType RunnableType;
            typedef typename utility::internal::FunctorTraits<Functor>::RunType RunType;

            typedef utility::internal::BindState<RunnableType, RunType,
                void(typename utility::internal::CallbackParamTraits<P1>::StorageType,
                typename utility::internal::CallbackParamTraits<P2>::StorageType,
                typename utility::internal::CallbackParamTraits<P3>::StorageType,
                typename utility::internal::CallbackParamTraits<P4>::StorageType)> BindState;


            return utility::Callback<typename BindState::UnboundRunType>(
                new BindState(utility::internal::MakeRunnable(functor), p1, p2, p3, p4));
    }

    template <typename Functor, typename P1, typename P2, typename P3, typename P4,
        typename P5>
        utility::Callback<
        typename utility::internal::BindState<
        typename utility::internal::FunctorTraits<Functor>::RunnableType,
        typename utility::internal::FunctorTraits<Functor>::RunType,
        void(typename utility::internal::CallbackParamTraits<P1>::StorageType,
        typename utility::internal::CallbackParamTraits<P2>::StorageType,
        typename utility::internal::CallbackParamTraits<P3>::StorageType,
        typename utility::internal::CallbackParamTraits<P4>::StorageType,
        typename utility::internal::CallbackParamTraits<P5>::StorageType)>
        ::UnboundRunType>
        Bind(Functor functor, const P1& p1, const P2& p2, const P3& p3, const P4& p4,
        const P5& p5) {
            typedef typename utility::internal::FunctorTraits<Functor>::RunnableType RunnableType;
            typedef typename utility::internal::FunctorTraits<Functor>::RunType RunType;

            typedef utility::internal::BindState<RunnableType, RunType,
                void(typename utility::internal::CallbackParamTraits<P1>::StorageType,
                typename utility::internal::CallbackParamTraits<P2>::StorageType,
                typename utility::internal::CallbackParamTraits<P3>::StorageType,
                typename utility::internal::CallbackParamTraits<P4>::StorageType,
                typename utility::internal::CallbackParamTraits<P5>::StorageType)> BindState;


            return utility::Callback<typename BindState::UnboundRunType>(
                new BindState(utility::internal::MakeRunnable(functor), p1, p2, p3, p4, p5));
    }

    template <typename Functor, typename P1, typename P2, typename P3, typename P4,
        typename P5, typename P6>
        utility::Callback<
        typename utility::internal::BindState<
        typename utility::internal::FunctorTraits<Functor>::RunnableType,
        typename utility::internal::FunctorTraits<Functor>::RunType,
        void(typename utility::internal::CallbackParamTraits<P1>::StorageType,
        typename utility::internal::CallbackParamTraits<P2>::StorageType,
        typename utility::internal::CallbackParamTraits<P3>::StorageType,
        typename utility::internal::CallbackParamTraits<P4>::StorageType,
        typename utility::internal::CallbackParamTraits<P5>::StorageType,
        typename utility::internal::CallbackParamTraits<P6>::StorageType)>
        ::UnboundRunType>
        Bind(Functor functor, const P1& p1, const P2& p2, const P3& p3, const P4& p4,
        const P5& p5, const P6& p6) {
            typedef typename utility::internal::FunctorTraits<Functor>::RunnableType RunnableType;
            typedef typename utility::internal::FunctorTraits<Functor>::RunType RunType;

            typedef utility::internal::BindState<RunnableType, RunType,
                void(typename utility::internal::CallbackParamTraits<P1>::StorageType,
                typename utility::internal::CallbackParamTraits<P2>::StorageType,
                typename utility::internal::CallbackParamTraits<P3>::StorageType,
                typename utility::internal::CallbackParamTraits<P4>::StorageType,
                typename utility::internal::CallbackParamTraits<P5>::StorageType,
                typename utility::internal::CallbackParamTraits<P6>::StorageType)> BindState;


            return utility::Callback<typename BindState::UnboundRunType>(
                new BindState(utility::internal::MakeRunnable(functor), p1, p2, p3, p4, p5, p6));
    }

    template <typename Functor, typename P1, typename P2, typename P3, typename P4,
        typename P5, typename P6, typename P7>
        utility::Callback<
        typename utility::internal::BindState<
        typename utility::internal::FunctorTraits<Functor>::RunnableType,
        typename utility::internal::FunctorTraits<Functor>::RunType,
        void(typename utility::internal::CallbackParamTraits<P1>::StorageType,
        typename utility::internal::CallbackParamTraits<P2>::StorageType,
        typename utility::internal::CallbackParamTraits<P3>::StorageType,
        typename utility::internal::CallbackParamTraits<P4>::StorageType,
        typename utility::internal::CallbackParamTraits<P5>::StorageType,
        typename utility::internal::CallbackParamTraits<P6>::StorageType,
        typename utility::internal::CallbackParamTraits<P7>::StorageType)>
        ::UnboundRunType>
        Bind(Functor functor, const P1& p1, const P2& p2, const P3& p3, const P4& p4,
        const P5& p5, const P6& p6, const P7& p7) {
            typedef typename utility::internal::FunctorTraits<Functor>::RunnableType RunnableType;
            typedef typename utility::internal::FunctorTraits<Functor>::RunType RunType;

            typedef utility::internal::BindState<RunnableType, RunType,
                void(typename utility::internal::CallbackParamTraits<P1>::StorageType,
                typename utility::internal::CallbackParamTraits<P2>::StorageType,
                typename utility::internal::CallbackParamTraits<P3>::StorageType,
                typename utility::internal::CallbackParamTraits<P4>::StorageType,
                typename utility::internal::CallbackParamTraits<P5>::StorageType,
                typename utility::internal::CallbackParamTraits<P6>::StorageType,
                typename utility::internal::CallbackParamTraits<P7>::StorageType)> BindState;


            return utility::Callback<typename BindState::UnboundRunType>(
                new BindState(utility::internal::MakeRunnable(functor), p1, p2, p3, p4, p5, p6,
                p7));
    }

}  // namespace tthread

#endif // __BIND_H__
