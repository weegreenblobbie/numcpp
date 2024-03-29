#ifndef _NUMCPP_ARRAY_HPP_
#define _NUMCPP_ARRAY_HPP_


#include <numcpp/axis_iterator.hpp>
#include <numcpp/fmt.hpp>
#include <numcpp/macros.hpp>
#include <numcpp/slice.hpp>
#include <numcpp/shape.hpp>
#include <numcpp/types.hpp>


#include <memory>
#include <sstream>
#include <type_traits>
#include <vector>


namespace numcpp
{


// forward

template <class R> class array;
template <class R> class array_view;

                   std::ostream & operator<<(std::ostream &, const std::vector<uint64> &);
template <class R> std::ostream & operator<<(std::ostream &, const array<R> &);

//-----------------------------------------------------------------------------
// forward these so they can be friends

namespace detail {

    template <class R>
    struct sum_type
    {
        using type = R;
    };

    template <>
    struct sum_type<bool>
    {
        using type = std::size_t;
    };

    template <class R>
    struct void_if_numeric
    {
        using type = typename std::enable_if_t<std::is_arithmetic<R>::value>;
    };

    template <class R>
    struct abs_type
    {
        using type = R;
    };

    template <>
    struct abs_type<complex64>
    {
        using type = float32;
    };

    template <>
    struct abs_type<complex128>
    {
        using type = float64;
    };

    template <class R>
    struct R_if_integral
    {
        using type = typename std::enable_if_t<std::is_integral<R>::value, R>;
    };

    template <class R>
    struct bool_if_integral
    {
        using type = typename std::enable_if_t<std::is_integral<R>::value, bool>;
    };

    template <typename R>
    struct const_ref_helper
    {
        using type = typename array<R>::const_reference;
    };

    template <>
    struct const_ref_helper<bool>
    {
        using type = bool;
    };
}

template <class R> typename detail::sum_type<R>::type sum(const array<R> & a);
template <class R> R min(const array<R> & a);
template <class R> R max(const array<R> & a);

template <class R> array<bool> operator== (const array<R> & lhs, const R & rhs);
template <class R> array<bool> operator!= (const array<R> & lhs, const R & rhs);
template <class R> array<bool> operator<  (const array<R> & lhs, const R & rhs);
template <class R> array<bool> operator<= (const array<R> & lhs, const R & rhs);
template <class R> array<bool> operator>  (const array<R> & lhs, const R & rhs);
template <class R> array<bool> operator>= (const array<R> & lhs, const R & rhs);

template <class R> array<bool> operator== (const R & lhs, const array<R> & rhs);
template <class R> array<bool> operator!= (const R & lhs, const array<R> & rhs);
template <class R> array<bool> operator<  (const R & lhs, const array<R> & rhs);
template <class R> array<bool> operator<= (const R & lhs, const array<R> & rhs);
template <class R> array<bool> operator>  (const R & lhs, const array<R> & rhs);
template <class R> array<bool> operator>= (const R & lhs, const array<R> & rhs);

template <class R> array<bool> operator== (const array<R> & lhs, const array<R> & rhs);
template <class R> array<bool> operator!= (const array<R> & lhs, const array<R> & rhs);
template <class R> array<bool> operator<  (const array<R> & lhs, const array<R> & rhs);
template <class R> array<bool> operator<= (const array<R> & lhs, const array<R> & rhs);
template <class R> array<bool> operator>  (const array<R> & lhs, const array<R> & rhs);
template <class R> array<bool> operator>= (const array<R> & lhs, const array<R> & rhs);


template <class R>
class array
{

public:

    using value_type      = typename std::vector<R>::value_type;
    using reference       = typename std::vector<R>::reference;
    using const_reference = typename std::vector<R>::const_reference;

    array(const std::initializer_list<R> & il);
    array(const std::vector<R> & v);
    array(const shape_t &, const std::vector<R> & v);
    array(const shape_t & shape, const R & value = R());
    array(array<R> && move) = default;
    array(const array<R> & other);
    array(const array_view<R> & other);

    array<R> & operator=(const array<R> & rhs)
    {
        if (this == &rhs) return *this;
        _size = rhs._size;
        _array = rhs._array;
        _shape = rhs._shape;
        _strides = rhs._strides;
        _offset = rhs._offset;
        return *this;
    }


    template <class U>
    array<U>                  astype() const;
//~
//~    array<R>                  flatten() const;
    std::size_t               ndim() const                   { return _shape.size(); }
    std::size_t               size() const                   { return _size; }
    const shape_t &           shape() const                  { return _shape; }
    array<R>                  transpose();
    array<R>                  T()                            { return transpose(); }

    array<R> &                reshape(const shape_t & new_shape);

    std::string               print(const std::string & fmt_ = "") const;
    std::string               debug_print() const;

    // element wise operations
    template <class U=R> typename detail::void_if_numeric<U>::type abs()   ;
    template <class U=R> typename detail::void_if_numeric<U>::type acos()  ;
    template <class U=R> typename detail::void_if_numeric<U>::type asin()  ;
    template <class U=R> typename detail::void_if_numeric<U>::type atan()  ;
    template <class U=R> typename detail::void_if_numeric<U>::type cos()   ;
    template <class U=R> typename detail::void_if_numeric<U>::type cosh()  ;
    template <class U=R> typename detail::void_if_numeric<U>::type exp()   ;
    template <class U=R> typename detail::void_if_numeric<U>::type log()   ;
    template <class U=R> typename detail::void_if_numeric<U>::type log10() ;
    template <class U=R> typename detail::void_if_numeric<U>::type sin()   ;
    template <class U=R> typename detail::void_if_numeric<U>::type sinh()  ;
    template <class U=R> typename detail::void_if_numeric<U>::type sqrt()  ;
    template <class U=R> typename detail::void_if_numeric<U>::type tan()   ;
    template <class U=R> typename detail::void_if_numeric<U>::type tanh()  ;

    //-------------------------------------------------------------------------
    // operators

    // Implicit convertions.
    operator typename detail::const_ref_helper<R>::type () const;
    operator reference ();

    array<R> & operator=(const R & rhs);

    template <typename U>
    array<R> & operator=(const U & rhs);  // used to create compiler error for type mismatch

    template<class U=R> array<typename detail::R_if_integral<U>::type> operator-() const;
    template<class U=R> array<typename detail::R_if_integral<U>::type> operator~() const;
    template<class U=R> array<typename detail::bool_if_integral<U>::type> operator!() const;

    array<R> operator()(const slice &);
    array<R> operator()(const slice &, const slice &);
    array<R> operator()(const slice &, const slice &, const slice &);

    virtual array_view<R> operator()(const slice &) const;
    virtual array_view<R> operator()(const slice &, const slice &) const;
    virtual array_view<R> operator()(const slice &, const slice &, const slice &) const;

    array<R> & operator+= ( const array<R> & rhs );
    array<R> & operator-= ( const array<R> & rhs );
    array<R> & operator*= ( const array<R> & rhs );
    array<R> & operator/= ( const array<R> & rhs );

    array<R> & operator+= ( typename detail::const_ref_helper<R>::type rhs );
    array<R> & operator-= ( typename detail::const_ref_helper<R>::type rhs );
    array<R> & operator*= ( typename detail::const_ref_helper<R>::type rhs );
    array<R> & operator/= ( typename detail::const_ref_helper<R>::type rhs );

    template<class U=R> array<typename detail::R_if_integral<U>::type> & operator%= ( const array<R> & rhs );
    template<class U=R> array<typename detail::R_if_integral<U>::type> & operator&= ( const array<R> & rhs );
    template<class U=R> array<typename detail::R_if_integral<U>::type> & operator|= ( const array<R> & rhs );
    template<class U=R> array<typename detail::R_if_integral<U>::type> & operator^= ( const array<R> & rhs );
    template<class U=R> array<typename detail::R_if_integral<U>::type> & operator<<=( const array<R> & rhs );
    template<class U=R> array<typename detail::R_if_integral<U>::type> & operator>>=( const array<R> & rhs );

    template<class U=R> array<typename detail::R_if_integral<U>::type> & operator%= ( const R & val );
    template<class U=R> array<typename detail::R_if_integral<U>::type> & operator&= ( const R & val );
    template<class U=R> array<typename detail::R_if_integral<U>::type> & operator|= ( const R & val );
    template<class U=R> array<typename detail::R_if_integral<U>::type> & operator^= ( const R & val );
    template<class U=R> array<typename detail::R_if_integral<U>::type> & operator<<=( const R & val );
    template<class U=R> array<typename detail::R_if_integral<U>::type> & operator>>=( const R & val );

    reference operator[](std::size_t);
    const_reference operator[](std::size_t) const;

protected:

    array(){}
    array(
        std::size_t                     size,
        std::shared_ptr<std::vector<R>> a,
        const shape_t &                 shape,
        const std::vector<index_t>      strides,
        index_t                         offset
    );

    void _deep_copy(const array<R> & other);

    array<R> _shallow_copy() const;

    std::size_t                     _size{0};
    std::shared_ptr<std::vector<R>> _array{nullptr};
    shape_t                         _shape{};
    std::vector<index_t>            _strides{};
    index_t                         _offset{0};

    friend class array_view<R>;

    template <typename> friend class array;

    friend typename detail::sum_type<R>::type sum <> (const array<R> & a);
    friend R min <> (const array<R> & a);
    friend R max <> (const array<R> & a);

    friend array<bool> operator== <> (const array<R> & lhs, const R & rhs);
    friend array<bool> operator!= <> (const array<R> & lhs, const R & rhs);
    friend array<bool> operator<  <> (const array<R> & lhs, const R & rhs);
    friend array<bool> operator<= <> (const array<R> & lhs, const R & rhs);
    friend array<bool> operator>  <> (const array<R> & lhs, const R & rhs);
    friend array<bool> operator>= <> (const array<R> & lhs, const R & rhs);

    friend array<bool> operator== <> (const R & lhs, const array<R> & rhs);
    friend array<bool> operator!= <> (const R & lhs, const array<R> & rhs);
    friend array<bool> operator<  <> (const R & lhs, const array<R> & rhs);
    friend array<bool> operator<= <> (const R & lhs, const array<R> & rhs);
    friend array<bool> operator>  <> (const R & lhs, const array<R> & rhs);
    friend array<bool> operator>= <> (const R & lhs, const array<R> & rhs);

    friend array<bool> operator== <> (const array<R> & lhs, const array<R> & rhs);
    friend array<bool> operator!= <> (const array<R> & lhs, const array<R> & rhs);
    friend array<bool> operator<  <> (const array<R> & lhs, const array<R> & rhs);
    friend array<bool> operator<= <> (const array<R> & lhs, const array<R> & rhs);
    friend array<bool> operator>  <> (const array<R> & lhs, const array<R> & rhs);
    friend array<bool> operator>= <> (const array<R> & lhs, const array<R> & rhs);
};


//-----------------------------------------------------------------------------
// array_view


template <class R>
class array_view : public array<R>
{
public:

    using value_type      = typename array<R>::value_type;
    using reference       = typename array<R>::reference;
    using const_reference = typename array<R>::const_reference;

    array_view<R> operator()(const slice & s0) const override;
    array_view<R> operator()(const slice & s0, const slice & s1) const override;
    array_view<R> operator()(const slice & s0, const slice & s1, const slice & s2) const override;

    void abs()   = delete;
    void acos()  = delete;
    void asin()  = delete;
    void atan()  = delete;
    void cos()   = delete;
    void cosh()  = delete;
    void exp()   = delete;
    void log()   = delete;
    void log10() = delete;
    void sin()   = delete;
    void sinh()  = delete;
    void sqrt()  = delete;
    void tan()   = delete;
    void tanh()  = delete;

    array<R> operator=(const R &)  = delete;

    array<R> & operator+=(const array<R> & rhs) = delete;
    array<R> & operator-=(const array<R> & rhs) = delete;
    array<R> & operator*=(const array<R> & rhs) = delete;
    array<R> & operator/=(const array<R> & rhs) = delete;

    array<R> & operator+=(const R & rhs) = delete;
    array<R> & operator-=(const R & rhs) = delete;
    array<R> & operator*=(const R & rhs) = delete;
    array<R> & operator/=(const R & rhs) = delete;

    array<R> & operator%= (const array<R> & rhs) = delete;
    array<R> & operator&= (const array<R> & rhs) = delete;
    array<R> & operator|= (const array<R> & rhs) = delete;
    array<R> & operator^= (const array<R> & rhs) = delete;
    array<R> & operator<<= (const array<R> & rhs) = delete;
    array<R> & operator>>= (const array<R> & rhs) = delete;

    array<R> & operator%= (const R & rhs) = delete;
    array<R> & operator&= (const R & rhs) = delete;
    array<R> & operator|= (const R & rhs) = delete;
    array<R> & operator^= (const R & rhs) = delete;
    array<R> & operator<<= (const R & rhs) = delete;
    array<R> & operator>>= (const R & rhs) = delete;

protected:

    array_view(const array<R> & a)
        : array<R>::array(a._size, a._array, a._shape, a._strides, a._offset)
    {}

    friend class array<R>;
};


//-----------------------------------------------------------------------------
// inline implemenation of some class array<R> conversion to array_view<R>.


template <class R>
array_view<R>
array<R>::operator()(const slice & s0) const
{
    array<R> tmp = array<R>::_shallow_copy()(s0);
    return array_view<R>(tmp);
}


template <class R>
array_view<R>
array<R>::operator()(const slice & s0, const slice & s1) const
{
    array<R> tmp = array<R>::_shallow_copy()(s0, s1);
    return array_view<R>(tmp);
}


template <class R>
array_view<R>
array<R>::operator()(const slice & s0, const slice & s1, const slice & s2) const
{
    array<R> tmp = array<R>::_shallow_copy()(s0, s1, s2);
    return array_view<R>(tmp);
}


//-----------------------------------------------------------------------------
// inline implemenation of some class array_view<R>::operator().


template <class R>
array_view<R>
array_view<R>::operator()(const slice & s0) const
{
    array<R> tmp = array<R>::_shallow_copy()(s0);
    return array_view<R>(tmp);
}


template <class R>
array_view<R>
array_view<R>::operator()(const slice & s0, const slice & s1) const
{
    array<R> tmp = array<R>::_shallow_copy()(s0, s1);
    return array_view<R>(tmp);
}


template <class R>
array_view<R>
array_view<R>::operator()(const slice & s0, const slice & s1, const slice & s2) const
{
    array<R> tmp = array<R>::_shallow_copy()(s0, s1, s2);
    return array_view<R>(tmp);
}


//-----------------------------------------------------------------------------
// array inline implementation

namespace detail
{
    inline
    std::size_t _compute_size(const shape_t & shape)
    {
        std::size_t s = ! shape.empty();

        for(auto x : shape)
        {
            if(x == 0) throw std::runtime_error("shape contains 0's!");
            s *= x;
        }

        return s;
    }
}


template <class R>
array<R>::
array(const std::initializer_list<R> & il)
    :
    _size(il.size()),
    _array(std::make_shared<std::vector<R>>(il)),
    _shape({_size})
{}


template <class R>
array<R>::
array(const std::vector<R> & v)
    :
    _size(v.size()),
    _array(std::make_shared<std::vector<R>>(v)),
    _shape({_size})
{}


template <class R>
array<R>::
array(const shape_t & shape, const std::vector<R> & v)
    :
    _size(v.size()),
    _array(std::make_shared<std::vector<R>>(v)),
    _shape(shape)
{
    auto s = detail::_compute_size(shape);

    if(v.size() != s) M_THROW_RT_ERROR("vector.size() and shape mismatch");
}


template <class R>
array<R>::
array(const shape_t & shape, const R & value)
    :
    _size(detail::_compute_size(shape)),
    _array(std::make_shared<std::vector<R>>(std::vector<R>(_size, value))),
    _shape(shape)
{}


template <class R>
array<R>::
array(const array<R> & other)
    :
    _size(other._size),
    _array(std::make_shared<std::vector<R>>()),
    _shape(other._shape)
{
    _deep_copy(other);
}


template <class R>
array<R>::
array(const array_view<R> & other)
    :
    _size(other._size),
    _array(std::make_shared<std::vector<R>>()),
    _shape(other._shape)
{
    _deep_copy(other);
}


template <class R>
void
array<R>::
_deep_copy(const array<R> & other)
{
    _array->reserve(_size);

    if(ndim() == 1)
    {
        #define loop( idx )                                                  \
            for(std::size_t i = 0; i < _size; ++i)                           \
            {                                                                \
                _array->emplace_back((*other._array)[other._offset + idx]);  \
            }

        if(other._strides.empty()) loop( i )
        else                       loop( i * other._strides[0] )

        #undef loop
    }
    else
    if(ndim() == 2)
    {
        #define loop( idx )                                                   \
            for(std::size_t m = 0; m < _shape[0]; ++m)                        \
            {                                                                 \
                for(std::size_t n = 0; n < _shape[1]; ++n)                    \
                {                                                             \
                    _array->emplace_back(                                     \
                        (*other._array)[other._offset + idx ]);               \
                }                                                             \
            }

        if(other._strides.empty()) loop( m * _shape[1] + n )
        else                       loop( m * other._strides[0] + n * other._strides[1] )

        #undef loop
    }
    else
    if(ndim() == 3)
    {
        #define loop( idx )                                                   \
            for(std::size_t m = 0; m < _shape[0]; ++m)                        \
            {                                                                 \
                for(std::size_t n = 0; n < _shape[1]; ++n)                    \
                {                                                             \
                    for(std::size_t p = 0; p < _shape[2]; ++p)                \
                    {                                                         \
                        _array->emplace_back(                                 \
                            (*other._array)[other._offset + idx]);            \
                    }                                                         \
                }                                                             \
            }

        if(other._strides.empty()) loop( m * _shape[1] *_shape[2] + n * _shape[2] + p )
        else                       loop( m * other._strides[0] + n * other._strides[1] + p * other._strides[2] )

        #undef loop
    }
    else
    {
        M_THROW_RT_ERROR("unhandled case"); // LCOV_EXCL_LINE
    }
}


template <class R>
array<R>::
array(
    std::size_t                     size,
    std::shared_ptr<std::vector<R>> a,
    const shape_t &                 shape,
    const std::vector<index_t>      strides,
    index_t                         offset
)
    :
    _size(size),
    _array(a),
    _shape(shape),
    _strides(strides),
    _offset(offset)
{}


template <class R>
array<R>
array<R>::
_shallow_copy() const
{
    return array<R>(_size, _array, _shape, _strides, _offset);
}


template <class R>
array<R>
array<R>::
transpose()
{
    if(ndim() == 1) return *this;

    array<R> out;

    out._size = _size;
    out._array = _array;
    out._offset = _offset;

    if(ndim() == 2)
    {
        out._shape = {_shape[1], _shape[0]};

        if(_strides.empty())
        {
            out._strides = {1, static_cast<index_t>(_shape[1])};
        }
        else
        if(_strides[0] != 1 or _strides[1] != static_cast<index_t>(_shape[1]))
        {
            out._strides = {
                static_cast<index_t>(_strides[1]),
                static_cast<index_t>(_strides[0])
            };
        }

        return out;
    }
    else
    if(ndim() == 3)
    {
        out._shape = {_shape[2], _shape[1], _shape[0]};

        if(_strides.empty())
        {
            out._strides = {
                1,
                static_cast<index_t>(_shape[2]),
                static_cast<index_t>(_shape[2] * _shape[1])
            };
        }
        else
        if(
            _strides[0] != 1 or
            _strides[1] != static_cast<index_t>(_shape[0]) or
            _strides[2] != static_cast<index_t>(_shape[0] * _shape[1]))
        {
            out._strides = {_strides[2], _strides[1], _strides[0]};
        }

        return out;
    }

    M_THROW_RT_ERROR("unhandled case"); // LCOV_EXCL_LINE

    return *this; // LCOV_EXCL_LINE
}


template <class R>
array<R>::operator typename array<R>::reference ()
{
    if(_size != 1)
    {
        if(std::is_same<bool, R>::value)
        {
            M_THROW_RT_ERROR("The truth value of an array with more than one element is ambiguous. Use numcpp::any() or numcpp::all().");
        }

        M_THROW_RT_ERROR("converting to single value from array!");
    }

    return (*_array)[_offset];
}


template <class R>
array<R>::operator typename detail::const_ref_helper<R>::type () const
{
    if(_size != 1)
    {
        if(std::is_same<bool, R>::value)
        {
            M_THROW_RT_ERROR("The truth value of an array with more than one element is ambiguous. Use numcpp::any() or numcpp::all().");
        }

        M_THROW_RT_ERROR("converting to single value from array!");
    }

    return (*_array)[_offset];
}


template <class R> template<class U>
array<U>
array<R>::
astype() const
{
    array<U> out;

    out._size = _size;
    out._array = std::make_shared<std::vector<U>>();
    out._array->reserve(_size);
    out._shape = _shape;

    if(ndim() == 1)
    {
        for(std::size_t i = 0; i < _size; ++i)
        {
            out._array->emplace_back(
                static_cast<U>((*this)(i)));
        }

        return out;
    }
    else
    if(ndim() == 2)
    {
        for(std::size_t m = 0; m < _shape[0]; ++m)
        {
            for(std::size_t n = 0; n < _shape[1]; ++n)
            {
                out._array->emplace_back(
                    static_cast<U>((*this)(m,n)));
            }
        }

        return out;
    }
    else
    if(ndim() == 3)
    {
        for(std::size_t m = 0; m < _shape[0]; ++m)
        {
            for(std::size_t n = 0; n < _shape[1]; ++n)
            {
                for(std::size_t p = 0; p < _shape[2]; ++p)
                {
                    out._array->emplace_back(
                        static_cast<U>((*this)(m,n,p)));
                }
            }
        }

        return out;
    }

    M_THROW_RT_ERROR("unhandled case"); // LCOV_EXCL_LINE

    return out;
}


template <class R>
array<R> &
array<R>::
reshape(const shape_t & shape)
{
    auto s = detail::_compute_size(shape);

    if(_size != s) M_THROW_RT_ERROR("total size of new array must be unchanged");

    if(_strides.empty())
    {
        _shape = shape;

        return *this;
    }

    // deep copy and transform

    std::vector<R> vec;
    vec.reserve(_size);

    if(ndim() == 1)
    {
        for(std::size_t i = 0; i < _size; ++i)
        {
            vec.emplace_back((*this)(i));
        }
    }
    else
    if(ndim() == 2)
    {
        for(std::size_t m = 0; m < _shape[0]; ++m)
        {
            for(std::size_t n = 0; n < _shape[1]; ++n)
            {
                vec.emplace_back((*this)(m,n));
            }
        }
    }
    else
    if(ndim() == 3)
    {
        for(std::size_t m = 0; m < _shape[0]; ++m)
        {
            for(std::size_t n = 0; n < _shape[1]; ++n)
            {
                for(std::size_t p = 0; p < _shape[2]; ++p)
                {
                    vec.emplace_back((*this)(m,n,p));
                }
            }
        }
    }
    else
    {
        M_THROW_RT_ERROR("unhandled case"); // LCOV_EXCL_LINE
    }

    *this = array<R>(vec).reshape(shape);

    return *this;
}


template <class R>
array<R> &
array<R>::
operator=(const R & rhs)
{
    if(ndim() == 1)
    {
        #define loop( idx )                               \
            for(uint64 i = 0; i < _size; ++i)             \
            {                                             \
                (*_array)[_offset + idx ] = rhs;          \
            }

        if(_strides.empty()) loop( i )
        else                 loop( i * _strides[0] )

        #undef loop

        return *this;
    }
    else
    if(ndim() == 2)
    {
        #define loop( idx )                                \
            for(uint64 m = 0; m < _shape[0]; ++m)          \
            {                                              \
                for(uint64 n = 0; n < _shape[1]; ++n)      \
                {                                          \
                    (*_array)[_offset + idx ] = rhs;       \
                }                                          \
            }                                              \

        if(_strides.empty()) loop( m * _shape[1] + n )
        else                 loop( m * _strides[0] + n * _strides[1] )

        #undef loop

        return *this;
    }
    else
    if(ndim() == 3)
    {
        #define loop( idx )                                    \
            for(uint64 m = 0; m < _shape[0]; ++m)              \
            {                                                  \
                for(uint64 n = 0; n < _shape[1]; ++n)          \
                {                                              \
                    for(uint64 p = 0; p < _shape[2]; ++p)      \
                    {                                          \
                        (*_array)[_offset + idx ] = rhs;       \
                    }                                          \
                }                                              \
            }                                                  \

        if(_strides.empty()) loop( m * _shape[1] * _shape[2] + n * _shape[2] + p )
        else                 loop( m * _strides[0] + n * _strides[1] + p * _strides[2] )

        #undef loop

        return *this;
    }

    M_THROW_RT_ERROR("unhandled case"); // LCOV_EXCL_LINE

    return *this; // LCOV_EXCL_LINE
}


template <class R> template <class U>
array<R> &
array<R>::
operator=(const U & rhs)
{
    static_assert(
        std::is_same<R, U>::value,
        "array<R> = array<U> is not allowed"
    );

    return *this;
}


template <class R>
array<R>
array<R>::
operator()(const slice & s0)
{
    if(_size == 0) throw std::runtime_error("can't slice an empty array");

    array<R> out;

    auto n_dim = ndim();

    if(n_dim == 1)
    {
        axis_iterator ai(_shape[0], s0);
        auto s = ai.final();

        index_t start = s.start();
        index_t stop = s.stop();
        index_t step = s.step();

        if(step > 0 and start >= stop) return out;
        if(step < 0 and stop >= start) return out;

        out._array = _array;

        uint64 count = ai.size();

        out._shape = {count};
        out._size = count;
        out._strides = _strides;

        if(_strides.empty())
        {
            out._offset = _offset + start;
            if(step != 1) out._strides = {step};
        }
        else
        {
            out._offset = _offset + start * _strides[0];
            out._strides[0] *= step;
        }

        return out;
    }
    else
    if(n_dim == 2)
    {
        return (*this)(s0, missing());
    }
    else
    if(n_dim == 3)
    {
        return (*this)(s0,missing(),missing());
    }

    M_THROW_RT_ERROR("unhandled case (" << n_dim << ")"); // LCOV_EXCL_LINE
}


template <class R>
array<R>
array<R>::
operator()(const slice & s0, const slice & s1)
{
    if(_size == 0) throw std::runtime_error("can't slice an empty array");

    auto n_dim = ndim();

    if(n_dim == 1)
    {
        M_THROW_RT_ERROR("too many indicies for array");
    }
    else
    if(n_dim == 2)
    {
        axis_iterator a0(_shape[0], s0);
        axis_iterator a1(_shape[1], s1);

        uint64 count0 = a0.size();
        uint64 count1 = a1.size();

        if(count0 == 0) M_THROW_RT_ERROR("invalid slice along axis 0");
        if(count1 == 0) M_THROW_RT_ERROR("invalid slice along axis 1");

        auto s0_ = a0.final();
        auto s1_ = a1.final();

        index_t start0 = s0_.start();
        index_t start1 = s1_.start();

        index_t step0  = s0_.step();
        index_t step1  = s1_.step();

        array<R> out;

        out._size  = count0 * count1;
        out._array = _array;

        if(_strides.empty())
        {
            out._offset = _offset + start0 * static_cast<index_t>(_shape[1]) + start1;
            out._strides = {static_cast<index_t>(_shape[1]) * step0, step1};
        }

        else
        {
            out._offset = _offset + start0 * _strides[0] + start1 * _strides[1];
            out._strides = {_strides[0] * step0, _strides[1] * step1};
        }

        //---------------------------------------------------------------------
        // squeezing, not it's own funciton yet!

        // row vector
        if(count0 == 1)
        {
            out._shape = {count1};
            out._strides = {out._strides[1]};
        }

        // column vector
        else
        if(count1 == 1)
        {
            out._shape = {count0};
            out._strides = {out._strides[0]};
        }

        // 2d
        else
        {
            out._shape = {count0, count1};
        }

        return out;
    }
    else
    if(n_dim == 3)
    {
        return (*this)(s0,s1,missing());
    }

    M_THROW_RT_ERROR("unhandled case"); // LCOV_EXCL_LINE

    return array<R>();
}



template <class R>
array<R>
array<R>::
operator()(const slice & s0, const slice & s1, const slice & s2)
{
    if(_size == 0) throw std::runtime_error("can't slice an empty array");

    auto n_dim = ndim();

    if(n_dim <= 2)
    {
        M_THROW_RT_ERROR("too many indicies for array");
    }
    else
    if(n_dim == 3)
    {
        axis_iterator a0(_shape[0], s0);
        axis_iterator a1(_shape[1], s1);
        axis_iterator a2(_shape[2], s2);

        uint64 count0 = a0.size();
        uint64 count1 = a1.size();
        uint64 count2 = a2.size();

        if(count0 == 0) M_THROW_RT_ERROR("invalid slice along axis 0");
        if(count1 == 0) M_THROW_RT_ERROR("invalid slice along axis 1");
        if(count2 == 0) M_THROW_RT_ERROR("invalid slice along axis 2");

        auto s0_ = a0.final();
        auto s1_ = a1.final();
        auto s2_ = a2.final();

        index_t start0 = s0_.start();
        index_t start1 = s1_.start();
        index_t start2 = s2_.start();

        index_t step0  = s0_.step();
        index_t step1  = s1_.step();
        index_t step2  = s2_.step();

        array<R> out;

        out._size  = count0 * count1 * count2;
        out._array = _array;

        if(_strides.empty())
        {
            index_t J = _shape[1];
            index_t K = _shape[2];

            out._offset = _offset + start0 * J * K + start1 * K + start2;
            out._strides =
            {
                step0 * J * K,
                step1 * K,
                step2
            };
        }

        else
        {
            index_t I = _strides[0];
            index_t J = _strides[1];
            index_t K = _strides[2];

            out._offset = _offset + start0 * I + start1 * J + start2 * K;
            out._strides =
            {
                _strides[0] * step0,
                _strides[1] * step1,
                _strides[2] * step2
            };
        }

        //---------------------------------------------------------------------
        // squeezing, not it's own funciton yet!

        int32 key = 4 * (count0 == 1) + 2 * (count1 == 1) + (count2 == 1);

        // single value
        if(key == 0b111)
        {
            out._shape = {1};
            out._strides = {};
        }

        // row vector
        else
        if(key == 0b110)
        {
            out._shape = {count2};

            auto c = out._strides[2];

            if(out._strides[2] != 1) out._strides = {c};
            else                     out._strides = {};
        }

        // col vector

        else
        if(key == 0b101)
        {
            out._shape = {count1};
            out._strides = {out._strides[1]};
        }

        // 2d
        else
        if(key == 0b100)
        {
            out._shape = {count1, count2};

            auto b = out._strides[1];
            auto c = out._strides[2];

            index_t cnt2 = static_cast<index_t>(count2);

            if(b != cnt2 or c != 1) out._strides = {b,c};
            else                    out._strides = {};
        }

        // 2d
        else
        if(key == 0b010)
        {
            out._shape = {count0, count2};

            auto a = out._strides[0];
            auto c = out._strides[2];

            out._strides = {a, c};
        }

        // 2d
        else
        if(key == 0b001)
        {
            out._shape = {count0, count1};

            auto a = out._strides[0];
            auto b = out._strides[1];

            out._strides = {a, b};
        }

        // 3d
        else
        if(key == 0b000)
        {
            out._shape = {count0, count1, count2};
        }

        if(out._shape.empty()) M_THROW_RT_ERROR(fmt::sprintf("unandled case (%03d)", key));

        return out;
    }

    M_THROW_RT_ERROR("unhandled case"); // LCOV_EXCL_LINE

    return array<R>();
}


template <class R>
typename array<R>::reference
array<R>::
operator[](std::size_t idx)
{
    if(_size == 0) throw std::runtime_error("can't use operator[] on an empty array");

    auto n_dim = ndim();

    if(n_dim == 1)
    {
        if(_strides.empty())
        {
            return (*_array)[_offset + idx];
        }
        else
        {
            return (*_array)[_offset + idx * _strides[0]];
        }
    }
    else
    if(n_dim == 2)
    {
        size_t i0 = idx / _shape[1];
        size_t i1 = idx - i0 * _shape[1];

        if(_strides.empty())
        {
            return (*_array)[_offset + i0 * _shape[1] + i1];
        }
        else
        {
            return (*_array)[_offset + i0 * _strides[0] + i1 * _strides[1]];
        }
    }
    else
    if(n_dim == 3)
    {
        size_t i0 = idx / (_shape[1] * _shape[2]);
        size_t i1 = (idx - i0 * _shape[1] * _shape[2]) / _shape[1];
        size_t i2 = idx - i0 * _shape[1] * _shape[2] - i1 * _shape[2];

        if(_strides.empty())
        {
            return (*_array)[_offset + i0 * _shape[1] * _shape[2] + i1 * _shape[2] + i2];
        }
        else
        {
            return (*_array)[_offset + i0 * _strides[0] + i1 * _strides[1] + i2 * _strides[2]];
        }
    }

    M_THROW_RT_ERROR("unhandled case"); // LCOV_EXCL_LINE

    // Keep compiler warning quiet.
    return (*_array)[0];
}



template <class R>
typename array<R>::const_reference
array<R>::
operator[](std::size_t idx) const
{
    if(_size == 0) throw std::runtime_error("can't use operator[] on an empty array");

    auto n_dim = ndim();

    if(n_dim == 1)
    {
        if(_strides.empty())
        {
            return (*_array)[_offset + idx];
        }
        else
        {
            return (*_array)[_offset + idx * _strides[0]];
        }
    }
    else
    if(n_dim == 2)
    {
        size_t i0 = idx / _shape[0];
        size_t i1 = idx - i0 * _shape[0];

        if(_strides.empty())
        {
            return (*_array)[_offset + i0 * _shape[1] + i1];
        }
        else
        {
            return (*_array)[_offset + i0 * _strides[0] + i1 * _strides[1]];
        }
    }
    else
    if(n_dim == 3)
    {
        size_t i0 = idx / (_shape[1] * _shape[2]);
        size_t i1 = (idx - i0 * _shape[1] * _shape[2]) / _shape[1];
        size_t i2 = idx - i0 * _shape[1] * _shape[2] - i1 * _shape[2];

        if(_strides.empty())
        {
            return (*_array)[_offset + i0 * _shape[1] * _shape[2] + i1 * _shape[2] + i2];
        }
        else
        {
            return (*_array)[_offset + i0 * _strides[0] + i1 * _strides[1] + i2 * _strides[2]];
        }
    }

    M_THROW_RT_ERROR("unhandled case"); // LCOV_EXCL_LINE

    // Keep compiler warning quiet.
    return (*_array)[0];
}


inline
std::ostream &
operator<<(std::ostream & out, const std::vector<uint64> & v)
{
    out << "("; for(auto x : v) out << x << ", ";
    return out << ")";
}


template <class R>
std::ostream &
operator<<(std::ostream & out, const array<R> & a)
{
    return out << a.print();
}


namespace detail
{
    // defaults for POD values
    template <class T> std::string _array_R_to_fmt() { return "%g"; }

    template <> inline std::string _array_R_to_fmt<bool>()  { return "%d"; }
    template <> inline std::string _array_R_to_fmt<int8 >() { return "%d"; }
    template <> inline std::string _array_R_to_fmt<int16>() { return "%d"; }
    template <> inline std::string _array_R_to_fmt<int32>() { return "%d"; }
    template <> inline std::string _array_R_to_fmt<int64>() { return "%d"; }

    template <> inline std::string _array_R_to_fmt<uint8 >() { return "%d"; }
    template <> inline std::string _array_R_to_fmt<uint16>() { return "%d"; }
    template <> inline std::string _array_R_to_fmt<uint32>() { return "%d"; }
    template <> inline std::string _array_R_to_fmt<uint64>() { return "%d"; }

    template <> inline std::string _array_R_to_fmt<float32>() { return "%11.8f"; }

    template <> inline std::string _array_R_to_fmt<complex64>() { return "%11.8f"; }

    template <> inline std::string _array_R_to_fmt<complex128>() { return "%14.11f"; }

    template <class T> std::string _format(const std::string & fmt_, const T & v) { return fmt::sprintf(fmt_, v); }

    template <> inline std::string _format<complex64>(const std::string & fmt_, const complex64 & v)  { return fmt::sprintf(fmt_ + "+" + fmt_ + "j", v.real(), v.imag()); }
    template <> inline std::string _format<complex128>(const std::string & fmt_, const complex128 & v) { return fmt::sprintf(fmt_ + "+" + fmt_ + "j", v.real(), v.imag()); }

    template <class T> std::string type_name() { return "unknown"; }

    template <> inline std::string type_name<bool>() { return "bool"; }

    template <> inline std::string type_name<int8 >() { return "int8"; }
    template <> inline std::string type_name<int16>() { return "int16"; }
    template <> inline std::string type_name<int32>() { return "int32"; }
    template <> inline std::string type_name<int64>() { return "int64"; }

    template <> inline std::string type_name<uint8 >() { return "uint8"; }
    template <> inline std::string type_name<uint16>() { return "uint16"; }
    template <> inline std::string type_name<uint32>() { return "uint32"; }
    template <> inline std::string type_name<uint64>() { return "uint64"; }

    template <> inline std::string type_name<float32>() { return "float32"; }

    template <> inline std::string type_name<complex64>() { return "complex64"; }

    template <> inline std::string type_name<complex128>() { return "complex128"; }
}


template <class R>
std::string
array<R>::
print(const std::string & fmt_in) const
{
//~    if(size() > 100) throw std::runtime_error("array to big to print");

    if(ndim() > 3) throw std::runtime_error("ndim() > 3 not implemented");

    std::string fmt_(fmt_in);

    if(fmt_.length() == 0) fmt_ = detail::_array_R_to_fmt<R>();

    const array<R> & a = *this;

    if(_size == 1) return detail::_format<R>(fmt_, a(0));

    std::stringstream out;

    if(ndim() <= 1)
    {
        out << "array([ ";

        for(uint64 i = 0; i < _size; ++i)
        {
            out << detail::_format<R>(fmt_, R{a(i)});
            if(i + 1 < a._size) out << ", ";
        }

        out << " ], " << detail::type_name<R>() << ")";
    }
    else
    if(ndim() == 2)
    {
        out << "array([\n";

        for(auto i = 0u; i < _shape[0]; ++i)
        {
            out << "  [ ";

            for(auto j = 0u; j < _shape[1]; ++j)
            {
                out << detail::_format(fmt_, R{a(i,j)});
                if(j + 1 < _shape[1]) out << ", ";
            }

            out << " ],\n";
        }

        out << "], " << detail::type_name<R>() << ")";
    }
    else
    if(ndim() == 3)
    {
        out << "array([\n";

        for(auto i = 0u; i < _shape[0]; ++i)
        {
            out << "  [\n";
            for(auto j = 0u; j < _shape[1]; ++j)
            {
                out << "    [ ";

                for(auto k = 0u; k < _shape[2]; ++k)
                {
                    out << detail::_format(fmt_, R{a(i,j,k)});
                    if(k + 1 < _shape[2]) out << ", ";
                }

                out << " ],\n";
            }

            out << "  ]";

            if(i + 1 < _shape[0]) out << ",";

            out << "\n";
        }

        out << "], " << detail::type_name<R>() << ")";
    }
    else
    {
        M_THROW_RT_ERROR("unhandled case"); // LCOV_EXCL_LINE
    }

    return out.str();
}


template <class R>
std::string
array<R>::
debug_print() const
{
    std::stringstream ss;

    ss
        << "array:\n"
        << "    dtype:    " << detail::type_name<R>() << "\n"
        << "    _size:    " << _size << "\n"
        << "    _data:    " << fmt::format(            // LCOV_EXCL_LINE
            "{:16d}, ref_count={:d}",
            reinterpret_cast<uint64>(_array.get()),
            _array.use_count()
        ) << "\n"
        << "    _shape:   " << _shape << "\n"
        << "    _strides: (";

    for(const auto & x : _strides) ss << x << ", ";

    ss
        << ")\n"
        << "    _offset: "<< _offset << "\n"
        << "    _array[_offset]: " << (*_array)[_offset] << "\n";

    return ss.str();
}


#include <numcpp/_array_ops.hpp>


} // namespace


#endif // _NUMCPP_ARRAY_HPP_

// :mode=c++:noTabs=true:
