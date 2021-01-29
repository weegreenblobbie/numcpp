#ifndef _NUMCPP_CORE_HPP_
#define _NUMCPP_CORE_HPP_


#include <numcpp/array.hpp>
#include <numcpp/const_array.hpp>
#include <numcpp/macros.hpp>
#include <numcpp/shape.hpp>


namespace numcpp
{

template <class R> array<R> abs(const array<R> & a);

bool any(const array<bool> & a);
bool all(const array<bool> & a);


template <class R> array<R> arange(R stop);
template <class R> array<R> arange(R start, R stop);
template <class R> array<R> arange(R start, R stop, R step);

template <class R> array<R> ones(const shape_t & shape);
template <class R> array<R> zeros(const shape_t & shape);

template <class R>
typename detail::sum_type<R>::type    sum(const array<R> & a);
template <class R> array<R>           sum(const array<R> & a, std::size_t axis);

template <class R> R        min(const array<R> & a);
template <class R> array<R> min(const array<R> & a, std::size_t axis);

template <class R> R        max(const array<R> & a);
template <class R> array<R> max(const array<R> & a, std::size_t axis);


//-----------------------------------------------------------------------------
// inline implementation

template <class R>
array<R>
abs(const array<R> & a)
{
    array<R> b(a);
    b.abs();
    return b;
}


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
        for(std::size_t m = 0; m < a.shape()[0]; ++m)
        {
            for(std::size_t n = 0; n < a.shape()[1]; ++n)
            {
                bool b = a(m,n);

                if(b) return true;
            }
        }

        return false;
    }
    if(a.ndim() == 3)
    {
        for(std::size_t m = 0; m < a.shape()[0]; ++m)
        {
            for(std::size_t n = 0; n < a.shape()[1]; ++n)
            {
                for(std::size_t p = 0; p < a.shape()[2]; ++p)
                {
                    bool b = a(m,n,p);
                    if(b) return true;
                }
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
        for(std::size_t i = 0; i < a.size(); ++i)
        {
            bool b = a(i);

            if(!b) return false;
        }

        return true;
    }
    else
    if(a.ndim() == 2)
    {
        for(std::size_t m = 0; m < a.shape()[0]; ++m)
        {
            for(std::size_t n = 0; n < a.shape()[1]; ++n)
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
        for(std::size_t m = 0; m < a.shape()[0]; ++m)
        {
            for(std::size_t n = 0; n < a.shape()[1]; ++n)
            {
                for(std::size_t p = 0; p < a.shape()[2]; ++p)
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
array<R> ones(const shape_t & shape)
{
    return array<R>(
        std::vector<R>(detail::_compute_size(shape), static_cast<R>(1)) // LCOV_EXCL_LINE
    ).reshape(shape);
}


template <class R>
array<R> zeros(const shape_t & shape)
{
    return array<R>(
        std::vector<R>(detail::_compute_size(shape), static_cast<R>(0)) // LCOV_EXCL_LINE
    ).reshape(shape);
}


template <class R>
typename detail::sum_type<R>::type
sum(const array<R> & a)
{
    typename detail::sum_type<R>::type sum_ = 0;

    if(a.ndim() == 1)
    {
        #define loop( idx )                                                   \
            for(std::size_t i = 0; i < a._size; ++i)                          \
            {                                                                 \
                sum_ += (*a._array)[a._offset + idx];                         \
            }

        if(a._strides.empty()) loop( i )
        else                   loop( i * a._strides[0] )

        #undef loop
    }
    else
    if(a.ndim() == 2)
    {
        #define loop( idx )                                                   \
            for(std::size_t m = 0; m < a._shape[0]; ++m)                      \
            {                                                                 \
                for(std::size_t n = 0; n < a._shape[1]; ++n)                  \
                {                                                             \
                    sum_ += (*a._array)[a._offset + idx ];                    \
                }                                                             \
            }

        if(a._strides.empty()) loop( m * a._shape[1] + n )
        else                   loop( m * a._strides[0] + n * a._strides[1] )

        #undef loop
    }
    else
    if(a.ndim() == 3)
    {
        #define loop( idx )                                                   \
            for(std::size_t m = 0; m < a._shape[0]; ++m)                      \
            {                                                                 \
                for(std::size_t n = 0; n < a._shape[1]; ++n)                  \
                {                                                             \
                    for(std::size_t p = 0; p < a._shape[2]; ++p)              \
                    {                                                         \
                        sum_ += (*a._array)[a._offset + idx];                 \
                    }                                                         \
                }                                                             \
            }

        if(a._strides.empty()) loop( m * a._shape[1] *a._shape[2] + n * a._shape[2] + p )
        else                   loop( m * a._strides[0] + n * a._strides[1] + p * a._strides[2] )

        #undef loop
    }
    else
    {
        M_THROW_RT_ERROR("unhandled case"); // LCOV_EXCL_LINE
    }

    return sum_;
}


template <class R>
array<R>
sum(const array<R> & a, std::size_t axis)
{
    if(axis >= a.ndim()) M_THROW_RT_ERROR("axis is out of bounds (" << axis << " >= " << a.ndim() << ")");

    if(a.ndim() == 1) return array<R>({sum(a)});

    missing _;

    if(a.ndim() == 2 and axis == 0)
    {
        // init to first row
        array<R> out(a(0,_));

        for(std::size_t m = 1; m < a.shape()[0]; ++m)
        {
            out += a(m,_);
        }

        return out;
    }
    else
    if(a.ndim() == 2 and axis == 1)
    {
        // init to first column
        array<R> out(a(_,0));

        for(std::size_t n = 1; n < a.shape()[1]; ++n)
        {
            out += a(_, n);
        }

        return out;
    }
    if(a.ndim() == 3 and axis == 0)
    {
        // init to first row
        array<R> out(a(0,_,_));

        for(std::size_t m = 1; m < a.shape()[0]; ++m)
        {
            out += a(m,_,_);
        }

        return out;
    }
    else
    if(a.ndim() == 3 and axis == 1)
    {
        // init to first column
        array<R> out(a(_,0,_));

        for(std::size_t n = 1; n < a.shape()[1]; ++n)
        {
            out += a(_, n, _);
        }

        return out;
    }
    else
    if(a.ndim() == 3 and axis == 2)
    {
        // init to first slice
        array<R> out(a(_,_,0));

        for(std::size_t p = 1; p < a.shape()[2]; ++p)
        {
            out += a(_, _, p);
        }

        return out;
    }
    else
    {
        M_THROW_RT_ERROR("unhandled case"); // LCOV_EXCL_LINE
    }

    return array<R>({});
}


template <class R>
R
min(const array<R> & a)
{
    R min_;

    if(a.ndim() == 1)
    {
        min_ = a(0);

        #define loop( idx )                                                   \
            for(std::size_t i = 0; i < a._size; ++i)                          \
            {                                                                 \
                min_ = std::min(min_, (*a._array)[a._offset + idx]);          \
            }

        if(a._strides.empty()) loop( i )
        else                   loop( i * a._strides[0] )

        #undef loop
    }
    else
    if(a.ndim() == 2)
    {
        min_ = a(0,0);

        #define loop( idx )                                                   \
            for(std::size_t m = 0; m < a._shape[0]; ++m)                      \
            {                                                                 \
                for(std::size_t n = 0; n < a._shape[1]; ++n)                  \
                {                                                             \
                    min_ = std::min(min_, (*a._array)[a._offset + idx]);      \
                }                                                             \
            }

        if(a._strides.empty()) loop( m * a._shape[1] + n )
        else                   loop( m * a._strides[0] + n * a._strides[1] )

        #undef loop
    }
    else
    if(a.ndim() == 3)
    {
        min_ = a(0,0,0);

        #define loop( idx )                                                   \
            for(std::size_t m = 0; m < a._shape[0]; ++m)                      \
            {                                                                 \
                for(std::size_t n = 0; n < a._shape[1]; ++n)                  \
                {                                                             \
                    for(std::size_t p = 0; p < a._shape[2]; ++p)              \
                    {                                                         \
                        min_ = std::min(min_, (*a._array)[a._offset + idx]);  \
                    }                                                         \
                }                                                             \
            }

        if(a._strides.empty()) loop( m * a._shape[1] *a._shape[2] + n * a._shape[2] + p )
        else                   loop( m * a._strides[0] + n * a._strides[1] + p * a._strides[2] )

        #undef loop
    }
    else
    {
        M_THROW_RT_ERROR("unhandled case"); // LCOV_EXCL_LINE
    }

    return min_;
}


template <class R>
array<R>
min(const array<R> & a, std::size_t axis)
{
    if(axis >= a.ndim()) M_THROW_RT_ERROR("axis is out of bounds (" << axis << " >= " << a.ndim() << ")");

    if(a.ndim() == 1) return array<R>({min(a)});

    missing _;

    if(a.ndim() == 2 and axis == 0)
    {
        // init to first row
        array<R> out(a(0,_));

        for(std::size_t m = 1; m < a.shape()[0]; ++m)
        {
            for(std::size_t n = 0; n < a.shape()[1]; ++n)
            {
                out(n) = std::min(R{out(n)}, R{a(m,n)});
            }
        }

        return out;
    }
    else
    if(a.ndim() == 2 and axis == 1)
    {
        // init to first column
        array<R> out(a(_,0));

        for(std::size_t n = 1; n < a.shape()[1]; ++n)
        {
            for(std::size_t m = 0; m < a.shape()[0]; ++m)
            {
                out(m) = std::min(R{out(m)}, R{a(m,n)});
            }
        }

        return out;
    }
    if(a.ndim() == 3 and axis == 0)
    {
        // init
        array<R> out(a(0,_,_));

        for(std::size_t m = 1; m < a.shape()[0]; ++m)
        {
            for(std::size_t n = 0 ; n < a.shape()[1]; ++n)
            {
                for(std::size_t p = 0; p < a.shape()[2]; ++p)
                {
                    out(n,p) = std::min(R{out(n,p)}, R{a(m,n,p)});
                }
            }
        }

        return out;
    }
    else
    if(a.ndim() == 3 and axis == 1)
    {
        // init
        array<R> out(a(_,0,_));

        for(std::size_t n = 1; n < a.shape()[1]; ++n)
        {
            for(std::size_t m = 0; m < a.shape()[0]; ++m)
            {
                for(std::size_t p = 0; p < a.shape()[2]; ++p)
                {
                    out(m,p) = std::min(R{out(m,p)}, R{a(m,n,p)});
                }
            }
        }

        return out;
    }
    else
    if(a.ndim() == 3 and axis == 2)
    {
        // init
        array<R> out(a(_,_,0));

        for(std::size_t p = 1; p < a.shape()[2]; ++p)
        {
            for(std::size_t m = 0; m < a.shape()[0]; ++m)
            {
                for(std::size_t n = 0; n < a.shape()[1]; ++n)
                {
                    out(m,n) = std::min(R{out(m,n)}, R{a(m,n,p)});
                }
            }
        }

        return out;
    }
    else
    {
        M_THROW_RT_ERROR("unhandled case"); // LCOV_EXCL_LINE
    }

    return array<R>({});
}


template <class R>
R
max(const array<R> & a)
{
    R max_;

    if(a.ndim() == 1)
    {
        max_ = a(0);

        #define loop( idx )                                                   \
            for(std::size_t i = 0; i < a._size; ++i)                          \
            {                                                                 \
                max_ = std::max(max_, (*a._array)[a._offset + idx]);          \
            }

        if(a._strides.empty()) loop( i )
        else                   loop( i * a._strides[0] )

        #undef loop
    }
    else
    if(a.ndim() == 2)
    {
        max_ = a(0,0);

        #define loop( idx )                                                   \
            for(std::size_t m = 0; m < a._shape[0]; ++m)                      \
            {                                                                 \
                for(std::size_t n = 0; n < a._shape[1]; ++n)                  \
                {                                                             \
                    max_ = std::max(max_, (*a._array)[a._offset + idx]);      \
                }                                                             \
            }

        if(a._strides.empty()) loop( m * a._shape[1] + n )
        else                   loop( m * a._strides[0] + n * a._strides[1] )

        #undef loop
    }
    else
    if(a.ndim() == 3)
    {
        max_ = a(0,0,0);

        #define loop( idx )                                                   \
            for(std::size_t m = 0; m < a._shape[0]; ++m)                      \
            {                                                                 \
                for(std::size_t n = 0; n < a._shape[1]; ++n)                  \
                {                                                             \
                    for(std::size_t p = 0; p < a._shape[2]; ++p)              \
                    {                                                         \
                        max_ = std::max(max_, (*a._array)[a._offset + idx]);  \
                    }                                                         \
                }                                                             \
            }

        if(a._strides.empty()) loop( m * a._shape[1] *a._shape[2] + n * a._shape[2] + p )
        else                   loop( m * a._strides[0] + n * a._strides[1] + p * a._strides[2] )

        #undef loop
    }
    else
    {
        M_THROW_RT_ERROR("unhandled case"); // LCOV_EXCL_LINE
    }

    return max_;
}


template <class R>
array<R>
max(const array<R> & a, std::size_t axis)
{
    if(axis >= a.ndim()) M_THROW_RT_ERROR("axis is out of bounds (" << axis << " >= " << a.ndim() << ")");

    if(a.ndim() == 1) return array<R>({max(a)});

    missing _;

    if(a.ndim() == 2 and axis == 0)
    {
        // init to first row
        array<R> out(a(0,_));

        for(std::size_t m = 1; m < a.shape()[0]; ++m)
        {
            for(std::size_t n = 0; n < a.shape()[1]; ++n)
            {
                out(n) = std::max(R{out(n)}, R{a(m,n)});
            }
        }

        return out;
    }
    else
    if(a.ndim() == 2 and axis == 1)
    {
        // init to first column
        array<R> out(a(_,0));

        for(std::size_t n = 1; n < a.shape()[1]; ++n)
        {
            for(std::size_t m = 0; m < a.shape()[0]; ++m)
            {
                out(m) = std::max(R{out(m)}, R{a(m,n)});
            }
        }

        return out;
    }
    if(a.ndim() == 3 and axis == 0)
    {
        // init
        array<R> out(a(0,_,_));

        for(std::size_t m = 1; m < a.shape()[0]; ++m)
        {
            for(std::size_t n = 0 ; n < a.shape()[1]; ++n)
            {
                for(std::size_t p = 0; p < a.shape()[2]; ++p)
                {
                    out(n,p) = std::max(R{out(n,p)}, R{a(m,n,p)});
                }
            }
        }

        return out;
    }
    else
    if(a.ndim() == 3 and axis == 1)
    {
        // init
        array<R> out(a(_,0,_));

        for(std::size_t n = 1; n < a.shape()[1]; ++n)
        {
            for(std::size_t m = 0; m < a.shape()[0]; ++m)
            {
                for(std::size_t p = 0; p < a.shape()[2]; ++p)
                {
                    out(m,p) = std::max(R{out(m,p)}, R{a(m,n,p)});
                }
            }
        }

        return out;
    }
    else
    if(a.ndim() == 3 and axis == 2)
    {
        // init
        array<R> out(a(_,_,0));

        for(std::size_t p = 1; p < a.shape()[2]; ++p)
        {
            for(std::size_t m = 0; m < a.shape()[0]; ++m)
            {
                for(std::size_t n = 0; n < a.shape()[1]; ++n)
                {
                    out(m,n) = std::max(R{out(m,n)}, R{a(m,n,p)});
                }
            }
        }

        return out;
    }
    else
    {
        M_THROW_RT_ERROR("unhandled case"); // LCOV_EXCL_LINE
    }

    return array<R>({});
}


} // namespace


// :noTabs=true:

#endif // _NUMCPP_CORE_HPP_