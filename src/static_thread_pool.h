/**
 *    @file:        static_thread_pool.h
 *    @author:      tiankk <tiankk@gmail.com>
 *    @created:     2014/02/13
 */

#ifndef __STATIC_THREAD_POOL_H__
#define __STATIC_THREAD_POOL_H__

#include "autolock.h"
#include "task_thread.h"
#include "const_define.h"
#include "scoped_ref_ptr.h"


namespace tthread
{
    namespace utility
    {
        /**
        *    @biref:    static thread pool
        */
        class StaticThreadPool : public RefCountedThreadSafe<StaticThreadPool>
        {
        public:
            /**
            *    @brief:       Get TaskThread pointer.
            *    @method:      GetThread
            *    @param:       THREAD_ID id
            *    @return:      TaskThread&
            */
            TaskThread* GetThread(THREAD_ID id);

            /**
             *    @brief:        Notify all static threads to run all queued tasks then quit.
             *    @method:       QuitAll
             *    @return:       void
             */
            void QuitAll();

            /**
            *    @brief:       Notify all static threads to emergency quit without run queued tasks.
            *    @method:      EmergencyQuitAll
            *    @return:      void
            */
            void EmergencyQuitAll();

            /**
            *    @brief:       Wait all static thread.
            *    @method:      WaitAll
            *    @param:       unsigned int msec    waiting time, default is INFINITE
            *    @return:      void
            */
            void WaitAll(unsigned int msec = INFINITE);

        private:
            unsigned int IdToIndex(unsigned int id);

            unsigned int IndexToId(unsigned int index);

        private:
            // static threads pool
            ScopedRefPtr<TaskThread> pool_[STATIC_THREAD_END - STATIC_THREAD_START - 1];

            // static thread access locks
            AutoLock pool_locks_[STATIC_THREAD_END - STATIC_THREAD_START - 1];
        };
    } // namespace utility
} // namespace tthread

#endif // __STATIC_THREAD_POOL_H__
