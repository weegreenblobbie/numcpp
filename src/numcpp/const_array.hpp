#ifndef _NUMCPP_CONST_ARRAY_HPP_
#define _NUMCPP_CONST_ARRAY_HPP_

#include <numcpp/array.hpp>


namespace numcpp
{

template <class R>
std::ostream & operator<<(std::ostream & out, const const_array<R> & rhs);


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

//~    template <class U=R>
//~    operator typename
//~    std::enable_if<
//~        !std::is_same<bool, U>::value,
//~        const_reference
//~    >::type () const
    operator const_reference () const
    {
        DOUT << __PRETTY_FUNCTION__ << std::endl;

        if(_a._size != 1)
        {
            M_THROW_RT_ERROR("converting to single reference from array!");
        }

        return (*_a._array)[_a._offset];
    }

//~    template <class U=R>
//~    operator typename
//~    std::enable_if<
//~        std::is_same<bool, U>::value,
//~        bool
//~    >::type () const
//~    {
//~        DOUT << __PRETTY_FUNCTION__ << std::endl;

//~        if(_a._size != 1)
//~        {
//~            M_THROW_RT_ERROR("The truth value of an array with more than one element is ambiguous. Use numcpp::any() or numcpp::all()");
//~        }

//~        return (*_a._array)[_a._offset];
//~    }

    array<bool> operator==(const R & rhs) const         { return _a == rhs; }
    array<bool> operator==(const array<R> & rhs) const  { return _a == rhs; }

protected:

    const_array(const array<R> & a) : _a(a) {}

    array<R> _a;

    friend class array<R>;
};


template <>
class const_array<bool>
{

public:

    using value_type      = typename array<bool>::value_type;
    using reference       = typename array<bool>::reference;
    using const_reference = typename array<bool>::const_reference;

//~    const uint32              ndim() const                   { return _a.ndim(); }
//~    std::size_t               size() const                   { return _a.size(); }
//~    const std::vector<uint64> shape() const                  { return _a.shape(); }

    std::string               print(const std::string & fmt_ = "") const { return _a.print(fmt_); }
    std::string               debug_print() const                        { return _a.debug_print(); }

    array<bool> operator==(const bool & rhs) const         { return _a == rhs; }
    array<bool> operator==(const array<bool> & rhs) const  { return _a == rhs; }

    operator bool () const
    {
        DOUT << __PRETTY_FUNCTION__ << std::endl;

        if(_a._size != 1)
        {
            M_THROW_RT_ERROR("The truth value of an array with more than one element is ambiguous. Use numcpp::any() or numcpp::all()");
        }

        return (*_a._array)[_a._offset];
    }

protected:

    const_array(const array<bool> & a) : _a(a) {}

    array<bool> _a;

    friend class array<bool>;
};



//-----------------------------------------------------------------------------
// inline implemenation


template <class R>
std::ostream &
operator<<(std::ostream & out, const const_array<R> & rhs)
{
    return out << rhs.print();
}



} // namespace


#endif // _NUMCPP_CONST_ARRAY_HPP_