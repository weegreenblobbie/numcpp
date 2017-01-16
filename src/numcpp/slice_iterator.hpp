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

#ifndef _NUMCPP_SLICE_ITERATOR_HPP_
#define _NUMCPP_SLICE_ITERATOR_HPP_


#include <numcpp/types.hpp>


namespace numcpp
{


class slice_iterator
{

public:

    // iterator traits
    using difference_type = uint64;
    using value_type = uint64;
    using pointer = const uint64 *;
    using reference = const uint64 &;
    using iterator_category = std::input_iterator_tag;

    static slice_iterator end() { return slice_iterator(0,0,0); }

    slice_iterator(uint64 start, uint64 stop, int64 step)
        :
        _start(start),
        _stop(stop),
        _step(step)
    {}

    slice_iterator & operator++()
    {
        // forward
        if(_step > 0)
        {
            if(_start + _step < _stop)
            {
                _start += _step;
                return *this;
            }
        }

        // backward
        else
        if(_step < 0)
        {
            if(_start >= _stop - _step)
            {
                _start += _step;
                return *this;
            }
        }

        // stop iteration

        *this = end();

        return *this;
    }

    bool operator==(const slice_iterator & rhs) const
    {
        return
            _start == rhs._start &&
            _stop == rhs._stop &&
            _step == rhs._step;
    }

    bool operator!=(const slice_iterator & rhs) const {return !(*this == rhs);}

    uint64 operator*() {return _start;}

protected:

    uint64 _start;
    uint64 _stop;
    int64 _step;
};


} // namespace


#endif // _NUMCPP_SLICE_ITERATOR_HPP_