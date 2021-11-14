#ifndef _NUMCPP_ARRAY_VIEW_HPP_
#define _NUMCPP_ARRAY_VIEW_HPP_

#include <numcpp/array.hpp>


namespace numcpp
{


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
// inline implemenation of some class array<R>.


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
// inline implemenation of some class array_view<R>.


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


} // namespace


#endif // _NUMCPP_ARRAY_VIEW_HPP_
