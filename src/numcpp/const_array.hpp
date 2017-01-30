#ifndef _NUMCPP_CONST_ARRAY_HPP_
#define _NUMCPP_CONST_ARRAY_HPP_

#include <numcpp/array.hpp>


namespace numcpp
{


template <class R>
class const_array
{


public:

    using value_type      = typename array<R>::value_type;
    using reference       = typename array<R>::reference;
    using const_reference = typename array<R>::const_reference;

    const uint32              ndim() const                   { return _a.ndim(); }
    std::size_t               size() const                   { return _a.size(); }
    const std::vector<uint64> shape() const                  { return _a.shape(); }

    std::string               print(const std::string & fmt_ = "") const { return _a.print(fmt_); }
    std::string               debug_print() const                        { return _a.debug_print(); }

    operator const_reference () const;

    array<bool> operator==(const R & rhs) const         { return _a == rhs; }
    array<bool> operator==(const array<R> & rhs) const  { return _a == rhs; }

    const_array<R> operator()(slice) const;

protected:

    const_array(const array<R> & a) : _a(a) {}

    array<R> _a;

    friend class array<R>;
};


//-----------------------------------------------------------------------------
// inline implemenation


template <class R>
const_array<R>::operator const_reference () const
{
    DOUT << __PRETTY_FUNCTION__ << std::endl;

    if(_a._size != 1)
    {
        if(std::is_same<bool, R>::value)
        {
            M_THROW_RT_ERROR("The truth value of an array with more than one element is ambiguous. Use numcpp::any() or numcpp::all()");
        }

        M_THROW_RT_ERROR("converting to single reference from array!");
    }

    return (*_a._array)[_a._offset];
}



} // namespace


#endif // _NUMCPP_CONST_ARRAY_HPP_