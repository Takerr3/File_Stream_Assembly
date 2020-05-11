// Tristan Kerr
// Tristan.AlexanderK@gmail.com

#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <iostream>
#include <vector>
#include <string>
#include "Utilities.h"

class Station {
   int m_id;
   int m_serial;
   int m_stock;
   std::string m_name;
   std::string m_des;
   static size_t m_widthField;
   static size_t id_gen;
public:
   Station(const std::string& x);
   const std::string& getItemName() const;
   unsigned int getNextSerialNumber();
   unsigned int getQuantity() const;
   void updateQuantity();
   void display(std::ostream& os, bool full) const;

};
#endif