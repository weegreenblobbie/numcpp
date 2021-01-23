#ifndef _NUMCPP_FMT_HPP_
#define _NUMCPP_FMT_HPP_


#ifndef FMT_HEADER_ONLY
    #define FMT_HEADER_ONLY
#endif


// https://github.com/fmtlib/fmt

#include <numcpp/external/fmt/printf.h>
#include <numcpp/external/fmt/format.h>

// Special handling for std::complex.
// Reference: https://github.com/fmtlib/fmt/issues/1467#issuecomment-653094376

#include <complex>
#include <vector>
#include <numeric>
#include <numcpp/external/fmt/ranges.h>

template <typename T, typename Char>
struct fmt::formatter<std::complex<T>, Char> : public fmt::formatter<T, Char> {
    typedef fmt::formatter<T, Char> base;
    enum style { expr, star, pair } style_ = expr;
    fmt::detail::dynamic_format_specs<Char> specs_;
    constexpr auto parse(fmt::format_parse_context& ctx) -> decltype(ctx.begin()) {
        using handler_type =
            fmt::detail::dynamic_specs_handler<fmt::format_parse_context>;
        auto type = fmt::detail::type_constant<T, Char>::value;
        fmt::detail::specs_checker<handler_type> handler(handler_type(specs_, ctx),
                                                         type);
        auto it = ctx.begin();
        if (it != ctx.end()) {
            switch (*it) {
                case '$': style_ = style::expr; ctx.advance_to(++it); break;
                case '*': style_ = style::star; ctx.advance_to(++it); break;
                case ',': style_ = style::pair; ctx.advance_to(++it); break;
                default: break;
            }
        }
        if (style_ != style::pair)
            parse_format_specs(ctx.begin(), ctx.end(), handler);
        // todo: fixup alignment
        return base::parse(ctx);
    }
    template <typename FormatCtx>
    auto format(const std::complex<T>& x, FormatCtx& ctx)
        -> decltype(ctx.out()) {
        format_to(ctx.out(), "(");
        if (x.real() || !x.imag())
            base::format(x.real(), ctx);
        if (x.imag()) {
            if (style_ == style::pair)
                format_to(ctx.out(), ",");
            else if (x.real() && x.imag() >= 0 && specs_.sign != sign::plus)
                format_to(ctx.out(), "+");
            base::format(x.imag(), ctx);
            if (style_ != style::pair) {
                if (style_ == style::star)
                    format_to(ctx.out(), "*i");
                else
                    format_to(ctx.out(), "i");
                if (std::is_same<typename std::decay<T>::type, float>::value)
                    format_to(ctx.out(), "f");
                if (std::is_same<typename std::decay<T>::type,
                                 long double>::value)
                    format_to(ctx.out(), "l");
            }
        }
        return format_to(ctx.out(), ")");
    }
};



#endif // _NUMCPP_FMT_HPP_
