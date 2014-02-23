/**
 *    @file:        const_define.h
 *    @author:      tiankk <tiankk@gmail.com>
 *    @created:     2014/02/13
 *    @brief:       Define static thread id.
 */

#ifndef __CONST_DEFINE_H__
#define __CONST_DEFINE_H__


namespace tthread
{
    enum THREAD_ID
    {
        STATIC_THREAD_START,  // add static thread id below
        DEFAULT,
        // for test
        TEST_MONSTER,
        TEST_CANNON,
        STATIC_THREAD_END, // add static thread id above
        RUNONCE = 1024
    };
}

#endif // __CONST_DEFINE_H__
