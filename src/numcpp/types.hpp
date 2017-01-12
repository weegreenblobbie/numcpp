#ifndef _NUMCPP_TYPES_HPP_
#define _NUMCPP_TYPES_HPP_


#include <cstdint>
#include <complex>


namespace numcpp
{

using int8  = std::int8_t;
using int16 = std::int16_t;
using int32 = std::int32_t;
using int64 = std::int64_t;

using uint8  = std::uint8_t;
using uint16 = std::uint16_t;
using uint32 = std::uint32_t;
using uint64 = std::uint64_t;

using float32 = float;
using float64 = double;

using complex64  = std::complex<float32>;
using complex128 = std::complex<float64>;


// I haven't settled on final index type so I'm using this

using index_t = uint64;


} // namespace


#endif