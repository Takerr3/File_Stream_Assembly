// Tristan Kerr
// Tristan.AlexanderK@gmail.com

#ifndef SDDS_WORKSTATION_H__
#define SDDS_WORKSTATION_H__
#include <iostream>
#include <deque> 
#include "Station.h"
#include "CustomerOrder.h"

class Workstation :public Station 
{
	std::deque <CustomerOrder> m_orders;
	Workstation* m_pNextStation = nullptr;
public:
	Workstation(const std::string& record);
	Workstation(const Workstation&) = delete;
	Workstation& operator=(const Workstation&) = delete;
	Workstation(Workstation&&) = delete;
	Workstation& operator=(Workstation&&) = delete;
	void runProcess(std::ostream& os);
	bool moveOrder();
	void setNextStation(Workstation& station);
	const Workstation* getNextStation() const;
	bool getIfCompleted(CustomerOrder& order);
	void display(std::ostream& os);
	Workstation& operator+=(CustomerOrder&& RO);
};

#endif