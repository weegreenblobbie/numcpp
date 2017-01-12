#ifndef _NUMCPP_SLICE_HPP_
#define _NUMCPP_SLICE_HPP_

#include <numcpp/types.hpp>

namespace numcpp
{


class _slice_helper0;
class _slice_helper1;
class _slice_helper2;



class slice
{

public:

    slice();

    // slice x0 = 50;
    slice(index_t i0_); // implicit conversion okay?

    slice(index_t i0_, index_t i1_);
    slice(index_t i0_, index_t i1_, index_t step_);

    slice(const slice & copy);

    // convert from slice helper
    slice(const _slice_helper0 & sh);
    slice(const _slice_helper1 & sh);
    slice(const _slice_helper2 & sh);

    index_t i0() const                 { return _i0; }
    index_t i1() const                 { return _i1; }
    index_t step() const               { return _step; }

    // operators

    slice operator-() const            { return slice(-_i0, -_i1, -_step); }
    slice operator+() const            { return slice(*this); }

    _slice_helper0 operator+(index_t rhs) const;
    _slice_helper1 operator|(const _slice_helper0 & rhs) const;
    _slice_helper1 operator|(index_t rhs) const;


protected:

    index_t _i0;
    index_t _i1;
    index_t _step;
};


// custom literals, so expressions like:
//
//     5_s;          // slice(5, 6, 1);
//     0_s | 8;      // slice(0, 8, 1);
//     2_s | 8 | 3;  // slice(2, 8, 3);
//

_slice_helper0 operator"" _s (unsigned long long int n);


//-----------------------------------------------------------------------------
// inline implementations

inline
slice::
slice()
    :
    _i0(0),
    _i1(1),
    _step(1)
{
}


inline
slice::
slice(index_t i0_)
    :
    _i0(i0_),
    _i1(i0_ + 1),
    _step(1)
{
}


inline
slice::
slice(index_t i0_, index_t i1_)
    :
    _i0(i0_),
    _i1(i1_),
    _step(1)
{
}


inline
slice::
slice(index_t i0_, index_t i1_, index_t step_)
    :
    _i0(i0_),
    _i1(i1_),
    _step(step_)
{
}


//-----------------------------------------------------------------------------
// slice helpers


class _slice_helper2
{
private:
    _slice_helper2(index_t a, index_t b, index_t c) : _a(a), _b(b), _c(c) {}

    index_t _a;
    index_t _b;
    index_t _c;

    friend _slice_helper1;
    friend slice;
};


class _slice_helper1
{
public:

    _slice_helper2 operator|(index_t c) const { return _slice_helper2(_a, _b, c); }

private:

    _slice_helper1(index_t a, index_t b) : _a(a), _b(b) {}

    index_t _a;
    index_t _b;

    friend _slice_helper0;
    friend slice;
};


class _slice_helper0
{
public:

    _slice_helper1 operator|(index_t b) const { return _slice_helper1(_a,b);}

    _slice_helper0 operator-() const { return _slice_helper0(-_a); }

private:
    _slice_helper0(index_t a) : _a(a) {}

    index_t _a;

    friend slice;
    friend _slice_helper0 operator"" _s (unsigned long long int n);
};


inline
slice::
slice(const _slice_helper0 & from_slice)
    :
    _i0(from_slice._a),
    _i1(_i0 + 1),
    _step(1)
{
}


inline
slice::
slice(const _slice_helper1 & from_slice)
    :
    _i0(from_slice._a),
    _i1(from_slice._b),
    _step(1)
{
}

inline
slice::
slice(const _slice_helper2 & from_slice)
    :
    _i0(from_slice._a),
    _i1(from_slice._b),
    _step(from_slice._c)
{
}


inline
_slice_helper1
slice::
operator|(index_t rhs) const
{
    return _slice_helper1(_i0, rhs);
}


inline
_slice_helper0
slice::
operator+(index_t rhs) const
{
    return _slice_helper0(_i0 + rhs);
}


inline
_slice_helper1
slice::
operator|(const _slice_helper0 & rhs) const
{
    return _slice_helper1(_i0, rhs._a);
}


//-----------------------------------------------------------------------------
// custom literal operator

_slice_helper0 operator"" _s (unsigned long long int n)
{
    return _slice_helper0(static_cast<index_t>(n));
}



} // namespace

#endif