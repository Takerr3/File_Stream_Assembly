// Tristan Kerr
// Tristan.AlexanderK@gmail.com

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include "LineManager.h"

LineManager::LineManager(const std::string& name, std::vector<Workstation*>& obj, std::vector<CustomerOrder>& order) {
	std::fstream file(name);
	if (!file) { throw "Error"; }
	else {
		while (!file.eof()) {
			Utilities util;
			size_t pos = 0;
			bool check = true;
			util.setDelimiter('|');
			std::string nextStat = "";
			std::string str = "";
			std::string stat = "";
			getline(file, str);
			stat = util.extractToken(str, pos, check);
			if (check) { nextStat = util.extractToken(str, pos, check); }
			else { nextStat = ""; }
			for (auto i : obj) {
				if (stat == i->getItemName()) {
					for (auto item : obj) {
						if (item->getItemName() == nextStat) { i->setNextStation(*item); }
					}
				}
			}
		}
	}
	for (auto& i : order) { ToBeFilled.push_back(std::move(i)); }
	AssemblyLine = obj;
	m_cntCustomerOrder = order.size();
}
std::deque<Workstation*> LineManager::sort(const std::vector<Workstation*>& obj) const {
	Workstation* last{};
	std::deque<Workstation*>station;
	while (station.size() != obj.size()) {
		for (size_t i = 0; i < obj.size(); i++) {
			if (obj[i]->getNextStation() == last) {
				station.push_front(obj[i]);
				last = obj[i];
			}
		}
	}
	return station;
}
bool LineManager::run(std::ostream& os) {
	static size_t counter = 1;
	std::deque<Workstation*>station = sort(AssemblyLine);
	os << "Line Manager Iteration: " << counter << std::endl;
	if (!ToBeFilled.empty()) {
		*station.front() += std::move(ToBeFilled.front());
		ToBeFilled.pop_front();
	}
	for (auto i : AssemblyLine) { i->runProcess(os); }
	CustomerOrder customer;
	for (auto i : AssemblyLine) {
		i->moveOrder();
		if (i->getIfCompleted(customer)) { Completed.push_back(std::move(customer)); }
	}
	counter++;
	return Completed.size() == m_cntCustomerOrder;
}
void LineManager::displayCompletedOrders(std::ostream& os) const {
	for (auto& i : Completed) { i.display(os); }
}
void LineManager::displayStations() const {
	for (auto& i : AssemblyLine) { i->display(std::cout); }
}
void LineManager::displayStationsSorted() const {
	std::deque<Workstation*>station = sort(AssemblyLine);
	for (auto& i : station) { i->display(std::cout); }
}