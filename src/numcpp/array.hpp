#ifndef _NUMCPP_ARRAY_HPP_
#define _NUMCPP_ARRAY_HPP_

#include <numcpp/axis_iterator.hpp>
#include <numcpp/slice.hpp>
#include <numcpp/types.hpp>

#include <fmt/fmt.hpp>  // https://github.com/fmtlib/fmt

#include <memory>
#include <sstream>
#include <vector>
#include <type_traits>


static bool _debug_out = false;

#define DOUT if(_debug_out) std::cout << fmt::format("\nDEBUG OUT | {}:({:4d}) | ", __FILE__, __LINE__)


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

    operator value_type () const;       // implicitly convert to R
    operator reference ();            // implicitly convert to R &

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
    std::vector<int64>              _strides;
    index_t                         _offset;

    friend class const_array<R>;

    template <typename>
    friend class array;
};


namespace detail
{
    // special helper expression to disable const & for bools

    template <class R>
    struct bool_return_type { using type = const R &; };

    template <>
    struct bool_return_type<bool> { using type = bool; };

} // namespace


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

    DOUT << __PRETTY_FUNCTION__ << std::endl;
}


template <class R>
array<R>::operator array<R>::value_type () const
{
    DOUT << __PRETTY_FUNCTION__ << std::endl;

    if(_size != 1) throw std::runtime_error("converting to single value from array!");

    return (*_array)[_offset];
}


template <class R>
array<R>::operator array<R>::reference ()
{
    DOUT << __PRETTY_FUNCTION__ << std::endl;

    if(_size != 1) throw std::runtime_error("converting to single reference from array!");

    return (*_array)[_offset];
}


template <>
array<bool>::operator bool() const
{
    DOUT << __PRETTY_FUNCTION__ << std::endl;

    if(_size == 0) return false;
    if(_size != 1) throw std::runtime_error("The truth value of an array with more than one element is ambiguous. Use numcpp::any() or numcpp::all()");

    return (*_array)[_offset];
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
array<bool>
array<R>::
operator!() const
{
    DOUT << __PRETTY_FUNCTION__ << std::endl;

//~    std::vector<bool> v(_size, false);
    array<bool> nick(std::vector<bool>(_size, false));

    index_t size_ = static_cast<index_t>(_size);

    if(ndim() == 1)
    {
        for(index_t i = 0; i < size_; ++i)
        {
            (*nick._array)[i] = !(*_array)[_offset + i];
        }

        return nick;
    }
    else
    if(ndim() == 2)
    {
    }
    else
    if(ndim() == 3)
    {
    }

    throw std::runtime_error(
        fmt::format("{}({}): unhandled case", __FILE__, __LINE__)
    );

    return nick;
}



template <class R>
array<bool>
array<R>::
operator==(const R & rhs) const
{
    DOUT << __PRETTY_FUNCTION__ << std::endl;

//~    std::vector<bool> v(_size, false);
    array<bool> nick(std::vector<bool>(_size, false));

    index_t size_ = static_cast<index_t>(_size);

    if(ndim() == 1)
    {
        for(index_t i = 0; i < size_; ++i)
        {
            (*nick._array)[i] = (*_array)[_offset + i] == rhs;
        }

        return nick;
    }
    else
    if(ndim() == 2)
    {
    }
    else
    if(ndim() == 3)
    {
    }

    throw std::runtime_error(
        fmt::format("{}({}): unhandled case", __FILE__, __LINE__)
    );

    return nick;
}


template <class R>
array<bool>
array<R>::
operator==(const array<R> & rhs) const
{
    DOUT << __PRETTY_FUNCTION__ << std::endl;

    if(_size != rhs._size) return array<bool>({false});
    if(_shape != rhs._shape) return array<bool>({false});

    if(ndim() == 1)
    {
        array<bool> nick(std::vector<bool>(_size, false));

        index_t size_ = static_cast<index_t>(_size);

        for(index_t i = 0; i < size_; ++i)
        {
            (*nick._array)[i] = (*_array)[_offset + i] == (*rhs._array)[rhs._offset + i];
        }

        return nick;
    }
    else
    if(ndim() == 2)
    {
        auto nick = array<bool>(std::vector<bool>(_size, false)).reshape(_shape);

        const index_t M = _shape[0];
        const index_t N = _shape[1];

        for(index_t m = 0; m < M; ++m)
        {
            for(index_t n = 0; n < N; ++n)
            {
                (*nick._array)[m * N + n] = (*rhs._array)[rhs._offset + m * N + n];
            }
        }

        return nick;
    }


    throw std::runtime_error(
        fmt::format("{}({}): unhandled case", __FILE__, __LINE__)
    );

    return array<bool>();
}


template <class R>
array<R> &
array<R>::
operator=(const R & rhs)
{
    DOUT << __PRETTY_FUNCTION__ << std::endl;

    index_t size_ = static_cast<index_t>(_size);

    if(ndim() == 1)
    {
        for(index_t i = 0; i < size_; ++i)
        {
            (*_array)[_offset + i] = rhs;
        }

        return *this;
    }
    else
    if(ndim() == 2)
    {
    }
    else
    if(ndim() == 3)
    {
    }

    throw std::runtime_error(
        fmt::format("{}({}): unhandled case", __FILE__, __LINE__)
    );

    return *this;
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
    _offset = rhs._offset;
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
operator()(const slice & s_)
{
    DOUT << __PRETTY_FUNCTION__ << std::endl;

    if(_size == 0) throw std::runtime_error("can't slice an empty array");

    array<R> a;

    switch(ndim())
    {
        // 1D -> 1D
        case 1:
        {
            axis_iterator ai(_shape[0], s_);
            auto s = ai.final();

            index_t start = s.start();
            index_t stop = s.stop();
            index_t step = s.step();

            if(step > 0)
            {
                if(start >= stop) return a;

                a._array = _array;

                uint64 count = 0;

                for(auto x : ai)
                {
                    ++count;
                }

                a._shape = {count};
                a._size = count;

                index_t stride = 1;

                if(!_strides.empty()) stride = _strides[0];

                a._offset = _offset + start * stride;

                a._strides = {step + stride - 1};

                return a;
            }
            else
            {
                if(stop >= start) return a;

                a._array = _array;

                uint64 count = 0;

                for(auto x : ai)
                {
                    ++count;
                }

                a._shape = {count};
                a._size = count;

                index_t stride = 1;

                if(!_strides.empty()) stride = _strides[0];

                a._offset = _offset + start * stride;

                a._strides = {step + stride - 1};

                return a;
            }
        }

        // 2D -> 1D
        case 2:
        {
            axis_iterator ai(_shape[0], s_);
            auto s = ai.final();

            index_t start = s.start();
            index_t stop = s.stop();
            index_t step = s.step();

            if(step > 0)
            {
                if(start >= stop) return a;

                a._array = _array;

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

                a._offset = _offset + start * stride * _shape[1];

                a._strides = {step + stride - 1};

                return a;
            }
            else
            {
                if(stop >= start) return a;

                a._array = _array;

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

                a._offset = _offset + start * stride;

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

    throw std::runtime_error(
        fmt::format("{}({}): unhandled case", __FILE__, __LINE__)
    );

    return a;
}


template <class R>
array<R>
array<R>::
operator()(const slice & s0_, const slice & s1_)
{
    DOUT << __PRETTY_FUNCTION__ << std::endl;

    if(_size == 0) throw std::runtime_error("can't slice an empty array");

    switch(ndim())
    {
        case 1:
        {
            throw std::runtime_error("too many indicies for array");
        }

        case 2:
        {
            axis_iterator a0(_shape[0], s0_);
            auto s0 = a0.final();

            axis_iterator a1(_shape[1], s1_);
            auto s1 = a1.final();

            index_t start0 = s0.start();
            index_t stop0  = s0.stop();
            index_t step0  = s0.step();

            index_t start1 = s1.start();
            index_t stop1  = s1.stop();
            index_t step1  = s1.step();

            uint64 count0 = 0;
            uint64 count1 = 0;

            index_t stride0 = 1;
            index_t stride1 = 1;

            if(step0 > 0 and start0 < stop0)
            {
                for(auto x : a0)
                {
                    ++count0;
                }

                if(!_strides.empty()) stride0 = _strides[1];
            }
            else
            if(step0 < 0 and stop0 < start0)
            {
                for(auto x : a1)
                {
                    ++count1;
                }
            }

            if(step1 > 0 and start1 < stop1)
            {
                for(auto x : a1)
                {
                    ++count1;
                }

                if(!_strides.empty()) stride0 = _strides[1];
            }
            else
            if(step1 < 0 and stop1 < start1)
            {
                for(auto x : a1)
                {
                    ++count1;
                }
            }

            //-----------------------------------------------------------------
            // special case size = 1

            if(count0 == 1 && count1 == 1)
            {
                array<R> out;

                out._size = 1;
                out._array = _array;
                out._shape = {1};
                out._offset = _offset + start0 * stride0 + start1;
                out._strides = {step0 + stride0 - 1};

                return out;
            }

            break;
        }

        // 3D -> 2D
        case 3:
        {
            break;
        }
    }

    throw std::runtime_error(
        fmt::format("{}({}): unhandled case", __FILE__, __LINE__)
    );

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

    array<R> & r = const_cast<array<R>&>(*this);

    return const_array<R>(r(s0, s1));
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

    template <> std::string _array_R_to_fmt<bool>()  { return "{}"; }
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

    template <> std::string type_name<bool>() { return "bool"; }

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
    DOUT << __PRETTY_FUNCTION__ << std::endl;

    if(size() > 100) throw std::runtime_error("array to big to print");

    if(ndim() > 2) throw std::runtime_error("fixme");

    std::string fmt_(fmt_in);

    if(fmt_.length() == 0) fmt_ = detail::_array_R_to_fmt<R>();

    std::stringstream out;

    const array<R> & a = *this;

    if(ndim() <= 1)
    {
        if(_size != 1) out << "array([ ";

        for(index_t i = 0; i < _size; ++i)
        {
            out << detail::_format<R>(fmt_, (*_array)[_offset + i]);
            if(_size != 1 && i + 1 < a._size) out << ", ";
        }

        if(_size != 1) out << " ], " << detail::type_name<R>() << ")";
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


template <class R>
std::string
array<R>::
debug_print() const
{
    DOUT << __PRETTY_FUNCTION__ << std::endl;

    std::stringstream ss;

    ss
        << "array:\n"
        << "        R:    " << detail::type_name<R>() << "\n"
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


//-----------------------------------------------------------------------------
// const_array implementation

template <class R>
const_array<R>::operator typename const_array<R>::const_reference () const
{
    DOUT << __PRETTY_FUNCTION__ << std::endl;

    if(_a._size != 1) throw std::runtime_error("converting to single value from array!");

    return (*_a._array)[_a._offset];
}


} // namespace


#endif

// :mode=c++:noTabs=true: