#ifndef _NUMCPP_ARRAY_HPP_
#define _NUMCPP_ARRAY_HPP_

#include <numcpp/types.hpp>

#include <iostream>
#include <memory>
#include <vector>


namespace numcpp
{


// forward

template <class R = float32> class array;

template <class R> std::ostream & operator<<(std::ostream &, const array<R> &);


template <class R>
class array
{


public:

    using value_type = R;

    array();
//~    explicit array(std::size_t);
    array(const std::vector<uint64> & shape, const R & value = R());
//~    array(const array & other);
//~    array(array && other);
//~    array();
//~    array(std::initializer_list<T> il, const std::vector<uint32> & shape);
//~
//~    template <class U>
//~    array<U>                  astype() const;
//~
//~    array<R>                  flatten() const;
    const uint32              ndim() const                   { return _shape.size(); }
    std::size_t               size() const                   { return _size; }
    const std::vector<uint64> shape() const                  { return _shape; }
//~    array<R> &                transpose();
//~    array<R> &                T();
//~
//~    // unary ops
//~
//~    array<R>    operator+() const;
//~    array<R>    operator-() const;
//~    array<R>    operator~() const;
//~    array<bool> operator!() const;
//~

    R &       operator()(index_t i);
    R &       operator()(index_t i, index_t j);
//~    R &       operator()(index_t i, index_t j, index_t k);
//~    R &       operator()(index_t i, index_t j, index_t k, index_t l);
//~
    const R & operator()(index_t i) const;
    const R & operator()(index_t i, index_t j) const;
//~    const R & operator()(index_t i, index_t j, index_t k) const;
//~    const R & operator()(index_t i, index_t j, index_t k, index_t l) const;
//~
//~
//~    array<R> & operator=(const array<R> & rhs);
//~
//~    array<R> operator+=( const array<R> & rhs );
//~    array<R> operator-=( const array<R> & rhs );
//~    array<R> operator*=( const array<R> & rhs );
//~    array<R> operator/=( const array<R> & rhs );
//~    array<R> operator%=( const array<R> & rhs );
//~    array<R> operator&=( const array<R> & rhs );
//~    array<R> operator|=( const array<R> & rhs );
//~    array<R> operator^=( const array<R> & rhs );
//~    array<R> operator<<=( const array<R> & rhs );
//~    array<R> operator>>=( const array<R> & rhs );
//~
//~    array<R> operator+=( const R & val );
//~    array<R> operator-=( const R & val );
//~    array<R> operator*=( const R & val );
//~    array<R> operator/=( const R & val );
//~    array<R> operator%=( const R & val );
//~    array<R> operator&=( const R & val );
//~    array<R> operator|=( const R & val );
//~    array<R> operator^=( const R & val );
//~    array<R> operator<<=( const R & val );
//~    array<R> operator>>=( const R & val );

friend std::ostream & operator<< <>(std::ostream &, const array<R> &);

protected:

    std::size_t                     _size;

    std::shared_ptr<std::vector<R>> _array;
    R *                             _data;

    std::vector<uint64>             _shape;
    std::vector<uint64>             _strides;
    std::vector<uint64>             _offsets;
};


template <class R>
std::ostream & operator<<(std::ostream &, const array<R> &);


//-----------------------------------------------------------------------------
// inline implementation

namespace detail
{
    std::size_t _compute_size(const std::vector<uint64> & shape)
    {
        std::size_t s = ! shape.empty();
        for(auto x : shape)
        {
            if(x == 0) continue;
            s *= x;
        }

        return s;
    }
}

template <class R>
array<R>::
array()
    :
    _size(0),
    _array(nullptr),
    _data(nullptr),
    _shape(),
    _strides(),
    _offsets()
{}


template <class R>
array<R>::
array(const std::vector<uint64> & shape, const R & value)
    :
    _size(detail::_compute_size(shape)),
    _array(std::make_shared<std::vector<R>>(std::vector<R>(_size, value))),
    _data(_array->data()),
    _shape(shape),
    _strides(),
    _offsets()
{
    // FIXME: fix strides & offsets
}


template <class R>
R &
array<R>::
operator()(index_t i)
{
    return _data[i];
}


template <class R>
const R &
array<R>::
operator()(index_t i) const
{
    return _data[i];
}


template <class R>
R &
array<R>::
operator()(index_t i, index_t j)
{
    return _data[i * _shape[1] + j];
}


template <class R>
const R &
array<R>::
operator()(index_t i, index_t j) const
{
    return _data[i * _shape[1] + j];
}


template <class R>
std::ostream &
operator<<(std::ostream & out, const array<R> & a)
{
    if(a.size() > 100) throw std::runtime_error("array to big to print");

    if(a.ndim() > 2) throw std::runtime_error("fixme");

    if(a.ndim() == 1)
    {
        out << "array([";

        for(auto x : *a._array)
        {
            out << x << ", ";
        }

        out << "])\n";
    }
    else
    if(a.ndim() == 2)
    {
        out << "array([\n";

        for(auto i = 0u; i < a._shape[0]; ++i)
        {
            out << "    [";

            for(auto j = 0u; j < a._shape[1]; ++j)
            {
                out << a(i,j) << ",";
            }

            out << "],\n";
        }

        out << "])";
    }

    return out;
}




} // namespace


#endif

// :mode=c++:noTabs=true: