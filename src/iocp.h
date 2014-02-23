/**
 *    @file:        iocp.h
 *    @author:      tiankk <tiankk@gmail.com>
 *    @created:     2014/02/13
 */

#ifndef __IOCP_H__
#define __IOCP_H__

#include <Windows.h>

namespace tthread
{
    namespace utility
    {
        /**
         *    @brief:  IOCP wrapper class
         */
        class CIOCP {
        public:
            CIOCP(int max_concurrency = -1)
                : iocp_(NULL)
            {
                if (max_concurrency != -1)
                    Create(max_concurrency);
            }

            ~CIOCP()
            {
                if (iocp_ != NULL)
                    CloseHandle(iocp_);
            }

            BOOL Close()
            {
                BOOL result = CloseHandle(iocp_);
                iocp_ = NULL;
                return result;
            }

            BOOL Create(int max_concurrency = 0)
            {
                iocp_ = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, max_concurrency);
                return (iocp_ != NULL);
            }

            BOOL AssociateDevice(HANDLE device, ULONG_PTR comp_key)
            {
                return (CreateIoCompletionPort(device, iocp_, comp_key, 0) == iocp_);
            }

            BOOL PostStatus(ULONG_PTR comp_key, DWORD num_bytes = 0, OVERLAPPED* po = NULL)
            {
                return PostQueuedCompletionStatus(iocp_, num_bytes, comp_key, po);
            }

            BOOL GetStatus(ULONG_PTR* ptr_comp_key, PDWORD ptr_num_bytes, OVERLAPPED** ppo, DWORD milliseconds = INFINITE)
            {
                return GetQueuedCompletionStatus(iocp_, ptr_num_bytes, ptr_comp_key, ppo, milliseconds);
            }

        private:
            HANDLE iocp_;
        };

    } // namespace utility
} // namespace tthread

#endif // __IOCP_H__
