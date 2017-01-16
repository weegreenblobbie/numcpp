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

#include <vector>


namespace numcpp
{


class axis_iterator
{

public:

    axis_iterator(uint64 axis_length, const slice & s);

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
axis_iterator(uint64 axis_length, const slice & s)
    :
    _begin(slice_iterator::end())
{
    index_t start = 0;
    index_t stop  = 0;

    switch(s.get_valid_bits())
    {
        // :b
        case 0b010:
        {
            start = 0;
            stop  = s.stop();

            if(stop < 0) stop += axis_length;

            _begin = slice_iterator(
                static_cast<uint64>(start),
                static_cast<uint64>(stop),
                1
            );

            break;
        }

        // 5_s, slice(5)
        case 0b100:
        {
            start = s.start();
            stop  = axis_length;

            if(start < 0) start += axis_length;

            _begin = slice_iterator(
                static_cast<uint64>(start),
                static_cast<uint64>(stop),
                1
            );

            break;
        }

        // a:b
        case 0b110:
        {
            start = s.start();
            stop  = s.stop();
            index_t step = 1;

            std::cout
                << "start = " << start << "\n"
                << "stop  = " << stop << "\n"
                << "step  = " << step << std::endl;

            if(start < 0) start += axis_length;
            if(stop < 0)  stop  += axis_length;

            std::cout
                << "    start = " << start << "\n"
                << "    stop  = " << stop << std::endl;

            if(stop <= start)
            {
                // invalid range
                break;
            }

            if(static_cast<uint64>(start) >= axis_length)
            {
                // invalid range
                break;
            }

            if(static_cast<uint64>(stop) >= axis_length)
            {
                stop = axis_length;
            }

            _begin = slice_iterator(
                static_cast<uint64>(start),
                static_cast<uint64>(stop),
                step
            );

            break;
        }

        // a:b:c
        case 0b111:
        {
            start = s.start();
            stop  = s.stop();
            auto step = s.step();

            std::cout
                << "start = " << start << "\n"
                << "stop  = " << stop << "\n"
                << "step  = " << step << std::endl;

            if(start < 0) start += axis_length;
            if(stop < 0)  stop  += axis_length;

            std::cout
                << "    start = " << start << "\n"
                << "    stop  = " << stop << std::endl;

            if(step > 0)
            {
                if(stop <= start)
                {
                    // invalid range
                    break;
                }

                if(static_cast<uint64>(start) >= axis_length)
                {
                    // invalid range
                    break;
                }

                if(static_cast<uint64>(stop) >= axis_length)
                {
                    stop = axis_length;
                }

                _begin = slice_iterator(
                    static_cast<uint64>(start),
                    static_cast<uint64>(stop),
                    step
                );
            }
            else
            if(step < 0)
            {
                if(start <= stop)
                {
                    // invalid range
                    break;
                }

                if(static_cast<uint64>(stop) >= axis_length)
                {
                    // invalid range
                    break;
                }

                if(static_cast<uint64>(start) >= axis_length)
                {
                    start = axis_length - 1;
                }

                _begin = slice_iterator(
                    static_cast<uint64>(start),
                    static_cast<uint64>(stop),
                    step
                );
            }

            break;
        }

        // ::2
        case 0b001:
        {
            _begin = slice_iterator(0, axis_length, s.step());

            break;
        }

        // 6::2
        case 0b101:
        {
            start = s.start();
            stop  = axis_length;

            if(start < 0) start += axis_length;

            auto step = s.step();

            if(step < 0) stop = 0;

            _begin = slice_iterator(start, stop, step);

            break;
        }

        default:
        {
            throw std::runtime_error("oops, missed case");

            break;
        }
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