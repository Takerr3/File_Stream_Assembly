// Tristan Kerr
// Tristan.AlexanderK@gmail.com

#ifndef SDDS_CUSTOMERORDER_H__
#define SDDS_CUSTOMERORDER_H__
#include <string>
#include "Station.h"
#include "Utilities.h"


   struct Item
   {
      std::string m_itemName;
      unsigned int m_serialNumber = 0;
      bool m_isFilled = false;
      Item(const std::string& src) : m_itemName(src) {};
   };
   class CustomerOrder
   {
      std::string m_name;
      std::string m_product;
      unsigned int m_cntItem;
      Item** m_lstItem = nullptr;
      static size_t m_widthField;
   public:
      CustomerOrder();
      CustomerOrder(std::string& tokens);
      CustomerOrder(CustomerOrder& RO) { throw "Copy Not allowed"; }
      CustomerOrder& operator=(CustomerOrder& RO) = delete;
      CustomerOrder(CustomerOrder&& RO) noexcept;
      CustomerOrder& operator=(CustomerOrder&& RO);
      ~CustomerOrder();
      bool isOrderFilled() const;
      bool isItemFilled(const std::string& itemName) const;
      void fillItem(Station& station, std::ostream& os);
      void display(std::ostream& os) const;
   };


#endif