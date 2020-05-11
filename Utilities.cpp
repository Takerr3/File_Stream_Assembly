// Tristan Kerr
// Tristan.AlexanderK@gmail.com

#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<algorithm>
#include<vector>
#include<list>
#include <memory>
#include "Utilities.h"
char Utilities::m_delim;
void Utilities::setFieldWidth(size_t width) { m_widthField = width; }
size_t Utilities::getFieldWidth() const { return m_widthField; }
std::string Utilities::extractToken(const std::string& str, size_t& nextPos, bool& TorF) {
	size_t posit = str.find(m_delim, nextPos);
	std::string token = str.substr(nextPos, posit - nextPos);
	if (token != "") {
		if (posit != std::string::npos) { TorF = true; }
		else { TorF = false; }
		nextPos = posit + 1;
		if (m_widthField < token.length()) { m_widthField = token.length(); }
		else { m_widthField = m_widthField; }
	}
	else {
		TorF = false;
		throw "Error" ;
	}
	return token;
}
void Utilities::setDelimiter(char newDelim) { m_delim = newDelim; }
char Utilities::getDelimiter() { return m_delim; }
