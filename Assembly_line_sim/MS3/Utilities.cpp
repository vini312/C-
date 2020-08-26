
#include "Utilities.h"

using namespace std;

char Utilities::m_delimiter = '\0';

void Utilities::setFieldWidth(size_t newWidth)
{
	m_widthField = newWidth;
}

size_t Utilities::getFieldWidth() const
{
	return m_widthField;
}

std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
{
	size_t tokenSize = str.find(m_delimiter, next_pos);
	string token = str.substr(next_pos, tokenSize - next_pos);

	if ((more = tokenSize != next_pos) && m_widthField < token.size())
		setFieldWidth(token.size());
	else if(!more)
		throw "error";
	
	return token;
}

void Utilities::setDelimiter(char newDelimiter)
{
	m_delimiter = newDelimiter;
}

char Utilities::getDelimiter()
{
	return m_delimiter;
}
