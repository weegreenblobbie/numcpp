#ifndef _NUMCPP_SHAPE_HPP_
#define _NUMCPP_SHAPE_HPP_


#include <numcpp/macros.hpp>
#include <numcpp/types.hpp>


#include <iostream>
#include <vector>


namespace numcpp
{


// forward
class shape_t;

std::ostream & operator<<(std::ostream &, const shape_t & s);


class shape_t
{

public:

    shape_t(const std::initializer_list<std::size_t> & il) : _shape(il) {}
    shape_t(const std::vector<std::size_t> & v)            : _shape(v)  {}

    operator const std::vector<std::size_t> & () const { return _shape; }
    operator std::vector<std::size_t> () const         { return _shape; }
    operator std::vector<std::size_t> & ()             { return _shape; }

    std::size_t operator[](std::size_t i) const        { return _shape[i]; }

    auto begin() const                             { return _shape.cbegin(); }
    auto end() const                               { return _shape.cend(); }

    bool empty() const                             { return _shape.empty(); }

    std::size_t size() const                       { return _shape.size(); }

    bool operator==(const shape_t & rhs) const     { return _shape == rhs._shape; }
    bool operator!=(const shape_t & rhs) const     { return _shape != rhs._shape; }

    shape_t(const shape_t & other) = default;
    shape_t & operator=(const shape_t & rhs) = default;

protected:

    std::vector<std::size_t> _shape;

    friend std::ostream & operator<<(std::ostream &, const shape_t &);
};


//-----------------------------------------------------------------------------
// inline implementation

inline
std::ostream &
operator<<(std::ostream & out, const shape_t & s)
{
    out << "(";

    for(std::size_t i = 0; i < s._shape.size() - 1; ++i)
    {
        out << s._shape[i] << ", ";
    }

    out << s._shape[s._shape.size() - 1] << ")";

    return out;
}


} // namespace


#endif // _NUMCPP_SHAPE_HPP_

// :mode=c++:noTabs=true: