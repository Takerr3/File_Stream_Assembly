// Tristan Kerr
// Tristan.AlexanderK@gmail.com

#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstring>
#include<algorithm>
#include<vector>
#include<list>
#include <memory>
#include "Station.h"
size_t Station::m_widthField = 0; size_t Station::id_gen = 0;
Station::Station(const std::string& x)
{
   m_id = id_gen + 1;
   Utilities utility;
   char delim = utility.getDelimiter();
   bool TorF = false;
   size_t begin = 0;
   size_t ending = x.find(delim);
   m_name = x.substr(begin, ending);
   begin = ending + 1;
   ending = x.find(delim, begin);
   m_serial = stoi(utility.extractToken(x, begin, TorF));
   begin = ending + 1;
   ending = x.find(delim, begin);
   m_stock = stoi(utility.extractToken(x, begin, TorF));
   begin = ending + 1;
   m_des = utility.extractToken(x, begin, TorF);
   if (m_widthField < m_name.length()) {
      m_widthField = m_name.length();
   }
   id_gen++;
}
const std::string& Station::getItemName() const { return m_name; }
unsigned int Station::getNextSerialNumber() { return m_serial++; }
unsigned int Station::getQuantity() const { return m_stock; }
void Station::updateQuantity()
{
   m_stock--;
   if (m_stock < 0) { m_stock = 0; }
}
void Station::display(std::ostream& os, bool full) const
{
   if (full == false) {
      os << "[" << std::setw(3) << std::right << std::setfill('0') << m_id << "] Item: "
         << std::setfill(' ') << std::setw(m_widthField) << std::left
         << m_name << " [" << std::setfill('0') << std::setw(6)
         << std::right << m_serial << "]";
   }
   else {
      os << "[" << std::setw(3) << std::right << std::setfill('0') << m_id << "] Item: "
         << std::setfill(' ') << std::setw(m_widthField) << std::left << m_name
         << " [" << std::setfill('0') << std::setw(6) << std::right << m_serial << "] "
         << std::setfill(' ') << "Quantity: " << std::setw(m_widthField) << std::left << m_stock
         << " Description: " << m_des;
   }
   os << std::endl;
}