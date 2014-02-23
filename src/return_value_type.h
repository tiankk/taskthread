/**
 *    @file:        return_value_type.h
 *    @author:      tiankk <tiankk@gmail.com>
 *    @created:     2014/02/13
 *    @brief:       Return value types and context parameter base struct.
 */

#ifndef __RETURNVALUE_H__
#define __RETURNVALUE_H__

#include "def.h"
#include "scoped_ref_ptr.h"


namespace tthread
{
    /**
     *    @brief:  Derived from this to support context parameter storage.
     */
    struct ReturnParam : public RefCountedThreadSafe<ReturnParam>
    {
        virtual ~ReturnParam() = 0
        {};
    };

    /**
     *    @brief:  Base class for return value.
     */
    struct ReturnValue : public RefCountedThreadSafe<ReturnValue>
    {
        ReturnValue()
            : default_ret_(0)
            , id_(0)
        {}
        virtual ~ReturnValue(){};

        int default_ret_;   // default return value member
        long id_;           // id for task
        ScopedRefPtr<ReturnParam> param_;   // context parameter
    };

    /**
     *    @brief:  String return value type.
     */
    struct StringReturnValue : public ReturnValue
    {
        tstring string_ret_;
    };

    /**
     *    @brief:  Integer return value type.
     */
    struct IntRetrunValue : public ReturnValue
    {
        IntRetrunValue()
            : int_val_(0)
        {}

        int int_val_;
    };
} // namespace tthread

#endif // __RETURNVALUE_H__
