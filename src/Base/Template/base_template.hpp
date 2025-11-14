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

	template <typename T>
	struct string_view_type;

	template <typename Traits, typename Alloc>
	struct string_view_type<std::basic_string<char, Traits, Alloc>> {
		using type = std::string_view;
	};

	template <>
	struct string_view_type<const char*> {
		using type = std::string_view;
	};

	template <>
	struct string_view_type<std::string_view> {
		using type = std::string_view;
	};


	// --- Wide Character ---

	template <typename Traits, typename Alloc>
	struct string_view_type<std::basic_string<wchar_t, Traits, Alloc>> {
		using type = std::wstring_view;
	};

	template <>
	struct string_view_type<const wchar_t*> {
		using type = std::wstring_view;
	};

	template <>
	struct string_view_type<std::wstring_view> {
		using type = std::wstring_view;
	};


	template <typename T>
	using string_view_type_t = typename string_view_type<std::remove_cv_t<std::remove_reference_t<T>>>::type;
}