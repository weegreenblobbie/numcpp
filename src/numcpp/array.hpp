#ifndef _NUMCPP_ARRAY_HPP_
#define _NUMCPP_ARRAY_HPP_


#include <numcpp/axis_iterator.hpp>
#include <numcpp/fmt.hpp>
#include <numcpp/macros.hpp>
#include <numcpp/slice.hpp>
#include <numcpp/types.hpp>


#include <memory>
#include <sstream>
#include <type_traits>
#include <vector>


namespace numcpp
{


// forward

template <class R> class array;
template <class R> class const_array;

// for printing shape
                   std::ostream & operator<<(std::ostream &, const std::vector<uint64> &);
template <class R> std::ostream & operator<<(std::ostream &, const array<R> &);
template <class R> std::ostream & operator<<(std::ostream &, const const_array<R> &);


template <class R>
class array
{

public:

    using value_type      = typename std::vector<R>::value_type;
    using reference       = typename std::vector<R>::reference;
    using const_reference = typename std::vector<R>::const_reference;

    array(const std::initializer_list<R> & il);
    array(const std::vector<R> & v);

    array(const std::vector<uint64> & shape, const R & value = R()); // std::vector like

    array(const array<R> & other);

    array<R> & operator=(const array<R> & rhs);

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

    operator value_type () const;      // implicitly convert to R
    operator reference ();             // implicitly convert to R &

//~    array<R> operator~() const;
    array<bool> operator!() const;

    array<bool> operator==(const R & rhs) const;

    array<bool> operator==(const array<R> & rhs) const;

    array<bool> operator!=(const R & rhs) const           { return !(*this == rhs); }

    array<bool> operator!=(const array<R> & rhs) const    { return !(*this == rhs); }

    array<R> & operator=(const R & rhs);

    template <typename U>
    array<R> & operator=(const U & rhs);  // used to create compiler error for type mismatch

//~
//~    // unary ops
//~
//~    array<R>    operator+() const;
//~    array<R>    operator-() const;
//~    array<R>    operator~() const;
//~    array<bool> operator!() const;
//~

    array<R> operator()(const slice &);
    array<R> operator()(const slice & s0, const slice & s1);

    const_array<R> operator()(const slice &) const;
    const_array<R> operator()(const slice &, const slice &) const;

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

    std::vector<uint64>             _shape;
    std::vector<index_t>            _strides;
    index_t                         _offset;

    friend class const_array<R>;

    template <typename>
    friend class array;
};


//-----------------------------------------------------------------------------
// inline implementation

namespace detail
{
    template <class R>
    R _compute_size(const std::vector<R> & shape)
    {
        R s = ! shape.empty();

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
    :
    _size(0),
    _array(nullptr),
    _shape(),
    _strides(),
    _offset(0)
{
    DOUT << __PRETTY_FUNCTION__ << std::endl;
}


template <class R>
array<R>::
array(const std::initializer_list<R> & il)
    :
    _size(il.size()),
    _array(std::make_shared<std::vector<R>>(il)),
    _shape({_size}),
    _strides(),
    _offset(0)
{
    DOUT << __PRETTY_FUNCTION__ << std::endl;
}


template <class R>
array<R>::
array(const std::vector<R> & v)
    :
    _size(v.size()),
    _array(std::make_shared<std::vector<R>>(v)),
    _shape({_size}),
    _strides(),
    _offset(0)
{
    DOUT << __PRETTY_FUNCTION__ << std::endl;
}


template <class R>
array<R>::
array(const std::vector<uint64> & shape, const R & value)
    :
    _size(detail::_compute_size(shape)),
    _array(std::make_shared<std::vector<R>>(std::vector<R>(_size, value))),
    _shape(shape),
    _strides(),
    _offset(0)
{
    DOUT << __PRETTY_FUNCTION__ << std::endl;
}


template <class R>
array<R>::
array(const array<R> & other)
    :
    array<R>()
{
    DOUT << __PRETTY_FUNCTION__ << std::endl;

    *this = other;
}


template <class R>
array<R>::operator array<R>::value_type () const
{
    DOUT << __PRETTY_FUNCTION__ << std::endl;

    if(_size != 1)
    {
        if(std::is_same<bool, R>::value)
        {
            M_THROW_RT_ERROR("The truth value of an array with more than one element is ambiguous. Use numcpp::any() or numcpp::all()");
        }

        M_THROW_RT_ERROR("converting to single reference from array!");
    }

    return (*_array)[_offset];
}


template <class R>
array<R>::operator array<R>::reference ()
{
    DOUT << __PRETTY_FUNCTION__ << std::endl;

    if(_size != 1)
    {
        if(std::is_same<bool, R>::value)
        {
            M_THROW_RT_ERROR("The truth value of an array with more than one element is ambiguous. Use numcpp::any() or numcpp::all()");
        }

        M_THROW_RT_ERROR("converting to single reference from array!");
    }

    return (*_array)[_offset];
}


template <class R>
array<R> &
array<R>::
reshape(const std::vector<uint64> & shape)
{
    DOUT << __PRETTY_FUNCTION__ << std::endl;

    auto s = detail::_compute_size(shape);

    if(_size != s) M_THROW_RT_ERROR("total size of new array must be unchanged");

    if(!_strides.empty()) M_THROW_RT_ERROR("trying to reshape a sliced array :(");

    _shape = shape;

    return *this;
}


template <class R>
array<bool>
array<R>::
operator!() const
{
    DOUT << __PRETTY_FUNCTION__ << std::endl;

    array<bool> out(std::vector<bool>(_size, false));

    if(ndim() == 1)
    {
        if(_strides.empty())
        {
            for(uint64 i = 0; i < _size; ++i)
            {
                (*out._array)[i] = !(*_array)[_offset + i];
            }

            return out;
        }

        else
        {
            for(uint64 i = 0; i < _size; ++i)
            {
                (*out._array)[i] = !(*_array)[_offset + i * _strides[0]];
            }

            return out;
        }
    }
    else
    if(ndim() == 2)
    {
        out.reshape(_shape);

        if(_strides.empty())
        {
            for(uint64 m = 0; m < _shape[0]; ++m)
            {
                for(uint64 n = 0; n < _shape[1]; ++n)
                {
                    (*out._array)[m * _shape[1] + n] =
                        !(*_array)[_offset + m * _shape[1] + n];
                }
            }

            return out;
        }
        else
        {
            for(uint64 m = 0; m < _shape[0]; ++m)
            {
                for(uint64 n = 0; n < _shape[1]; ++n)
                {
                    (*out._array)[m * _shape[1] + n] =
                        !(*_array)[_offset + m * _strides[0] + n * _strides[1]];
                }
            }

            return out;
        }
    }

    M_THROW_RT_ERROR("unhandled case"); // LCOV_EXCL_LINE

    return out; // LCOV_EXCL_LINE
}


template <class R>
array<bool>
array<R>::
operator==(const R & rhs) const
{
    DOUT << __PRETTY_FUNCTION__ << std::endl;

    auto out = array<bool>(std::vector<bool>(_size, false)).reshape(_shape);

    if(ndim() == 1)
    {
        if(_strides.empty())
        {
            for(uint64 i = 0; i < _size; ++i)
            {
                (*out._array)[i] = (*_array)[_offset + i] == rhs;
            }

            return out;
        }
        else
        {
            for(uint64 i = 0; i < _size; ++i)
            {
                (*out._array)[i] = (*_array)[_offset + i * _strides[0]] == rhs;
            }

            return out;
        }
    }
    else
    if(ndim() == 2)
    {
        if(_strides.empty())
        {
            for(uint64 m = 0; m < _shape[0]; ++m)
            {
                for(uint64 n = 0; n < _shape[1]; ++n)
                {
                    const R & lhs = (*_array)[_offset + m * _shape[1] + n];

                    (*out._array)[m * _shape[1] + n] = lhs == rhs;
                }
            }

            return out;
        }
        else
        {
            for(uint64 m = 0; m < _shape[0]; ++m)
            {
                for(uint64 n = 0; n < _shape[1]; ++n)
                {
                    const R & lhs = (*_array)[_offset + m * _strides[0] + n * _strides[1]];

                    (*out._array)[m * _shape[1] + n] = lhs == rhs;
                }
            }

            return out;
        }
    }

    M_THROW_RT_ERROR("unhandled case"); // LCOV_EXCL_LINE

    return out;
}


template <class R>
array<bool>
array<R>::
operator==(const array<R> & rhs) const
{
    DOUT << __PRETTY_FUNCTION__ << std::endl;

    if(_size != rhs._size) return array<bool>({false});
    if(_shape != rhs._shape) return array<bool>({false});

    array<bool> out(std::vector<bool>(_size, false));

    if(ndim() == 1)
    {
        const index_t size_ = static_cast<index_t>(_size);

        for(index_t i = 0; i < size_; ++i)
        {
            (*out._array)[i] = bool{(*this)(i) == rhs(i)};
        }

        return out;
    }
    else
    if(ndim() == 2)
    {
        out.reshape(_shape);

        const index_t M = _shape[0];
        const index_t N = _shape[1];

        for(index_t m = 0; m < M; ++m)
        {
            for(index_t n = 0; n < N; ++n)
            {
                (*out._array)[m * N + n] = bool{(*this)(m,n) == rhs(m,n)};
            }
        }

        return out;
    }

    M_THROW_RT_ERROR("unhandled case"); // LCOV_EXCL_LINE

    return array<bool>();
}


template <class R>
array<R> &
array<R>::
operator=(const R & rhs)
{
    DOUT << __PRETTY_FUNCTION__ << std::endl;

    if(ndim() == 1)
    {
        if(_strides.empty())
        {
            for(uint64 i = 0; i < _size; ++i)
            {
                (*_array)[_offset + i] = rhs;
            }

            return *this;
        }
        else
        {
            for(uint64 i = 0; i < _size; ++i)
            {
                (*_array)[_offset + i * _strides[0]] = rhs;
            }

            return *this;
        }
    }
    else
    if(ndim() == 2)
    {
        if(_strides.empty())
        {
            for(uint64 m = 0; m < _shape[0]; ++m)
            {
                for(uint64 n = 0; n < _shape[1]; ++n)
                {
                    (*_array)[_offset + m * _shape[1] + n] = rhs;
                }
            }

            return *this;
        }
        else
        {
            for(uint64 m = 0; m < _shape[0]; ++m)
            {
                for(uint64 n = 0; n < _shape[1]; ++n)
                {
                    (*_array)[_offset + m * _strides[0] + n * _strides[1]] = rhs;
                }
            }

            return *this;
        }
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
array<R> &
array<R>::
operator=(const array<R> & rhs)
{
    DOUT << __PRETTY_FUNCTION__ << std::endl;

    if(this == &rhs) return *this;

    _size = rhs._size;
    _array = rhs._array;
    _shape = rhs._shape;
    _strides = rhs._strides;
    _offset = rhs._offset;

    return *this;
}


template <class R>
array<R>
array<R>::
operator()(const slice & s0)
{
    DOUT << __PRETTY_FUNCTION__ << std::endl;

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

    M_THROW_RT_ERROR("unhandled case (" << n_dim << ")"); // LCOV_EXCL_LINE
}


template <class R>
array<R>
array<R>::
operator()(const slice & s0, const slice & s1)
{
    DOUT << __PRETTY_FUNCTION__ << std::endl;

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
        auto s0_ = a0.final();

        axis_iterator a1(_shape[1], s1);
        auto s1_ = a1.final();

        index_t start0 = s0_.start();
        index_t step0  = s0_.step();

        index_t start1 = s1_.start();
        index_t step1  = s1_.step();

        uint64 count0 = a0.size();
        uint64 count1 = a1.size();

        if(count0 == 0) M_THROW_RT_ERROR("invalid slice along axis 0");
        if(count1 == 0) M_THROW_RT_ERROR("invalid slice along axis 1");

        DOUT << "array<R> out;";
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

    M_THROW_RT_ERROR("unhandled case"); // LCOV_EXCL_LINE

    return array<R>();
}


template <class R>
const_array<R>
array<R>::
operator()(const slice & s) const
{
    DOUT << __PRETTY_FUNCTION__ << std::endl;

    array<R> & r = const_cast<array<R>&>(*this);

    return const_array<R>(r(s));
}


template <class R>
const_array<R>
array<R>::
operator()(const slice & s0, const slice & s1) const
{
    DOUT << __PRETTY_FUNCTION__ << std::endl;

    array<R> & r = const_cast<array<R> &>(*this);

    return const_array<R>(r(s0, s1));
}


template <class R>
std::ostream &
operator<<(std::ostream & out, const array<R> & a)
{
    DOUT << __PRETTY_FUNCTION__ << std::endl;
    return out << a.print();
}


inline
std::ostream &
operator<<(std::ostream & out, const std::vector<uint64> & v)
{
    out << "("; for(auto x : v) out << x << ", ";
    return out << ")";
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
    DOUT << __PRETTY_FUNCTION__ << std::endl;

    if(size() > 100) throw std::runtime_error("array to big to print");

    if(ndim() > 2) throw std::runtime_error("fixme");

    std::string fmt_(fmt_in);

    if(fmt_.length() == 0) fmt_ = detail::_array_R_to_fmt<R>();

    std::stringstream out;

    const array<R> & a = *this;

    switch(ndim())
    {

        case 0:  // fall through
        case 1:
        {
            if(_size != 1) out << "array([ ";

            for(uint64 i = 0; i < _size; ++i)
            {
                out << detail::_format<R>(fmt_, a(i));
                if(_size != 1 && i + 1 < a._size) out << ", ";
            }

            if(_size != 1) out << " ], " << detail::type_name<R>() << ")";

            break;
        }

        case 2:
        {
            if(_size != 1) out << "array([\n";

            for(auto i = 0u; i < _shape[0]; ++i)
            {
                if(_size != 1) out << "    [ ";

                for(auto j = 0u; j < _shape[1]; ++j)
                {
                    const R r = a(i,j);
                    out << detail::_format(fmt_, r); //a(i, j));
                    if(_size != 1 && j + 1 < _shape[1]) out << ", ";
                }

                if(_size != 1) out << " ],\n";
            }

            if(_size != 1) out << "], " << detail::type_name<R>() << ")";

            break;
        }

        default:
        {
            M_THROW_RT_ERROR("unhandled case"); // LCOV_EXCL_LINE
        }
    }

    return out.str();
}


template <class R>
std::string
array<R>::
debug_print() const
{
    DOUT << __PRETTY_FUNCTION__ << std::endl;

    std::stringstream ss;

    ss
        << "array:\n"
        << "    dtype:    " << detail::type_name<R>() << "\n"
        << "    _size:    " << _size << "\n"
        << "    _data:    " << fmt::format(
            "{:16d}",
            reinterpret_cast<uint64>(_array.get())) << "\n"
        << "    _shape:   (";

    for(const auto & x : _shape) ss << x << ", ";

    ss
        << ")\n"
        << "    _strides: (";

    for(const auto & x : _strides) ss << x << ", ";

    ss
        << ")\n"
        << "    _offset: "<< _offset << "\n";

    return ss.str();
}


} // namespace


#endif

// :mode=c++:noTabs=true: