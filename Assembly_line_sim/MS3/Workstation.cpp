
#include "Workstation.h"

using namespace std;

Workstation::Workstation(const string& line) : Station{ line } {}

void Workstation::runProcess(ostream& os)
{
	if (!m_orders.empty() && !m_orders.front().isOrderFilled())
		m_orders.front().fillItem(*this, os);
}

bool Workstation::moveOrder()
{
	bool moved = false;

	if (!m_orders.empty() && m_orders.front().isItemFilled(getItemName()) && m_pNextStation != nullptr)
	{
		*m_pNextStation += move(m_orders.front());
		m_orders.pop_front();
		moved = true;
	}

	return moved;
}

void Workstation::setNextStation(Station& station)
{
	m_pNextStation = (Workstation*)&station;
}

const Workstation* Workstation::getNextStation() const
{
	return m_pNextStation;
}

bool Workstation::getIfCompleted(CustomerOrder& order)
{
	bool placed = false;

	if (!m_orders.empty() && m_orders.front().isOrderFilled())
	{
		order = move(m_orders.front());
		m_orders.pop_front();
		placed = true;
	}
	
	return placed;
}

void Workstation::display(ostream& os)
{
	if(m_pNextStation != nullptr)
		os << getItemName() << " --> " << m_pNextStation->getItemName() << endl;
	else
		os << getItemName() << " --> END OF LINE" << endl;
}

Workstation& Workstation::operator+=(CustomerOrder&& order)
{
	m_orders.push_back(move(order));

	return *this;
}
