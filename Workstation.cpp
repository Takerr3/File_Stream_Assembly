// Tristan Kerr
// Tristan.AlexanderK@gmail.com

#include <iostream>
#include <string>
#include <iomanip>
#include "Workstation.h"

Workstation::Workstation(const std::string& record) :Station(record) { m_pNextStation = nullptr; }
void Workstation::runProcess(std::ostream& os) {
	if (!m_orders.empty()) {
		if (!m_orders.front().isOrderFilled()) { m_orders.front().fillItem(*this, os); }
	}
}
void Workstation::setNextStation(Workstation& station) { m_pNextStation = &station; }
bool Workstation::moveOrder() {
	bool success = false;
	if (!m_orders.empty()) {
		if (m_orders.front().isItemFilled(getItemName()))
		{
			if (m_pNextStation != nullptr) {
				*m_pNextStation += std::move(m_orders.front());
				m_orders.pop_front();
				success = true;
			}
		}
	}
	return success;
}
const Workstation* Workstation::getNextStation() const { return m_pNextStation; }
void Workstation::display(std::ostream& os) {
	if (m_pNextStation != nullptr)
		os << getItemName() << " --> " << m_pNextStation->getItemName() << std::endl;
	else
		os << getItemName() << " --> " << "END OF LINE" << std::endl;
}
bool Workstation::getIfCompleted(CustomerOrder& order) {
	bool success = false;
	if (!m_orders.empty()) {
		if (m_orders.front().isOrderFilled())
		{
			order = std::move(m_orders.front());
			m_orders.pop_front();
			success = true;
		}
	}
	return success;
}
Workstation& Workstation::operator+=(CustomerOrder&& RO) {
	m_orders.push_back(std::move(RO));
	return *this;
}
