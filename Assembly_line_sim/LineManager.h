

#ifndef STD_LINEMANAGER_H
#define STD_LINEMANAGER_H

#include "CustomerOrder.h"
#include "Station.h"
#include "Utilities.h"
#include "Workstation.h"

#include <chrono>
#include <string>
#include <deque>
#include <fstream>
#include <vector>
#include <iostream>
#include <iomanip>
#include <cctype>
#include <sstream>
#include <stdio.h>

class LineManager
{
private:
	size_t first;
	std::vector<Workstation *> AssemblyLine;
	std::deque<CustomerOrder> ToBeFilled;
	std::deque<CustomerOrder> Completed;
	unsigned int m_cntCustomerOrder = 0;

public:
	LineManager(const std::string &str, std::vector<Workstation *> &workstations, std::vector<CustomerOrder> &toBeFilled);
	bool run(std::ostream &os);
	void displayCompletedOrders(std::ostream &os) const;
	void displayStations() const;
	void displayStationsSorted() const;
};

#endif