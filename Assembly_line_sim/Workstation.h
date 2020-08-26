
#ifndef STD_WORKSTATION_H
#define STD_WORKSTATION_H

#include "CustomerOrder.h"
#include "Station.h"
#include "Utilities.h"

#include <chrono>
#include <string>
#include <deque>
#include <iostream>
#include <functional>
#include <string>

class Workstation : public Station
{
private:
	std::deque<CustomerOrder> m_orders;
	Workstation *m_pNextStation = nullptr;

public:
	Workstation(const std::string &str);

	Workstation &operator=(Workstation &other) = delete;
	Workstation(Workstation &other) = delete;
	Workstation &operator=(Workstation &&other) = delete;
	Workstation(Workstation &&other) = delete;

	void runProcess(std::ostream &os);
	bool moveOrder();
	void setNextStation(Station &station);
	const Workstation *getNextStation() const;
	bool getCompleted(CustomerOrder &order);
	void display(std::ostream &os);
	Workstation &operator+=(CustomerOrder &&other);
};

#endif