

#include "Workstation.h"

using namespace std;

Workstation::Workstation(const string &str) : Station(str)
{
	m_pNextStation = nullptr;
}

void Workstation::runProcess(ostream &os)
{
	if (!m_orders.empty())
	{
		if (this->m_orders.front().isOrderFilled() == false)
		{
			this->m_orders.front().fillItem(std::ref(*this), os);
		}
	}
}

bool Workstation::moveOrder()
{
	if (m_orders.empty())
	{
		return false;
	}

	if (m_orders.front().isItemFilled(getItemName()) == true)
	{
		if (m_pNextStation != nullptr)
		{
			*(m_pNextStation) += std::move(m_orders.front());
			m_orders.pop_front();
		}
	}

	return true;
}

void Workstation::setNextStation(Station &station)
{
	m_pNextStation = (Workstation *)&station;
}

const Workstation *Workstation::getNextStation() const
{
	return m_pNextStation;
}

bool Workstation::getCompleted(CustomerOrder &order)
{
	if (!m_orders.empty())
	{
		if (m_orders.front().isOrderFilled() == true)
		{
			order = std::move(m_orders.front());
			m_orders.pop_front();
			return true;
		}
	}

	return false;
}

void Workstation::display(std::ostream &os)
{
	os << getItemName() << " --> "
	   << (m_pNextStation ? m_pNextStation->getItemName() : "END OF LINE") << std::endl;
}

Workstation &Workstation::operator+=(CustomerOrder &&other)
{
	m_orders.push_back(std::move(other));
	return *this;
}
