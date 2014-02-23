/**
 *    @file:        notifier_pool.h
 *    @author:      tiankk <tiankk@gmail.com>
 *    @created:     2014/02/13
 */

#ifndef __NOTIFIER_POOL_H__
#define __NOTIFIER_POOL_H__

#include "scoped_ref_ptr.h"
#include "notifier.h"
#include <map>


namespace tthread
{
    namespace utility
    {
        struct IMsgReceiver;
        /**
        *    @biref:    manage notifiers
        */
        class NotifierPool : public RefCountedThreadSafe<NotifierPool>
        {
        public:
            /**
             *    @brief:        Register message receiver, and get window handle and message id.
             *    @method:       Register
             *    @param:        IMsgReceiver * msg_evt     receiver pointer
             *    @param:        HWND & wnd                 (out) window handle which will receive message
             *    @param:        UINT & msg                 (out) window message which should be sent to the receiver window
             *    @param:        unsigned int id            id for notifier, if 0, default value is ::GetCurrentThreadId().
             *    @return:       void
             */
            void Register(IMsgReceiver* msg_evt, HWND& wnd, UINT& msg, unsigned int id = 0);

            void UnRegister(IMsgReceiver* msg_evt);

        private:
            std::map<unsigned int, ScopedRefPtr<Notifier> > map_;
            AutoLock lock_;
        };
    } // namespace utility
} // namespace tthread

#endif // __NOTIFIER_POOL_H__
