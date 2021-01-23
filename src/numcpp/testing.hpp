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
    const std::string & err_msg = "",
    bool                verbose = false
);


template <class R>
void
assert_allclose(
    const array<R> &    actual,
    const array<R> &    desired,
    const R &           rtol,
    const std::string & err_msg
) { assert_allclose(actual, desired, rtol, 0, false, err_msg); }


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
    const std::string & err_msg,
    bool                verbose)
{
    if (equal_nan) M_THROW_RT_ERROR("oops, equal_nan not implemented yet!");
    if (verbose) M_THROW_RT_ERROR("oops, verbose not implemented yet!");

    if (actual.shape() != desired.shape())
    {
        auto msg = fmt::sprintf(
            "(shapes %s, %s mismatch)",
            to_string(actual.shape()),
            to_string(desired.shape())
        );
        throw assertion_error( err_msg + "\n" + msg );
    }

    array<R> diff = actual - desired;

    array<bool> mask = abs(diff) > (atol + rtol * abs(desired));

    if (any(mask))
    {
        if (err_msg == "")
        {
            throw assertion_error(
                fmt::sprintf(
                    "arrays are not close, %d value(s) out of tolerance",
                    sum(mask)
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