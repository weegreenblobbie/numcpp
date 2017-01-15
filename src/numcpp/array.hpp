#ifndef _NUMCPP_ARRAY_HPP_
#define _NUMCPP_ARRAY_HPP_

#include <numcpp/types.hpp>
#include <numcpp/slice.hpp>

#include <fmt/fmt.hpp>  // https://github.com/fmtlib/fmt

#include <initializer_list>
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

    array(const std::initializer_list<R> & il);

    array(const std::vector<uint64> & shape, const R & value = R()); // std::vector like

//~    array(const array & other) = default;

//~    array<R> & operator=(const array & rhs) = default;

//~    array(array && other);
//~
//~    template <class U>
//~    array<U>                  astype() const;
//~
//~    array<R>                  flatten() const;
    const uint32              ndim() const                   { return _shape.size(); }
    std::size_t               size() const                   { return _size; }
    const std::vector<uint64> shape() const                  { return _shape; }
//~    array<R>                  transpose();
//~    array<R>                  T();

    std::string               print(const std::string & fmt_ = "") const;
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

    array<R> operator()(const slice & s);

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

    array();

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
            if(x == 0) throw std::runtime_error("shape contains 0's!");
            s *= x;
        }

        return s;
    }
}


template <class R>
array<R>::
array()
    : _size(0), _array(nullptr), _data(nullptr), _shape(), _strides(), _offsets()
{}


template <class R>
array<R>::
array(const std::initializer_list<R> & il)
    :
    _size(il.size()),
    _array(std::make_shared<std::vector<R>>(il)),
    _data(_array->data()),
    _shape({_size}),
    _strides(),
    _offsets()
{
    if(_size == 0) throw std::runtime_error("initializer list is emtpy!");

    // FIXME: fix strides & offsets
}



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
array<R>
array<R>::
operator()(const slice & s)
{
    array<R> out;


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
    return out << a.print();
}


namespace detail
{
    // defaults for POD values
    template <class T> std::string _array_R_to_fmt() { return "{:g}"; }

    template <> std::string _array_R_to_fmt<int8 >() { return "{:d}"; }
    template <> std::string _array_R_to_fmt<int16>() { return "{:d}"; }
    template <> std::string _array_R_to_fmt<int32>() { return "{:d}"; }
    template <> std::string _array_R_to_fmt<int64>() { return "{:d}"; }

    template <> std::string _array_R_to_fmt<uint8 >() { return "{:d}"; }
    template <> std::string _array_R_to_fmt<uint16>() { return "{:d}"; }
    template <> std::string _array_R_to_fmt<uint32>() { return "{:d}"; }
    template <> std::string _array_R_to_fmt<uint64>() { return "{:d}"; }

    template <> std::string _array_R_to_fmt<float32>() { return "{:11.8f}"; }

    template <> std::string _array_R_to_fmt<complex64>() { return "{:11.8f}+{:.8f}j"; }

    template <> std::string _array_R_to_fmt<complex128>() { return "{:14.11f}+{:.11f}j"; }

    template <class T> std::string _format(const std::string & fmt_, const T & v) { return fmt::format(fmt_, v); }

    template <> std::string _format<complex64>(const std::string & fmt_, const complex64 & v)  { return fmt::format(fmt_, v.real(), v.imag()); }
    template <> std::string _format<complex128>(const std::string & fmt_, const complex128 & v) { return fmt::format(fmt_, v.real(), v.imag()); }

}


template <class R>
std::string
array<R>::
print(const std::string & fmt_in) const
{
    if(size() > 100) throw std::runtime_error("array to big to print");

    if(ndim() > 2) throw std::runtime_error("fixme");

    std::string fmt_(fmt_in);

    if(fmt_.length() == 0) fmt_ = detail::_array_R_to_fmt<R>();

    std::stringstream out;

    const array<R> & a = *this;

    if(ndim() == 1)
    {
        out << "array([ ";

        for(auto i = 0u; i < _size; ++i)
        {
            out << detail::_format(fmt_, a(i));
            if(i + 1 < a.size()) out << ", ";
        }

        out << " ])\n";
    }
    else
    if(ndim() == 2)
    {
        out << "array([\n";

        for(auto i = 0u; i < _shape[0]; ++i)
        {
            out << "    [ ";

            for(auto j = 0u; j < _shape[1]; ++j)
            {
                out << detail::_format(fmt_, a(i, j));
                if(j + 1 < _shape[1]) out << ", ";
            }

            out << " ],\n";
        }

        out << "])";
    }

    return out.str();
}




} // namespace


#endif

// :mode=c++:noTabs=true: