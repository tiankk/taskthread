#ifndef __SCOPED_REF_PTR_H__
#define __SCOPED_REF_PTR_H__

#include "ref_counted.h"


// Usage:
//   class MyFoo : public RefCountedThreadSafe<MyFoo> {
//    ...
//   };
//
//   void some_function() {
//     ScopedRefPtr<MyFoo> foo = new MyFoo();
//     foo->Method(param);
//     // |foo| is released when this function returns
//   }
//
//   void some_other_function() {
//     ScopedRefPtr<MyFoo> foo = new MyFoo();
//     ...
//     foo = NULL;  // explicitly releases |foo|
//     ...
//     if (foo)
//       foo->Method(param);
//   }
//
// Swap:
//
//   {
//     ScopedRefPtr<MyFoo> a = new MyFoo();
//     ScopedRefPtr<MyFoo> b;
//
//     b.swap(a);
//     // now, |b| references the MyFoo object, and |a| references NULL.
//   }
//
// Assignment:
//
//   {
//     ScopedRefPtr<MyFoo> a = new MyFoo();
//     ScopedRefPtr<MyFoo> b;
//
//     b = a;
//     // now, |a| and |b| each own a reference to the same MyFoo object.
//   }
//
namespace tthread {
    template <class T>
    class ScopedRefPtr
    {
    public:
        ScopedRefPtr() : ptr_(NULL)
        {
        }

        ScopedRefPtr(T* p) : ptr_(p)
        {
            if (ptr_)
                ptr_->AddRef();
        }

        ScopedRefPtr(const ScopedRefPtr<T>& r) : ptr_(r.ptr_)
        {
            if (ptr_)
                ptr_->AddRef();
        }

        template <typename U>
        ScopedRefPtr(const ScopedRefPtr<U>& r) : ptr_(r.get())
        {
            if (ptr_)
                ptr_->AddRef();
        }

        ~ScopedRefPtr()
        {
            if (ptr_)
                ptr_->Release();
        }

        T* get() const { return ptr_; }
        operator T*() const { return ptr_; }
        T* operator->() const
        {
            return ptr_;
        }

        T* release()
        {
            T* retVal = ptr_;
            ptr_ = NULL;
            return retVal;
        }

        ScopedRefPtr<T>& operator=(T* p)
        {
            // AddRef first so that self assignment should work
            if (p)
                p->AddRef();
            T* old_ptr = ptr_;
            ptr_ = p;
            if (old_ptr)
                old_ptr->Release();
            return *this;
        }

        ScopedRefPtr<T>& operator=(const ScopedRefPtr<T>& r)
        {
            return *this = r.ptr_;
        }

        template <typename U>
        ScopedRefPtr<T>& operator=(const ScopedRefPtr<U>& r)
        {
            return *this = r.get();
        }

        void swap(T** pp)
        {
            T* p = ptr_;
            ptr_ = *pp;
            *pp = p;
        }

        void swap(ScopedRefPtr<T>& r)
        {
            swap(&r.ptr_);
        }

    protected:
        T* ptr_;
    };

    template <typename T>
    ScopedRefPtr<T> MakeScopedRefPtr(T* t)
    {
        return ScopedRefPtr<T>(t);
    }
} // namespace tthread

#endif // __SCOPED_REF_PTR_H__
