#include "ParseUtils.h"
#include <iostream>

using namespace dae;

std::string ParseUtils::GetAttributeValue(const std::string& attribute, const std::string& srcString)
{
	const std::string startSequence{ "<" + attribute + ">" };
	const std::string endSequence{ "</" + attribute + ">" };

	const size_t startPos{ srcString.find(startSequence) + startSequence.size() };
	const size_t endPos{ srcString.find(endSequence) };

	/*assert(startPos != std::string::npos);
	assert(endPos != std::string::npos);*/
	if (startPos == std::string::npos || endPos == std::string::npos)
	{
		std::cout << "string attribute not found\n";
		return "";
	}

	return srcString.substr(startPos, endPos - startPos);
}

void ParseUtils::DeleteAttribute(const std::string& attribute, std::string& srcString)
{
	const std::string startSequence{ "<" + attribute + ">" };
	const std::string endSequence{ "</" + attribute + ">" };

	const size_t startPos{ srcString.find(startSequence) };
	const size_t endPos{ srcString.find(endSequence) + endSequence.size() };

	srcString.erase(startPos, endPos - startPos);
}