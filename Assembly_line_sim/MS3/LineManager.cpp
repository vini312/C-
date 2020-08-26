
#include <fstream>
#include "LineManager.h"
#include "Utilities.h"

using namespace std;

LineManager::LineManager(string fileName, vector<Workstation*>& assembLine, vector<CustomerOrder>& custOrder)
{
	std::fstream file(fileName);
	std::string line, iniStation, nextStation;
	Utilities util;

	for (size_t i = 0; i < assembLine.size(); ++i)
	{
		AssemblyLine.push_back(std::move(assembLine[i]));
	}

	for (size_t i = 0; i < custOrder.size(); ++i)
	{
		ToBeFilled.push_back(std::move(custOrder[i]));
		++m_cntCustomerOrder;
	}

	while (std::getline(file, line))
	{
		size_t pos = 0;
		bool flag = true;

		iniStation = util.extractToken(line, pos, flag);
		pos = iniStation.size() + 1;
		try
		{
			nextStation = util.extractToken(line, pos, flag);
		}
		catch (...)
		{
			flag = false;
		}

		if (flag)
		{
			for (size_t i = 0; i < assembLine.size(); ++i)
			{
				if (assembLine[i]->getItemName() == iniStation)
				{
					if (!startPointSet)
					{
						startPoint = i;
						startPointSet = true;
					}

					for (size_t j = 0; assembLine[i]->getNextStation() == nullptr && j < assembLine.size(); j++)
					{
						if (assembLine[j]->getItemName() == nextStation)
							assembLine[i]->setNextStation(*assembLine[j]);
					}
				}
			}
		}
	}

	file.close();
}

bool LineManager::run(ostream& os)
{
	bool complete = false;
	static int iteration = 1;
	os << "Line Manager Iteration: " << iteration++ << std::endl;

	if (!ToBeFilled.empty())
	{
		*AssemblyLine[startPoint] += std::move(ToBeFilled.front());
		ToBeFilled.pop_front();
	}

	for (auto& i : AssemblyLine)
		i->runProcess(os);

	for (auto& i : AssemblyLine)
	{
		if (!i->moveOrder())
		{
			CustomerOrder tempOrder;

			if (i->getIfCompleted(tempOrder))
				Completed.push_back(std::move(tempOrder));
		}
	}

	if (Completed.size() == m_cntCustomerOrder && ToBeFilled.empty())
	{
		complete = true;
	}
	
	return complete;
}

void LineManager::displayCompletedOrders(ostream& os) const
{
	for (auto& i : Completed)
		i.display(os);
}

void LineManager::displayStations() const
{
	for (auto& i : AssemblyLine)
		i->display(std::cout);
}

void LineManager::displayStationsSorted() const
{
	Workstation* tempStation = AssemblyLine[startPoint];

	while (tempStation != nullptr)
	{
		tempStation->display(cout);
		tempStation = (Workstation*) tempStation->getNextStation();
	}
}
