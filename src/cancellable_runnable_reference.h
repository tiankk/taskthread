/**
 *    @file:        cancellable_runnable_reference.h
 *    @author:      tiankk <tiankk@gmail.com>
 *    @created:     2014/02/13
 *    @brief:       Reference wrapper class for cancel task object.
 */

#ifndef __CANCELLABLE_RUNABLE_REFERENCE_H__
#define __CANCELLABLE_RUNABLE_REFERENCE_H__

#include "scoped_ref_ptr.h"
#include "ref_ptr_flag.h"
#include "autolock.h"
#include <tchar.h>


namespace tthread
{
    namespace utility
    {
        class CancellableRunnable;
    }

    class CancellableRunnableReference
    {
    public:
        CancellableRunnableReference();
        CancellableRunnableReference(ScopedRefPtr<utility::RefPtrFlag> flag, utility::CancellableRunnable * ptr);

        /**
         *    @brief:        Try to cancel this task.
         *    @method:       TryCancel
         *    @return:       bool if success, return true, otherwise false.
         */
        bool TryCancel();

    private:
        ScopedRefPtr<utility::RefPtrFlag> flag_;
        utility::CancellableRunnable * ptr_;
    };
} // namespace tthread

#endif // __CANCELLABLE_RUNABLE_REFERENCE_H__
