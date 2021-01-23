#ifndef _NUMCPP_CONST_ARRAY_HPP_
#define _NUMCPP_CONST_ARRAY_HPP_

#include <numcpp/array.hpp>


namespace numcpp
{

template <class R>
std::ostream & operator<<(std::ostream & out, const const_array<R> & rhs);

namespace {

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


template <class R>
class const_array
{

public:

    using value_type      = typename array<R>::value_type;
    using reference       = typename array<R>::reference;
    using const_reference = typename array<R>::const_reference;

    const uint32       ndim() const                   { return _a->ndim(); }
    std::size_t        size() const                   { return _a->size(); }
    const shape_t &    shape() const                  { return _a->shape(); }

    std::string        print(const std::string & fmt_ = "") const { return _a->print(fmt_); }
    std::string        debug_print() const                        { return _a->debug_print(); }

    array<bool> operator==(const R & rhs) const         { return (*_a) == rhs; }
    array<bool> operator==(const array<R> & rhs) const  { return (*_a) == rhs; }

    const array<R> operator()(const slice & s0) const                                     { return (*_a)(s0); }
    const array<R> operator()(const slice & s0, const slice & s1) const                   { return (*_a)(s0, s1); }
    const array<R> operator()(const slice & s0, const slice & s1, const slice & s2) const { return (*_a)(s0, s1, s2); }

    template <class U=R>
    operator
    typename std::enable_if<!std::is_same<bool, U>::value, value_type>::type () const
    {
        DOUT << __PRETTY_FUNCTION__ << std::endl;

        if(_a->_size != 1)
        {
            M_THROW_RT_ERROR("converting to single value from array!");
        }

        return (*_a->_array)[_a->_offset];
    }

    operator typename const_ref_helper<R>::type () const
    {
        DOUT << __PRETTY_FUNCTION__ << std::endl;

        if(_a->_size != 1)
        {
            if(std::is_same<bool, R>::value)
            {
                M_THROW_RT_ERROR("The truth value of an array with more than one element is ambiguous. Use numcpp::any() or numcpp::all().");
            }
            M_THROW_RT_ERROR("converting to single value from array!");
        }

        return (*_a->_array)[_a->_offset];
    }

protected:

    const_array(const array<R> & a) : _a(std::make_shared<const array<R>>(a)) {}

    std::shared_ptr<const array<R>> _a;

    friend class array<R>;
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