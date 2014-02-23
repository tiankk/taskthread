/**
 *    @file:        runnable_base.h
 *    @author:      tiankk <tiankk@gmail.com>
 *    @created:     2014/02/13
 */

#ifndef __AsyncRunnable_H__
#define __AsyncRunnable_H__


namespace tthread
{
    namespace utility
    {
        namespace runnable
        {
            extern volatile long id_;
            long IDAtomicInc();
        } // namespace runnable

        class RunnableBase
        {
        public:
            RunnableBase()
                : id_(0)
            {
                id_ = runnable::IDAtomicInc();
            }

            long GetID()
            {
                return id_;
            }


            /**
             *    @brief:        Run task, called by tthread::TaskThread.
             *    @method:       __Do
             *    @return:       void
             */
            virtual void __Do() = 0;

            /**
             *    @brief:        Commit task.
             *    @method:       Run
             *    @return:       void
             */
            virtual void Run() = 0;

        protected:
            /// task id, global unique
            long id_;
        };
    } // namespace utility
}// namespace tthread

#endif //__AsyncRunnable_H__
