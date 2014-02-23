/**
 *    @file:        thread_pool.h
 *    @author:      tiankk <tiankk@gmail.com>
 *    @created:     2014/02/13
 */

#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include "static_thread_pool.h"
#include "runonce_thread_pool.h"
#include "notifier_pool.h"
#include "task_thread.h"

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


namespace tthread
{
    namespace utility
    {
        /**
        *    @biref:    interfaces for thread pools management
        */
        class ThreadPool
        {
        public:
            /**
            *    @brief:       Get TaskThread object pointer.
            *    @method:      GetThread
            *    @param:       THREAD_ID id
            *    @return:      TaskThread&
            */
            static TaskThread* GetThread(THREAD_ID id)
            {
                if (id == RUNONCE)
                {
                    return runonce_pool_->GetThread();
                }
                return static_pool_->GetThread(id);
            }

            /**
            *    @brief:       Get static thread pointer.
            *    @method:      GetStaticThread
            *    @param:       THREAD_ID id
            *    @return:      TaskThread&
            */
            static TaskThread* GetStaticThread(THREAD_ID id)
            {
                return static_pool_->GetThread(id);
            }

            /**
            *    @brief:       Get runonce thread pinter.
            *    @method:      GetRunOnceThread
            *    @return:      TaskThread&
            */
            static TaskThread* GetRunOnceThread()
            {
                return runonce_pool_->GetThread();
            }

            /**
            *    @brief:       Register MsgReceiver and get window handle and window message id
            *    @method:      RegisterMsgReceiver
            *    @param        IMsgReceiver* msg_evt
            *    @param        HWND& wnd
            *    @param        UINT& msg
            *    @param        unsigned int id      id of notifier. if id is 0, real id is ::GetCurrentThreadId().
            *    @return:      void
            */
            static void RegisterMsgReceiver(IMsgReceiver* msg_evt, HWND& wnd, UINT& msg, unsigned int id = 0)
            {
                notifier_pool_->Register(msg_evt, wnd, msg, id);
            }

            /**
            *    @brief:       Unregister MsgReceiver
            *    @method:      UnRegisterMsgReceiver
            *    @return:      void
            */
            static void UnRegisterMsgReceiver(IMsgReceiver* msg_evt)
            {
                notifier_pool_->UnRegister(msg_evt);
            }

            /**
            *    @brief:       Send quit message to all static threads.
            *    @method:      QuitStaticThread
            *    @return:      void
            */
            static void QuitStaticThread()
            {
                static_pool_->QuitAll();
            }

            /**
            *    @brief:       Send emergency quit message to all static threads.
            *    @method:      EmergencyQuitStaticThread
            *    @return:      void
            */
            static void EmergencyQuitStaticThread()
            {
                static_pool_->EmergencyQuitAll();
            }

            /**
            *    @brief:       Wait for quitting.
            *    @method:      WaitAll
            *    @param:       unsigned int msec    waiting time
            *    @return:      void
            */
            static void WaitAll(unsigned int msec = INFINITE)
            {
                static_pool_->WaitAll(msec);
                runonce_pool_->WaitAll(msec);
            }

        private:
            static ScopedRefPtr<StaticThreadPool> static_pool_;
            static ScopedRefPtr<RunOnceThreadPool> runonce_pool_;
            static ScopedRefPtr<NotifierPool> notifier_pool_;
        };
    } // namespace utility
} // namespace tthread
#endif // __THREADPOOL_H__
