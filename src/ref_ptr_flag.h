/**
 *    @file:        ref_ptr_flag.h
 *    @author:      tiankk <tiankk@gmail.com>
 *    @created:     2014/02/13
 */

#ifndef __REF_PTR_FLAG_H__
#define __REF_PTR_FLAG_H__

#include "scoped_ref_ptr.h"
#include "autolock.h"
#include <tchar.h>


namespace tthread {
    namespace utility {
        /**
         *    @brief:  counted flag
         */
        class RefPtrFlag : public RefCountedThreadSafe<RefPtrFlag>
        {
        public:
            RefPtrFlag()
                : is_valid_(true)
            {}

            bool IsValid()
            {
                return is_valid_;
            };

            void Invalidate()
            {
                InterlockedExchange(reinterpret_cast<volatile LONG*>(&is_valid_), static_cast<LONG>(0));
            }

            AutoLock lock_;
        private:
            volatile bool is_valid_;
        };

        /**
         *    @brief:  base class for supporting counted flag
         */
        class HasRefPtrFlag
        {
        public:
            HasRefPtrFlag()
                : flag_(new RefPtrFlag)
            {}

            ScopedRefPtr<RefPtrFlag> GetRefPtrFlag() const
            {
                return flag_;
            }

        private:
            ScopedRefPtr<RefPtrFlag> flag_;
        };
    } // namespace utility
} // namespace tthread

#endif // __REF_PTR_FLAG_H__
