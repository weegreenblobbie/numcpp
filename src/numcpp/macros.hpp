#ifndef _NUMCPP_MACROS_HPP_
#define _NUMCPP_MACROS_HPP_

#include <numcpp/fmt.hpp>  // https://github.com/fmtlib/fmt


namespace numcpp
{

static bool _debug_out = false;

} // namespace


#define DOUT if(_debug_out) std::cout << fmt::format("\nDEBUG OUT | {}:({:4d}) | ", __FILE__, __LINE__)

#define M_THROW_RT_ERROR( msg_expr ) \
    {std::stringstream ss; ss << __FILE__ << "(" << __LINE__ << ") " << msg_expr; throw std::runtime_error(ss.str());}


#endif // _NUMCPP_MACROS_HPP_