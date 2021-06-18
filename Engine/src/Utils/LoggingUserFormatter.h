#pragma once
#include <fmt/core.h>
#include <fmt/format.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

template <>
struct fmt::formatter<glm::vec2> {
    char presentation = 'f';
    constexpr auto parse(format_parse_context& ctx) {
        auto it = ctx.begin(), end = ctx.end();
        if (it != end && (*it == 'f' || *it == 'e')) presentation = *it++;
        if (it != end && *it != '}')
        throw format_error("invalid format");
        return it;
    }
    template <typename FormatContext>
    auto format(const glm::vec2& p, FormatContext& ctx) {
        return format_to(
            ctx.out(),
            presentation == 'f' ? "({:.1f}, {:.1f})" : "({:.1e}, {:.1e})",
            p.x, p.y);
        }
};


template <>
struct fmt::formatter<glm::vec3> {
    char presentation = 'f';
    constexpr auto parse(format_parse_context& ctx) {
        auto it = ctx.begin(), end = ctx.end();
        if (it != end && (*it == 'f' || *it == 'e')) presentation = *it++;
        if (it != end && *it != '}')
        throw format_error("invalid format");
        return it;
    }
    template <typename FormatContext>
    auto format(const glm::vec3& p, FormatContext& ctx) {
        return format_to(
            ctx.out(),
            presentation == 'f' ? "({:.1f}, {:.1f}, {:.1f})" : "({:.1e}, {:.1e}, {:.1e})",
            p.x, p.y, p.z);
        }
};

template <>
struct fmt::formatter<glm::vec4> {
    char presentation = 'f';
    constexpr auto parse(format_parse_context& ctx) {
        auto it = ctx.begin(), end = ctx.end();
        if (it != end && (*it == 'f' || *it == 'e')) presentation = *it++;
        if (it != end && *it != '}')
        throw format_error("invalid format");
        return it;
    }
    template <typename FormatContext>
    auto format(const glm::vec4& p, FormatContext& ctx) {
        return format_to(
            ctx.out(),
            presentation == 'f' ? "({:.1f}, {:.1f}, {:.1f}, {:.1f})" : "({:.1e}, {:.1e}, {:.1e}, {:.1e})",
            p.x, p.y, p.z, p.w);
        }
};
