// Tristan Kerr
// Tristan.AlexanderK@gmail.com

#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H
#include <iostream>
#include <vector>
#include <string>

class Utilities {
   size_t m_widthField = 1;
   static char m_delim;

public:
   void setFieldWidth(size_t newWidth);
   size_t getFieldWidth() const;
   std::string extractToken(const std::string& str, size_t& nextPos, bool& TorF);
   static void setDelimiter(char newDelim);
   static char getDelimiter();
};

#endif