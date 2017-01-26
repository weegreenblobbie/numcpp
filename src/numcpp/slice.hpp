//-----------------------------------------------------------------------------
//
// slice.hpp
//
// slice expressions are used to represent a range of index values, these
// expressions are my attempt at mimicking Python slicing.
//
//-----------------------------------------------------------------------------

#ifndef _NUMCPP_SLICE_HPP_
#define _NUMCPP_SLICE_HPP_

#include <numcpp/types.hpp>

#include <bitset>
#include <iostream>
#include <ostream>


namespace numcpp
{


// forward

class slice;

struct missing {};


namespace detail
{
    // helper classes to enable operator expressions for slices.
    class slice_0b100;
    class slice_0b110;
    class slice_0b111;
    class slice_0b___ {};
    class slice_0b__1;
    class slice_0b_1_;
    class slice_0b_11;
    class slice_0b1__;
    class slice_0b1_1;
}


class slice
{

public:

    slice(index_t start_);                                 // 0b11_
    slice(index_t start_, index_t stop_);                  // 0b11_
    slice(index_t start_, index_t stop_, index_t step_);   // 0b111

    slice(missing,        index_t stop_);                  // 0b_1_
    slice(missing,        missing,        index_t step_);  // 0b__1
    slice(index_t start_, missing,        index_t step_);  // 0b1_1

    slice(const slice & copy) = default;

    index_t start() const     { return _start;}
    index_t stop() const      { return _stop;}
    index_t step() const      { return _step;}

    bool start_valid() const    { return _valid[2]; }
    bool stop_valid() const     { return _valid[1]; }
    bool step_valid() const     { return _valid[0]; }

    uint64 get_size(uint64 axis_length) const;

    uint64 get_valid_bits() const  { return static_cast<uint64>(_valid.to_ulong());}

    // operators

    friend std::ostream & operator<<(std::ostream &, const slice &);

    slice operator-() const    { return slice(-_start, -_stop, -_step); }
    slice operator+() const    { return slice(*this); }

    detail::slice_0b100 operator+(index_t rhs) const;
    detail::slice_0b110 operator|(const detail::slice_0b100 & rhs) const;
    detail::slice_0b110 operator|(index_t rhs) const;

    // convert from help objects
    slice(const detail::slice_0b100 &);
    slice(const detail::slice_0b110 &);
    slice(const detail::slice_0b111 &);
    slice(const detail::slice_0b__1 &);
    slice(const detail::slice_0b_1_ &);
    slice(const detail::slice_0b_11 &);
    slice(const detail::slice_0b1__ &);
    slice(const detail::slice_0b1_1 &);

protected:

    index_t         _start;
    index_t         _stop;
    index_t         _step;
    std::bitset<3>  _valid;

};

// literal operator to support these expressions starting with a constant:
//
//     5_s;          // slice(5);                  0b100;
//     0_s | 8;      // slice(0, 8);               0b110
//     2_s | 8 | 3;  // slice(2, 8, 3);            0b111
//

detail::slice_0b100 operator"" _s (unsigned long long int n);


//-----------------------------------------------------------------------------
//
// Python slice expressions:
//
//      :5   // slice(None, 5, None)  start at begin, stop at 5
//      5:   // slice(5, None, None)  start at 5,     stop at end
//      ::2  // slice(None, None, 2)  start at begin, stop at end,   step by 2
//     6::2  // slice(6, None, 2)     start at 6,     stop at end,   step by 2
//
//     :-5   // slice(None, -5, None) start at begin, stop at end-5
//     -5:   // slice(-5, None, None) start at end-5, stop at end
//     ::-2  // slice(None, None, 2)  start at end,   stop at begin, step by -2
//   -6::-2  // slice(6, None, 2)     start at end-6, stop at begin, step by -2
//
// C++ slice expressions using the missing object:
//
//     missing _;   // delcare short hand missing object
//
//     Python            C++
//       :b              _|b;                             (returns slice_0b_1_)
//      a:               a|_;                             (returns slice_0b1__)
//       ::c             _|_|c;                           (returns slice_0b__1)
//      a::c             a|_|c;                           (returns slice_0b1_1)
//

detail::slice_0b_1_ operator|(const missing &, index_t);               //  :b
detail::slice_0b1__ operator|(index_t, const missing &);               // a:
detail::slice_0b___ operator|(const missing &, const missing &);       //  ::c part 1
detail::slice_0b__1 operator|(const detail::slice_0b___ &, index_t);   //  ::c part 2
detail::slice_0b1_1 operator|(const detail::slice_0b1__ &, index_t);   // a::c
detail::slice_0b_11 operator|(const detail::slice_0b_1_ &, index_t);   //  :b:c

//-----------------------------------------------------------------------------
// inline implementations


inline slice::slice(index_t start_)
    :
    _start(start_), _stop(start_+1), _step(), _valid(0b110)
{
    // initializing stop here provides a way to distinguish:
    //
    //      slice(5)    vs    5 | _
}


inline slice::slice(index_t start_, index_t stop_)
    :
    _start(start_), _stop(stop_), _step(), _valid(0b110)
{}


inline slice::slice(index_t start_, index_t stop_, index_t step_)
    :
    _start(start_), _stop(stop_), _step(step_), _valid(0b111)
{}


inline slice::slice(missing, index_t stop_)
    :
    _start(), _stop(stop_), _step(), _valid(0b010)
{}


inline slice::slice(missing, missing, index_t step_)
    :
    _start(), _stop(), _step(step_), _valid(0b001)
{}


inline slice::slice(index_t start_, missing, index_t step_)
    :
    _start(start_), _stop(), _step(step_), _valid(0b101)
{}


inline
std::ostream &
operator<<(std::ostream & out, const slice & s)
{
    out << "slice(";

    if(s.start_valid()) out << s.start();
    else                out << "None";

    out << ", ";

    if(s.stop_valid()) out << s.stop();
    else               out << "None";

    out << ", ";

    if(s.step_valid()) out << s.step();
    else               out << "None";

    return out << ")";
}


//-----------------------------------------------------------------------------
// slice helpers


namespace detail
{


class slice_0b111
{
private:
    slice_0b111(index_t a, index_t b, index_t c) : _a(a), _b(b), _c(c) {}

    index_t _a;
    index_t _b;
    index_t _c;

    friend slice_0b110;
    friend slice;
};


class slice_0b110
{
public:

    slice_0b111 operator|(index_t c) const { return slice_0b111(_a, _b, c); }

private:

    slice_0b110(index_t a, index_t b) : _a(a), _b(b) {}

    index_t _a;
    index_t _b;

    friend slice_0b100;
    friend slice;
};


class slice_0b100
{
public:

    slice_0b110 operator|(index_t b) const { return slice_0b110(_a,b);}

    slice_0b100 operator-() const { return slice_0b100(-_a); }

private:
    slice_0b100(index_t a) : _a(a) {}

    index_t _a;

    friend slice;
    friend slice_0b100 numcpp::operator"" _s (unsigned long long int n);
};


class slice_0b_1_
{
public:


private:
    slice_0b_1_(index_t b) : _b(b) {}

    index_t _b;

    friend slice;
    friend detail::slice_0b_1_ numcpp::operator|(const missing &, index_t);
    friend detail::slice_0b_11 numcpp::operator|(const detail::slice_0b_1_ &, index_t);
};


class slice_0b_11
{
public:


private:
    slice_0b_11(index_t b, index_t c) : _b(b), _c(c) {}

    index_t _b;
    index_t _c;

    friend slice;
    friend detail::slice_0b_11 numcpp::operator|(const detail::slice_0b_1_ &, index_t);
};


class slice_0b__1
{
public:


private:
    slice_0b__1(index_t c) : _c(c) {}

    index_t _c;

    friend slice;
    friend detail::slice_0b__1 numcpp::operator|(const detail::slice_0b___ &, index_t);
};


class slice_0b1_1
{
public:


private:
    slice_0b1_1(index_t a, index_t c) : _a(a), _c(c) {}

    index_t _a;
    index_t _c;

    friend slice;
    friend detail::slice_0b1_1 numcpp::operator|(const detail::slice_0b1__ &, index_t);
};


class slice_0b1__
{
public:


private:
    slice_0b1__(index_t a) : _a(a) {}

    index_t _a;

    friend slice;
    friend detail::slice_0b1__ numcpp::operator|(index_t a, const missing &);
    friend detail::slice_0b1_1 numcpp::operator|(const detail::slice_0b1__ &, index_t);
};


} // namespace


//-----------------------------------------------------------------------------
// slice constructor from helper objects

inline slice::slice(const detail::slice_0b100 & helper)
    :
    _start(helper._a), _stop(helper._a + 1), _step(), _valid(0b110)
{}


inline slice::slice(const detail::slice_0b110 & helper)
    :
    _start(helper._a), _stop(helper._b), _step(), _valid(0b110)
{}


inline slice::slice(const detail::slice_0b111 & helper)
    :
    _start(helper._a), _stop(helper._b), _step(helper._c), _valid(0b111)
{}


inline slice::slice(const detail::slice_0b__1 & helper)
    :
    _start(), _stop(), _step(helper._c), _valid(0b001)
{}


inline slice::slice(const detail::slice_0b_1_ & helper)
    :
    _start(), _stop(helper._b), _step(1), _valid(0b011)
{}


inline slice::slice(const detail::slice_0b_11 & helper)
    :
    _start(), _stop(helper._b), _step(helper._c), _valid(0b011)
{}


inline slice::slice(const detail::slice_0b1__ & helper)
    :
    _start(helper._a), _stop(), _step(), _valid(0b100)
{}


inline slice::slice(const detail::slice_0b1_1 & helper)
    :
    _start(helper._a), _stop(), _step(helper._c), _valid(0b101)
{}


//-----------------------------------------------------------------------------
// slice operators

inline detail::slice_0b110 slice::operator|(index_t rhs) const
{
    return detail::slice_0b110(_start, rhs);
}


inline detail::slice_0b100 slice::operator+(index_t rhs) const
{
    return detail::slice_0b100(_start + rhs);
}


inline detail::slice_0b110 slice::operator|(const detail::slice_0b100 & rhs) const
{
    return detail::slice_0b110(_start, rhs._a);
}


//-----------------------------------------------------------------------------
// custom literal operator

inline detail::slice_0b100 operator"" _s (unsigned long long int n)
{
    return detail::slice_0b100(static_cast<index_t>(n));
}


//-----------------------------------------------------------------------------
// other operators

inline detail::slice_0b_1_ operator|(const missing &, index_t b)
{
    return detail::slice_0b_1_(b);
}


inline detail::slice_0b_11 operator|(const detail::slice_0b_1_ & helper, index_t c)
{
    return detail::slice_0b_11(helper._b, c);
}


inline detail::slice_0b1__ operator|(index_t a, const missing &)
{
    return detail::slice_0b1__(a);
}


inline detail::slice_0b___ operator|(const missing &, const missing &)
{
    return detail::slice_0b___();
}


inline detail::slice_0b__1 operator|(const detail::slice_0b___ &, index_t c)
{
    return detail::slice_0b__1(c);
}


inline detail::slice_0b1_1 operator|(const detail::slice_0b1__ & a, index_t c)
{
    return detail::slice_0b1_1(a._a, c);
}


} // namespace


#endif // _NUMCPP_SLICE_HPP_