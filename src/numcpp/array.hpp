#ifndef _NUMCPP_ARRAY_HPP_
#define _NUMCPP_ARRAY_HPP_

#include <numcpp/axis_iterator.hpp>
#include <numcpp/slice.hpp>
#include <numcpp/types.hpp>

#include <fmt/fmt.hpp>  // https://github.com/fmtlib/fmt

#include <initializer_list>
#include <memory>
#include <sstream>
#include <vector>


namespace numcpp
{


// forward

template <class R> class array;
template <class R> class const_array;

template <class R> std::ostream & operator<<(std::ostream &, const array<R> &);
template <class R> std::ostream & operator<<(std::ostream &, const const_array<R> &);


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

    array<R> &                reshape(const std::vector<uint64> & new_shape);

    std::string               print(const std::string & fmt_ = "") const;
    std::string               debug_print() const;

    //-------------------------------------------------------------------------
    // operators

//~    operator R & ();
    operator R() const;

    bool operator==(const R & rhs) const;

//~    bool operator==(const array<R> & rhs) const;

    array<R> & operator=(const R & rhs);


//~
//~    // unary ops
//~
//~    array<R>    operator+() const;
//~    array<R>    operator-() const;
//~    array<R>    operator~() const;
//~    array<bool> operator!() const;
//~

    array<R> operator()(slice);

    const_array<R> operator()(slice) const;


//~    const array<R> operator()(index_t i) const;

//~    R &       operator()(index_t i);
//~    const R & operator()(index_t i) const;

//~    array<R>  operator()(const slice &);


//~    array<R> operator()(index_t i, index_t j);

//~    R &       operator()(index_t i, index_t j);
//~    R &       operator()(index_t i, index_t j, index_t k);
//~    R &       operator()(index_t i, index_t j, index_t k, index_t l);
//~
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

    array();

    std::size_t                     _size;

    std::shared_ptr<std::vector<R>> _array;
    R *                             _data;

    std::vector<uint64>             _shape;
    std::vector<int64>              _strides;
    std::vector<uint64>             _offsets;

    friend class const_array<R>;
};


template <class R>
class const_array
{


public:

    using value_type = R;

    const uint32              ndim() const                   { return _a._size; }
    std::size_t               size() const                   { return _a._size; }
    const std::vector<uint64> shape() const                  { return _a._shape; }

    std::string               print(const std::string & fmt_ = "") const { return _a.print(fmt_); }
    std::string               debug_print() const                        { return _a.debug_print(); }

    operator const R & () const;

    bool operator==(const R & rhs) const                         { return _a._size == 1 && _a._data[0] == rhs; }

    bool operator==(const array<R> & rhs) const                  { return _a == rhs; }

    const_array<R> operator()(slice) const;

protected:

    const_array(const array<R> & a) : _a(a) {}

    array<R> _a;

    friend class array<R>;
};





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

    uint64 _flat_index(
        const std::vector<uint64> & index,
        const std::vector<int64> & strides,
        uint64 offset)
    {
        for(uint64 i = 0; i < index.size(); ++i)
        {
            offset += strides[i] * index[i];
        }

        return offset;
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
}


template <class R>
array<R>::operator R() const
{
    if(_size != 1) throw std::runtime_error("converting to single value from array!");

    return _data[0];
}


template <class R>
array<R> &
array<R>::
reshape(const std::vector<uint64> & shape)
{
    auto s = detail::_compute_size(shape);

    if(_size != s) throw std::runtime_error("total size of new array must be unchanged");

    _shape = shape;

    return *this;
}


template <class R>
bool
array<R>::
operator==(const R & rhs) const
{
    return _size == 1 && _data[0] == rhs;
}


template <class R>
array<R> &
array<R>::
operator=(const R & rhs)
{
    _size = 1;
    _data[0] = rhs;
    _shape = {};
    _offsets = {};
    return *this;
}


//~template <class R>
//~bool
//~array<R>::
//~operator==(const array<R> & rhs) const
//~{
//~    return _data == rhs._data && _shape == rhs._shape
//~}


template <class R>
array<R>
array<R>::
operator()(slice s)
{
    if(_size == 0) throw std::runtime_error("can't slice an empty array");

    array<R> a;

    switch(ndim())
    {
        // 1D -> 1D
        case 1:
        {
            axis_iterator ai(_shape[0], s);
            s = ai.final();

            index_t start = s.start();
            index_t stop = s.stop();
            index_t step = s.step();

            if(step > 0)
            {
                if(start >= stop) return a;

                a._array = _array; // bump shared reference.

                uint64 count = 0;

                for(auto x : ai)
                {
                    ++count;
                }

                a._shape = {count};
                a._size = count;

                index_t stride = 1;

                if(!_strides.empty()) stride = _strides[0];

                a._data = _data + start * stride;

                a._strides = {step + stride - 1};

                return a;
            }
            else
            {
                if(stop >= start) return a;

                a._array = _array; // bump shared reference.

                uint64 count = 0;

                for(auto x : ai)
                {
                    ++count;
                }

                a._shape = {count};
                a._size = count;

                index_t stride = 1;

                if(!_strides.empty()) stride = _strides[0];

                a._data = _data + start * stride;

                a._strides = {step + stride - 1};

                return a;
            }
        }

        // 2D -> 1D
        case 2:
        {
            axis_iterator ai(_shape[0], s);
            s = ai.final();

            index_t start = s.start();
            index_t stop = s.stop();
            index_t step = s.step();

            if(step > 0)
            {
                if(start >= stop) return a;

                a._array = _array; // bump shared reference.

                uint64 count = 0;

                for(auto x : ai)
                {
                    ++count;
                }

                if(count > 1) a._shape = {count, _shape[1]};
                else          a._shape = {_shape[1]};

                a._size = count * _shape[1];

                index_t stride = 1;

                if(!_strides.empty()) stride = _strides[1];

                a._data = _data + start * stride * _shape[1];

                a._strides = {step + stride - 1};

                return a;
            }

            break;
        }

        // 3D -> 2D
        case 3:
        {
            break;
        }

    }

    std::stringstream ss;

    ss << __FILE__ << "(" << __LINE__ << ") unhandled case";

    throw std::runtime_error(ss.str());

    return a;
}


template <class R>
const_array<R>
array<R>::
operator()(slice s) const
{
    array<R> & r = const_cast<array<R>&>(*this);

    return const_array<R>(r(s));
}


//~template <class R>
//~array<R>
//~array<R>::
//~operator()(slice s) const
//~{
//~    array<R> a;

//~    a._size = 1;
//~    a._array = _array; // increase reference count
//~    a._data = _data + s.start();

//~    return a;
//~}



//~template <class R>
//~const R &
//~array<R>::
//~operator()(index_t i) const
//~{
//~    return _data[i];
//~}


//~template <class R>
//~array<R>
//~array<R>::
//~operator()(const slice & s)
//~{
//~    array<R> out;


//~}


//~#ifndef NUMPCPP_NO_NDIM_CHECKS
//~    #define _NUMCPP_ASSERT_DIM_ 0
//~#else
//~    #define _NUMCPP_ASSERT_DIM_ 1
//~#endif

//~namspace detail
//~{
//~    template <int i>
//~    void assert_ndim_matches(uint64 expcted, uint64 actual){};

//~    inline
//~    template <>
//~    void assert_ndim_matches<1>(uint64 expected, uint64 actual)
//~    {
//~        if(expected != actual) throw std::runtime_exception("
//~    }
//~}



//~template <class R>
//~R &
//~array<R>::
//~operator()(index_t i, index_t j)
//~{


//~    return _data[i * _shape[1] + j];
//~}


//~template <class R>
//~const R &
//~array<R>::
//~operator()(index_t i, index_t j) const
//~{
//~    return _data[i * _shape[1] + j];
//~}


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

    template <class T> std::string type_name() { return "unknown"; }

    template <> std::string type_name<int8 >() { return "int8"; }
    template <> std::string type_name<int16>() { return "int16"; }
    template <> std::string type_name<int32>() { return "int32"; }
    template <> std::string type_name<int64>() { return "int64"; }

    template <> std::string type_name<uint8 >() { return "uint8"; }
    template <> std::string type_name<uint16>() { return "uint16"; }
    template <> std::string type_name<uint32>() { return "uint32"; }
    template <> std::string type_name<uint64>() { return "uint64"; }

    template <> std::string type_name<float32>() { return "float32"; }

    template <> std::string type_name<complex64>() { return "complex64"; }

    template <> std::string type_name<complex128>() { return "complex128"; }
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

    if(ndim() <= 1)
    {
        if(_size > 1) out << "array([ ";

        for(auto i = 0u; i < _size; ++i)
        {
            out << detail::_format<R>(fmt_, a(i));
            if(_size > 1 && i + 1 < a._size) out << ", ";
        }

        if(_size > 1) out << " ], " << detail::type_name<R>() << ")\n";
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
//~                out << detail::_format(fmt_, a(i, j));
                if(j + 1 < _shape[1]) out << ", ";
            }

            out << " ],\n";
        }

        out << "])";
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
        << "        R:    " << detail::type_name<R>() << "\n"
        << "    _size:    " << _size << "\n"
        << "    _data:    " << fmt::format(
            "{:16d}",
            reinterpret_cast<uint64>(_data)) << "\n"
        << "    _shape:   (";

    for(const auto & x : _shape) ss << x << ", ";

    ss
        << ")\n"
        << "    _strides: (";

    for(const auto & x : _strides) ss << x << ", ";

    ss
        << ")\n"
        << "    _offsets: (";

    for(const auto & x : _offsets) ss << x << ", ";

    ss << ")";

    return ss.str();
}


//-----------------------------------------------------------------------------
// const_array implementation

template <class R>
const_array<R>::operator const R & () const
{
    if(_a._size != 1) throw std::runtime_error("converting to single value from array!");

    return _a._data[0];
}


//~template <class R>
//~const_array<R>::operator R() const
//~{
//~    if(_a._size != 1) throw std::runtime_error("converting to single value from array!");

//~    return _a._data[0];
//~}


} // namespace


#endif

// :mode=c++:noTabs=true: