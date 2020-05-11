// Tristan Kerr
// Tristan.AlexanderK@gmail.com

#include <cstring>
#include <algorithm>
#include "Station.h"
#include "Utilities.h"
#include "CustomerOrder.h"
#include <iomanip>
#include <iostream>


   size_t CustomerOrder::m_widthField = 1;
   CustomerOrder::CustomerOrder() {
      m_cntItem = 0u;
      m_name = "";
      m_product = "";
   }
   CustomerOrder::CustomerOrder(std::string& tokens) {
      Utilities m_util;
      char delim = m_util.getDelimiter();
      bool success = false;
      size_t begin = 0;
      size_t ending = tokens.find(delim);
      m_name = tokens.substr(begin, ending);
      begin = ending + 1;
      ending = tokens.find(delim, begin);
      m_product = m_util.extractToken(tokens, begin, success);
      m_cntItem = std::count(tokens.begin(), tokens.end(), m_util.getDelimiter()) - 1;
      if (m_cntItem > 0) {
         m_lstItem = new Item * [m_cntItem];
         for (auto i = 0u; i < this->m_cntItem - 1; i++) {
            begin = ending + 1;
            ending = tokens.find(delim, begin);
            m_lstItem[i] = new Item(m_util.extractToken(tokens, begin, success));
         }
         begin = ending + 1;
         m_lstItem[m_cntItem - 1] = new Item(tokens.substr(begin));
      }
      if (m_widthField < m_util.getFieldWidth()) { m_widthField = m_util.getFieldWidth(); }
   }
   CustomerOrder::CustomerOrder(CustomerOrder&& RO) noexcept { *this = std::move(RO); }
   CustomerOrder& CustomerOrder::operator=(CustomerOrder&& RO) {
      if (this != &RO) {
         m_lstItem = RO.m_lstItem;
         m_name = RO.m_name;
         m_product = RO.m_product;
         m_cntItem = RO.m_cntItem;
         RO.m_lstItem = nullptr;
         RO.m_name = "";
         RO.m_cntItem = 0;
         RO.m_product = "";
      }
      return *this;
   }
   CustomerOrder::~CustomerOrder() { 
      for (size_t i = 0; i < m_cntItem; i++) { delete m_lstItem[i]; }
      delete[] m_lstItem;
   }
   bool CustomerOrder::isOrderFilled() const {
      bool success = true;
      for (auto i = 0u; i < m_cntItem; i++) {
         if (m_lstItem[i]->m_isFilled == false){ success = false; }     
      }
      return success;
   }
   bool CustomerOrder::isItemFilled(const std::string& itemName) const {
      bool success = true;
      for (auto i = 0u; i < this->m_cntItem; i++) {
         if (m_lstItem[i]->m_itemName == itemName) {
            if (m_lstItem[i]->m_isFilled == false) { success = false;}
         }
      }
      return success;
   }
   void CustomerOrder::fillItem(Station& station, std::ostream& os) {
      for (auto i = 0u; i < m_cntItem; i++) {
         if (station.getItemName() == m_lstItem[i]->m_itemName) {
            if (station.getQuantity() > 0) {
               station.updateQuantity();
               m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
               m_lstItem[i]->m_isFilled = true;
               os << "    Filled " << m_name << ", "
                  << m_product << " [" << station.getItemName() << "]" << std::endl;
            }
            else {
               os << "    Unable to fill " << m_name << ", "
                  << m_product << " [" << station.getItemName() << "]" << std::endl;
            }
         }
      }
   }
   void CustomerOrder::display(std::ostream& os) const {
      os << m_name << " - " << m_product << std::endl;
      for (size_t i = 0; i < m_cntItem; i++) {
         os << "[" << std::setw(6) << std::right << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] ";
         os << std::setw(m_widthField) << std::left << std::setfill(' ') << m_lstItem[i]->m_itemName << " - ";
         if (m_lstItem[i]->m_isFilled) os << "FILLED";
         else os << "MISSING";
         os << std::endl;
      }
   }

