#ifndef _NUMCPP_ARRAY_HPP_
#define _NUMCPP_ARRAY_HPP_

#include <numcpp/types.hpp>

#include <memory>
#include <vector>


namespace numcpp
{


template <class R=float32>
class array
{


public:


using value_type = R;

    array();
//~    explicit array(std::size_t);
    array(const std::vector<uint32> & shape);
//~    array(const array & other);
//~    array(array && other);
//~    array(std::initializer_list<T> il);
//~    array(std::initializer_list<T> il, const std::vector<uint32> & shape);
//~
//~    template <class U>
//~    array<U>                  astype() const;
//~
//~    array<R>                  flatten() const;
//~    const uint32              ndim() const;
//~    const std::vector<uint32> shape() const;
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
//~
    R &       operator()(index_t i);
//~    R &       operator()(index_t i, index_t j);
//~    R &       operator()(index_t i, index_t j, index_t k);
//~    R &       operator()(index_t i, index_t j, index_t k, index_t l);
//~
    const R & operator()(index_t i) const;
//~    const R & operator()(index_t i, index_t j) const;
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


protected:


    std::shared_ptr<std::vector<R>> _array;
    R *                             _data;
    std::vector<uint32>             _strides;
    std::vector<uint32>             _offsets;


};


//-----------------------------------------------------------------------------
// inline implementation

template <class R>
array<R>::
array()
    :
    _array(std::make_shared(std::vector<R>())),
    _data(_array->data()),
    _strides({0}),
    _offsets({0})
{
}


template <class R>
array<R>::
array(const std::vector<uint32> & shape)
    :
    _array(nullptr),
    _data(nullptr),
    _strides({0}),
    _offsets({0})
{
    std::size_t n_elements = 1;

    for(auto x : shape)
    {
        if(x == 0) continue;
        n_elements *= x;
    }

    _array = std::make_shared(std::vector<R>(n_elements));
    _data = _array->data();

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







} // namespace


#endif