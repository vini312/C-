
#ifndef LINEMANAGER_H
#define LINEMANAGER_H

#include <iostream>
#include <vector>
#include "Workstation.h"

class LineManager {
	std::vector<Workstation*> AssemblyLine;
	std::deque<CustomerOrder> ToBeFilled;
	std::deque<CustomerOrder> Completed;
	unsigned int m_cntCustomerOrder{ 0 };
	size_t startPoint{ 0 };
	bool startPointSet{ 0 };

public:
	LineManager(std::string fileName, std::vector<Workstation*>& assembLine, std::vector<CustomerOrder>& custOrder);
	bool run(std::ostream& os);
	void displayCompletedOrders(std::ostream& os) const;
	void displayStations() const;
	void displayStationsSorted() const;
};

#endif // !LINEMANAGER_H
