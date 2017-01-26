#ifndef _NUMCPP_CORE_HPP_
#define _NUMCPP_CORE_HPP_


#include <numcpp/array.hpp>


#include <fmt/fmt.hpp>  // https://github.com/fmtlib/fmt


namespace numcpp
{


bool any(const array<bool> & a);
bool all(const array<bool> & a);


template <class R>
array<R> arange(index_t start, index_t stop, index_t step);

template <class R>
array<R> arange(index_t stop)                    { return arange<R>(0, stop, 1); }

template <class R>
array<R> arange(index_t start, index_t stop)     { return arange<R>(start, stop, 1); }


//-----------------------------------------------------------------------------
// inline implementation

inline bool
any(const array<bool> & a)
{
    if(a.ndim() == 1)
    {
        for(index_t i = 0; i < a.size(); ++i)
        {
            bool b = a(i);

            if(b) return true;
        }

        return false;
    }
    if(a.ndim() == 2)
    {
        for(index_t m = 0; m < a.shape()[0]; ++m)
        {
            for(index_t n = 0; n < a.shape()[1]; ++n)
            {
                bool b = a(m,n);

                if(b) return true;
            }
        }

        return false;
    }

    throw std::runtime_error(
        fmt::format("{}({}): unhandled case", __FILE__, __LINE__)
    );

    return false;
}


inline bool
all(const array<bool> & a)
{
    if(a.ndim() == 1)
    {
        for(index_t i = 0; i < a.size(); ++i)
        {
            bool b = a(i);

            if(!b) return false;
        }

        return true;
    }
    if(a.ndim() == 2)
    {
        for(index_t m = 0; m < a.shape()[0]; ++m)
        {
            for(index_t n = 0; n < a.shape()[1]; ++n)
            {
                bool b = a(m,n);

                if(!b) return false;
            }
        }

        return true;
    }

    throw std::runtime_error(
        fmt::format("{}({}): unhandled case", __FILE__, __LINE__)
    );

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


template <class R>
array<R>
arange(index_t start, index_t stop, index_t step)
{
    if(step == 0) M_THROW_RT_ERROR("step cannot be 0");

    // compute size directly

    index_t s = (stop - start);

    if(s % step) s += step;

    s /= step;

    if(s == 0)
    {
        return array<R>({});
    }

    std::vector<R> v(s, R(0));

    uint32 i = 0;

    index_t t = start;

    while((step > 0 and t < stop) or (step < 0 and t > stop))
    {
        v[i++] = static_cast<R>(t);
        t += step;
    }

    return array<R>(v);
}


} // namespace


// :noTabs=true:

#endif // _NUMCPP_CORE_HPP_