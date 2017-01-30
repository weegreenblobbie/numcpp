#ifndef _NUMCPP_CORE_HPP_
#define _NUMCPP_CORE_HPP_


#include <numcpp/array.hpp>
#include <numcpp/const_array.hpp>
#include <numcpp/macros.hpp>


namespace numcpp
{


bool any(const array<bool> & a);
bool all(const array<bool> & a);


template <class R> array<R> arange(R stop);
template <class R> array<R> arange(R start, R stop);
template <class R> array<R> arange(R start, R stop, R step);

template <class R> array<R> ones(const std::vector<uint64> & shape);
template <class R> array<R> zeros(const std::vector<uint64> & shape);


//-----------------------------------------------------------------------------
// inline implementation

inline bool
any(const array<bool> & a)
{
    if(a.ndim() == 1)
    {
        for(uint64 i = 0; i < a.size(); ++i)
        {
            bool b = a(i);

            if(b) return true;
        }

        return false;
    }
    if(a.ndim() == 2)
    {
        for(uint64 m = 0; m < a.shape()[0]; ++m)
        {
            for(uint64 n = 0; n < a.shape()[1]; ++n)
            {
                bool b = a(m,n);

                if(b) return true;
            }
        }

        return false;
    }

    M_THROW_RT_ERROR("unhandled case"); // LCOV_EXCL_LINE

    return false;
}


inline bool
all(const array<bool> & a)
{
    if(a.ndim() == 1)
    {
        for(uint64 i = 0; i < a.size(); ++i)
        {
            bool b = a(i);

            if(!b) return false;
        }

        return true;
    }
    else
    if(a.ndim() == 2)
    {
        for(uint64 m = 0; m < a.shape()[0]; ++m)
        {
            for(uint64 n = 0; n < a.shape()[1]; ++n)
            {
                bool b = a(m,n);

                if(!b) return false;
            }
        }

        return true;
    }
    else
    if(a.ndim() == 3)
    {
        for(uint64 m = 0; m < a.shape()[0]; ++m)
        {
            for(uint64 n = 0; n < a.shape()[1]; ++n)
            {
                for(uint64 p = 0; p < a.shape()[2]; ++p)
                {
                    bool b = a(m,n,p);

                    if(!b) return false;
                }
            }
        }

        return true;
    }

    M_THROW_RT_ERROR("unhandled case"); // LCOV_EXCL_LINE

    return false;
}


namespace detail
{
    template <typename T>
    T sign(T val)
    {
        return (T(0) < val) - (val < T(0));
    }

} // namespace


namespace detail
{


template <class R>
typename std::enable_if<std::is_integral<R>::value, array<R>>::type
arange(R start, R stop, R step)
{
    if(step == 0) M_THROW_RT_ERROR("step cannot be 0");

    // compute size directly

    R s = (stop - start);

    if(s % step) s += step;

    s /= step;

    if(s == 0) return array<R>({});

    std::vector<R> v(s, R(0));

    uint32 i = 0;

    R t = start;

    while((step > 0 and t < stop) or (step < 0 and t > stop))
    {
        v[i++] = static_cast<R>(t);
        t += step;
    }

    return array<R>(v);
}


template <class R>
typename std::enable_if<std::is_floating_point<R>::value, array<R>>::type
arange(R start, R stop, R step)
{
    if(step == 0) M_THROW_RT_ERROR("step cannot be 0");

    std::vector<R> v;

    R t = start;

    while((step > 0 and t < stop) or (step < 0 and t > stop))
    {
        v.push_back(static_cast<R>(t));
        t += step;
    }

    return array<R>(v);
}


} // namespace



template <class R>
array<R>
arange(R stop)
{
    return detail::arange(static_cast<R>(0), stop, static_cast<R>(1));
}


template <class R>
array<R>
arange(R start, R stop)
{
    return detail::arange(start, stop, static_cast<R>(1));
}


template <class R>
array<R>
arange(R start, R stop, R step)
{
    return detail::arange(start, stop, step);
}



template <class R>
array<R> ones(const std::vector<uint64> & shape)
{
    return array<R>(
        std::vector<R>(detail::_compute_size(shape), static_cast<R>(1))
    ).reshape(shape);
}


template <class R>
array<R> zeros(const std::vector<uint64> & shape)
{
    return array<R>(
        std::vector<R>(detail::_compute_size(shape), static_cast<R>(0))
    ).reshape(shape);
}


} // namespace


// :noTabs=true:

#endif // _NUMCPP_CORE_HPP_