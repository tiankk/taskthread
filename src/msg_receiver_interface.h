/**
 *    @file:        msg_receiver_interface.h
 *    @author:      tiankk <tiankk@gmail.com>
 *    @created:     2014/02/13
 */

#ifndef __MSG_RECEIVER_INTERFACE_H__
#define __MSG_RECEIVER_INTERFACE_H__

#include <Windows.h>


namespace tthread
{
    namespace utility
    {
        /**
         * @class IMsgReceiver
         * @brief interface for tthread::utility::Notifier()
         */
        struct IMsgReceiver
        {
            virtual ~IMsgReceiver(void){};
            virtual void OnMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
        };
    } // namespace utility
} // namespace tthread

#endif // __MSG_RECEIVER_INTERFACE_H__
