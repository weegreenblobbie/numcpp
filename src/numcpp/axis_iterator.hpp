//-----------------------------------------------------------------------------
//
// slice_iterator.hpp
//
// An iterator class to be used by array for indexing over axis.
//
// References:
//
//    "How to correctly implement custom iterators and const_iterators?"
//        http://stackoverflow.com/a/3582733/562106
//
//-----------------------------------------------------------------------------

#ifndef _NUMCPP_AXIS_ITERATOR_HPP_
#define _NUMCPP_AXIS_ITERATOR_HPP_


#include <numcpp/slice.hpp>
#include <numcpp/slice_iterator.hpp>

#include <algorithm>
#include <vector>


namespace numcpp
{


class axis_iterator
{

public:

    axis_iterator(int64 axis_length, const slice & s);

    slice_iterator begin() const              { return _begin; }

    slice_iterator end() const                { return slice_iterator::end(); }

    std::vector<uint64> indices() const;     // convience utiltiy

private:

    slice_iterator _begin;
};


//-----------------------------------------------------------------------------
// inline implementation


inline
axis_iterator::
axis_iterator(int64 axis_length, const slice & s)
    :
    _begin(slice_iterator::end())
{
    // Reference: https://github.com/python/cpython/blob/c30098c8c6014f3340a369a31df9c74bdbacc269/Lib/test/test_slice.py

    index_t start = 0;
    index_t stop  = 0;
    index_t step  = 1;

    if(s.step_valid()) step = s.step();

    if(axis_length == 0) throw std::runtime_error("axis_length can not be 0");
    if(step == 0)        throw std::runtime_error("step can not be 0");

    index_t lower = 0;
    index_t upper = axis_length;

    if(step < 0)
    {
        lower = -1;
        upper = axis_length - 1;
    }

    // compute start

    if(s.start_valid())
    {
        start = s.start();

        if(start < 0) start = std::max(start + axis_length, lower);
        else          start = std::min(start, upper);
    }
    else
    {
        if(step < 0) start = upper;
        else         start = lower;
    }

    // compute stop

    if(s.stop_valid())
    {
        stop = s.stop();

        if(stop < 0) stop = std::max(stop + axis_length, lower);
        else         stop = std::min(stop, upper);
    }
    else
    {
        if(step < 0) stop = lower;
        else         stop = upper;
    }

    if(step > 0 and start >= stop)
    {
        // bad range
    }
    else
    if(step < 0 and stop >= start)
    {
        // bad range
    }
    else
    {
        // good
        _begin = slice_iterator(start, stop, step);
    }
}


inline std::vector<uint64> axis_iterator::indices() const
{
    std::vector<uint64> out;

    axis_iterator tmp = *this;

    for(auto x : tmp)
    {
        out.push_back(x);
    }

    return out;
}


} // namespace


#endif // _NUMCPP_AXIS_ITERATOR_HPP_