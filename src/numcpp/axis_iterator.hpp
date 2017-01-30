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

    std::vector<uint64> indices() const;      // convience utiltiy

    slice final() const                       { return slice(_start, _stop, _step); }

    index_t size() const; // compute the number of elements in the slice

private:

    slice_iterator _begin;

    index_t _start;
    index_t _stop;
    index_t _step;
};


//-----------------------------------------------------------------------------
// inline implementation


inline
axis_iterator::
axis_iterator(int64 axis_length, const slice & s)
    :
    _begin(slice_iterator::end()),
    _start(0),
    _stop(0),
    _step(0)
{
    // Reference: https://github.com/python/cpython/blob/c30098c8c6014f3340a369a31df9c74bdbacc269/Lib/test/test_slice.py

    if(axis_length == 0) throw std::runtime_error("axis_length can not be 0");

    index_t step = 1;

    if(s.step_valid()) step = s.step();

    if(step == 0) throw std::runtime_error("step can not be 0");

    //-------------------------------------------------------------------------
    // special case for slice(-5)

    if(s.get_valid_bits() == 0b110)
    {
        index_t start = s.start();
        index_t stop  = s.stop();

        if(start < 0 and stop - start == 1)
        {
            start += axis_length;

            // out of bounds still
            if(start < 0) return;

            _start = start;
            _stop = _start + 1;
            _step = 1;

            _begin = slice_iterator(_start, _stop, _step);

            return;
        }
    }

    //-------------------------------------------------------------------------
    // speci

    index_t lower = 0;
    index_t upper = axis_length;

    if(step < 0)
    {
        lower = -1;
        upper = axis_length - 1;
    }

    //-------------------------------------------------------------------------
    // compute start

    index_t start = 0;

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

    index_t stop  = 0;

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
        _start = start;
        _stop = stop;
        _step = step;
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


inline index_t axis_iterator::size() const
{
    index_t s = (_stop - _start);

    if(_step != 0)
    {
        if(s % _step) s += _step;

        s /= _step;
    }

    return s;
}


} // namespace


#endif // _NUMCPP_AXIS_ITERATOR_HPP_