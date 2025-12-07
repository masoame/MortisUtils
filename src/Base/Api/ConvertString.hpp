#pragma once
#include<string>
#include<functional>

#include<windows.h>
namespace Mortis
{
	std::wstring MultiStringToWideString(UINT CodePage, std::string_view str);
	std::string WideStringToMultiString(UINT CodePage, std::wstring_view str);

	std::wstring UTF8ToUTF16(std::string_view str);
	std::wstring ANSIToUTF16(std::string_view str);
	std::wstring GBKToUTF16(std::string_view str);

	std::string UTF16ToUTF8(std::wstring_view str);
	std::string UTF16ToANSI(std::wstring_view str);
	std::string UTF16ToGBK(std::wstring_view str);

	template<typename TChar>
	constexpr auto ToUpperCaseStdString(std::basic_string_view<TChar> str_view)
		-> std::basic_string<TChar>
	{
		std::basic_string<TChar>  result;
		result.resize(str_view.size());
		std::ranges::transform(str_view, result.begin(),
			[](TChar c) {
				return static_cast<TChar>(std::toupper(c));
			});
		return result;
	}

	template<typename TChar>
	constexpr auto ToLowerCaseStdString(std::basic_string_view<TChar> str_view)
		-> std::basic_string<TChar>
	{
		std::basic_string<TChar> result;
		result.resize(str_view.size());
		std::ranges::transform(str_view, result.begin(),
			[](TChar c)->TChar {
				return static_cast<TChar>(std::tolower(c));
			});
		return result;
	}

	template<typename TChar>
	constexpr bool CaseInsensitiveCompare(std::basic_string_view<TChar> str_view1, std::basic_string_view<TChar> str_view2)
	{
		return ToUpperCaseStdString<TChar>(str_view1) == ToUpperCaseStdString<TChar>(str_view2);
	}

	template<typename TChar>
	struct CaseInsensitiveStdString : std::basic_string<TChar>
	{
		template<typename... Args>
		constexpr CaseInsensitiveStdString(Args&&... args) :
			std::basic_string<TChar>(std::forward<Args>(args)...),
			_lowerStdString(ToLowerCaseStdString<TChar>(dynamic_cast<std::basic_string<TChar>&>(*this)))
		{
		}

		constexpr operator std::basic_string_view<TChar>() const {
			return dynamic_cast<const std::basic_string<TChar>&>(*this);
		}

		constexpr std::basic_string_view<TChar> view() const {
			return dynamic_cast<const std::basic_string<TChar>&>(*this);
		}

		constexpr auto operator <=> (const CaseInsensitiveStdString& other) const noexcept {
			return _lowerStdString <=> other._lowerStdString;
		}

		constexpr void releaseToStdString(std::basic_string<TChar>& target) {
			target = std::move(dynamic_cast<std::basic_string<TChar>&>(*this));
			_lowerStdString.clear();
		}

		constexpr void release(std::basic_string<TChar>& target) {
			dynamic_cast<std::basic_string<TChar>&>(*this).clear();
			_lowerStdString.clear();
		}

		mutable std::basic_string<TChar> _lowerStdString;
	};
}



