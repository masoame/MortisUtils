#include<ConvertString.hpp>

namespace Mortis
{
	std::wstring MultiStringToWideString(UINT CodePage, std::string_view str)
	{
		std::wstring result(MultiByteToWideChar(CodePage, 0, str.data(), -1, nullptr, 0) - 1, L'\0');
		MultiByteToWideChar(CodePage, 0, str.data(), -1, result.data(), static_cast<int>(result.size()));
		return result;
	}

	std::string WideStringToMultiString(UINT CodePage, std::wstring_view str)
	{
		std::string result(WideCharToMultiByte(CodePage, 0, str.data(), -1, nullptr, 0, NULL, NULL) - 1, '\0');
		WideCharToMultiByte(CodePage, 0, str.data(), -1, result.data(), static_cast<int>(result.size()), NULL, NULL);
		return result;
	}

	std::wstring UTF8ToUTF16(std::string_view str)
	{
		return MultiStringToWideString(CP_UTF8, str);
	}

	std::wstring ANSIToUTF16(std::string_view str)
	{
		return MultiStringToWideString(CP_ACP, str);
	}

	std::wstring GBKToUTF16(std::string_view str)
	{
		return MultiStringToWideString(936, str);
	}

	std::string UTF16ToUTF8(std::wstring_view str)
	{
		return WideStringToMultiString(CP_UTF8, str);
	}

	std::string UTF16ToANSI(std::wstring_view str)
	{
		return WideStringToMultiString(CP_ACP, str);
	}

	std::string UTF16ToGBK(std::wstring_view str)
	{
		return WideStringToMultiString(936, str);
	}

}



