#pragma once
#include <string>

namespace dae
{
	namespace ParseUtils
	{
		std::string GetAttributeValue(const std::string& attribute, const std::string& srcString);

		void DeleteAttribute(const std::string& attribute, std::string& srcString);
	}
}
