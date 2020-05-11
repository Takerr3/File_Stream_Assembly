// Tristan Kerr
// Tristan.AlexanderK@gmail.com

#ifndef SDDS_LINEMANAGER_H__
#define SDDS_LINEMANAGER_H__
#include <iostream>
#include <deque> 
#include <vector>
#include "Workstation.h"

class LineManager 
{
	std::vector<Workstation*> AssemblyLine;
	std::deque<CustomerOrder> ToBeFilled;
	std::deque<CustomerOrder> Completed;
	unsigned int m_cntCustomerOrder;
public:
	LineManager(const std::string& name, std::vector<Workstation*>& obj, std::vector<CustomerOrder>& order);
	std::deque<Workstation*> sort(const std::vector<Workstation*>&) const;
	bool run(std::ostream& os);
	void displayCompletedOrders(std::ostream& os) const;
	void displayStations() const;
	void displayStationsSorted() const;
};
#endif 