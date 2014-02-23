/**
 *    @file:        runonce_thread_pool.h
 *    @author:      tiankk <tiankk@gmail.com>
 *    @created:     2014/02/13
 */

#ifndef __RUNONCE_THREAD_POOL_H__
#define __RUNONCE_THREAD_POOL_H__

#include "autolock.h"
#include "task_thread.h"
#include "scoped_ref_ptr.h"
#include <list>


namespace tthread
{
    namespace utility
    {
        class TaskThread;

        /**
        *    @biref:    manage runonce threads
        */
        class RunOnceThreadPool : public RefCountedThreadSafe<RunOnceThreadPool>
        {
        public:
            ~RunOnceThreadPool();

            //////////////////////////////////////////////////////////////////////////
            /// for runonce thread
        public:
            void ClearAll();

            void WaitAll(unsigned int msec = INFINITE);

            ScopedRefPtr<TaskThread> GetThread();

        private:
            std::list< ScopedRefPtr<TaskThread> > lst_;
            AutoLock lock_;
        };
    } // namespace utility
} // namespace tthread

#endif // __RUNONCE_THREAD_POOL_H__
