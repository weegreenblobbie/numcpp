#ifndef _NUMCPP_CORE_HPP_
#define _NUMCPP_CORE_HPP_


#include <numcpp/array.hpp>


#include <fmt/fmt.hpp>  // https://github.com/fmtlib/fmt


namespace numcpp
{


bool any(const array<bool> & a);
bool all(const array<bool> & a);



//-----------------------------------------------------------------------------
// inline implementation

inline bool
any(const array<bool> & a)
{
    if(a.ndim() == 1)
    {
        for(index_t i = 0; i < a.size(); ++i)
        {
            bool b = a(i);

            if(b) return true;
        }

        return false;
    }

    throw std::runtime_error(
        fmt::format("{}({}): unhandled case", __FILE__, __LINE__)
    );

    return false;
}


inline bool
all(const array<bool> & a)
{
    if(a.ndim() == 1)
    {
        for(index_t i = 0; i < a.size(); ++i)
        {
            bool b = a(i);

            if(!b) return false;
        }

        return true;
    }

    throw std::runtime_error(
        fmt::format("{}({}): unhandled case", __FILE__, __LINE__)
    );

    return false;
}





} // namespace


#endif // _NUMCPP_CORE_HPP_