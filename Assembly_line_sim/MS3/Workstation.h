
#ifndef WORKSTATION_H
#define WORKSTATION_H

#include <iostream>
#include <deque>
#include "Station.h"
#include "CustomerOrder.h"

class Workstation : public Station {
	std::deque<CustomerOrder> m_orders;
	Workstation* m_pNextStation = nullptr;

public:
	Workstation(const std::string& line);
	Workstation(Workstation&) = delete;
	Workstation(Workstation&&) = delete;
	Workstation& operator=(const Workstation&) = delete;
	Workstation& operator=(const Workstation&&) = delete;
	void runProcess(std::ostream& os);
	bool moveOrder();
	void setNextStation(Station& station);
	const Workstation* getNextStation() const;
	bool getIfCompleted(CustomerOrder& order);
	void display(std::ostream& os);
	Workstation& operator+=(CustomerOrder&& order);
};

#endif // !WORKSTATION_H
