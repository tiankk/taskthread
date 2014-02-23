#ifndef __SCOPED_PTR_H__
#define __SCOPED_PTR_H__

namespace tthread {
    template <class C>
    class ScopedPtr {
    private:
        struct RValue : public ScopedPtr {
            RValue();
            ~RValue();
            RValue(const RValue&);
            void operator=(const RValue&);
        };
        ScopedPtr(ScopedPtr&);
        void operator=(ScopedPtr&);
    public:
        operator RValue&() { return *reinterpret_cast<RValue*>(this); }
        ScopedPtr Pass() { return ScopedPtr(*reinterpret_cast<RValue*>(this)); }

        typedef C element_type;

        explicit ScopedPtr(C* p = NULL) : ptr_(p) { }

        template <typename U>
        ScopedPtr(ScopedPtr<U> other) : ptr_(other.release()) { }

        ScopedPtr(RValue& other) : ptr_(other.release()) { }

        ~ScopedPtr() {
            enum { type_must_be_complete = sizeof(C) };
            delete ptr_;
        }

        template <typename U>
        ScopedPtr& operator=(ScopedPtr<U> rhs)
        {
            reset(rhs.release());
            return *this;
        }

        ScopedPtr& operator=(RValue& rhs)
        {
            swap(rhs);
            return *this;
        }

        void reset(C* p = NULL)
        {
            if (p != ptr_) {
                enum { type_must_be_complete = sizeof(C) };
                delete ptr_;
                ptr_ = p;
            }
        }

        C& operator*() const
        {
            return *ptr_;
        }
        C* operator->() const
        {
            return ptr_;
        }
        C* get() const { return ptr_; }

        bool operator==(C* p) const { return ptr_ == p; }
        bool operator!=(C* p) const { return ptr_ != p; }

        void swap(ScopedPtr& p2)
        {
            C* tmp = ptr_;
            ptr_ = p2.ptr_;
            p2.ptr_ = tmp;
        }

        C* release()
        {
            C* retVal = ptr_;
            ptr_ = NULL;
            return retVal;
        }

        template <typename PassAsType>
        ScopedPtr<PassAsType> PassAs()
        {
            return ScopedPtr<PassAsType>(release());
        }

    private:
        C* ptr_;

        template <class C2> bool operator==(ScopedPtr<C2> const& p2) const;
        template <class C2> bool operator!=(ScopedPtr<C2> const& p2) const;

    };

    // Free functions
    template <class C>
    void swap(ScopedPtr<C>& p1, ScopedPtr<C>& p2)
    {
        p1.swap(p2);
    }

    template <class C>
    bool operator==(C* p1, const ScopedPtr<C>& p2)
    {
        return p1 == p2.get();
    }

    template <class C>
    bool operator!=(C* p1, const ScopedPtr<C>& p2)
    {
        return p1 != p2.get();
    }
} // namespace tthread

#endif // __SCOPED_PTR_H__
