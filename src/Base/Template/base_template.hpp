#pragma once
#include <type_traits>
#include <memory>
namespace Mortis::BT
{
	template <auto F>
	using StaticFunctorWrapper = std::integral_constant<std::decay_t<decltype(F)>, F>;

    template<typename T, typename... Args>
    constexpr auto get_type_positions_impl() {
        constexpr std::size_t count = (std::is_same_v<T, Args> +...);
        std::array<std::size_t, count> result{};
        std::size_t index = 0;

        [&] <std::size_t... Is>(std::index_sequence<Is...>) {
            ((std::is_same_v<T, Args> ? (void)(result[index++] = Is) : void()), ...);
        }(std::make_index_sequence<sizeof...(Args)>{});

        return result;
    }

    template<typename T, typename R, typename... Args>
    constexpr auto get_type_positions(R(*)(Args...)) {
        return get_type_positions_impl<T, Args...>();
    }

    template<typename T, typename C, typename R, typename... Args>
    constexpr auto get_type_positions(R(C::*)(Args...)) {
        return get_type_positions_impl<T, Args...>();
    }

    template<typename T, typename C, typename R, typename... Args>
    constexpr auto get_type_positions(R(C::*)(Args...) noexcept) {
        return get_type_positions_impl<T, Args...>();
    }

    template<typename T, typename C, typename R, typename... Args>
    constexpr auto get_type_positions(R(C::*)(Args...) const) {
        return get_type_positions_impl<T, Args...>();
    }

    template<typename T, typename C, typename R, typename... Args>
    constexpr auto get_type_positions(R(C::*)(Args...) const noexcept) {
        return get_type_positions_impl<T, Args...>();
    }

#include <type_traits>
#include <string>
#include <string_view>

	template <typename T>
	struct extract_char_type;

	template <typename CharT, typename Traits, typename Alloc>
	struct extract_char_type<std::basic_string<CharT, Traits, Alloc>> {
		using type = CharT;
	};

	template <typename CharT, typename Traits>
	struct extract_char_type<std::basic_string_view<CharT, Traits>> {
		using type = CharT;
	};

	template <typename CharT>
	struct extract_char_type<const CharT*> {
		using type = CharT;
	};

	template <typename CharT>
	struct extract_char_type<CharT*> {
		using type = CharT;
	};

	template <typename T>
	using extract_char_type_t = typename extract_char_type<std::remove_cv_t<std::remove_reference_t<T>>>::type;

	template <typename T>
	using derive_string_view_t = typename std::base_string_view<extract_char_type_t<T>>;
}