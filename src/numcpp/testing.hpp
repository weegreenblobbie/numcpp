#ifndef _NUMCPP_TESTING_HPP_
#define _NUMCPP_TESTING_HPP_


#include <numcpp/array.hpp>
#include <numcpp/core.hpp>

#include <stdexcept>


namespace numcpp
{


struct assertion_error : public std::runtime_error
{
    explicit assertion_error( const std::string & message)
        :
        std::runtime_error(message)
    {}
};


template <class R>
void
assert_allclose(
    const array<R> &    actual,
    const array<R> &    desired,
    const R &           rtol,
    const R &           atol = 0,
    bool                equal_nan = false,
    const std::string & err_msg = ""
);


//-----------------------------------------------------------------------------
// inline implementation


template <class R>
void
assert_allclose(
    const array<R> &    actual,
    const array<R> &    desired,
    const R &           rtol,
    const R &           atol,
    bool                equal_nan,
    const std::string & err_msg)
{
    if(equal_nan) M_THROW_RT_ERROR("oops, equal_nan not implemented yet!");

    array<R> diff = actual - desired;

    diff.abs();

    array<bool> mask = diff > atol + rtol * desired;

    if(any(diff > atol + rtol * desired))
    {
        if(err_msg == "")
        {
            auto mask2 = mask.astype<int>();

            throw assertion_error(
                fmt::sprintf(
                    "arrays are not close, %d value(s) out of tolerance",
                    sum(mask2)
                )
            );
        }
        else
        {
            throw assertion_error(err_msg);
        }
    }
}


} // namespace


#endif // _NUMCPP_TESTING_HPP_