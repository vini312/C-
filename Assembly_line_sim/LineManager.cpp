

#include "LineManager.h"

LineManager::LineManager(const std::string &str, std::vector<Workstation *> &workstations, std::vector<CustomerOrder> &toBeFilled)
{

	std::fstream file(str);
	std::string line, token;
	Utilities util;

	for (size_t i = 0; i < workstations.size(); ++i)
	{
		AssemblyLine.push_back(std::move(workstations[i]));
	}

	for (size_t i = 0; i < toBeFilled.size(); ++i)
	{
		ToBeFilled.push_back(std::move(toBeFilled[i]));
		++m_cntCustomerOrder;
	}

	while (std::getline(file, line))
	{
		size_t pos = 0;
		bool flag = true;

		token = util.extractToken(line, pos, flag);

		for (size_t i = 0; i < workstations.size(); ++i)
		{

			if (workstations[i]->getItemName() == token)
			{
				first = workstations.size() - i + 1;

				if (pos != 0)
				{
					token = util.extractToken(line, pos, flag);

					for (size_t j = 0; j < workstations.size(); ++j)
					{
						if (workstations[j]->getItemName() == token)
						{
							workstations[i]->setNextStation(*AssemblyLine[j]);
							j = workstations.size();
						}
					}

					i = workstations.size();
				}
			}
		}
	}

	file.close();
}

bool LineManager::run(std::ostream &os)
{
	static int iteration = 1;
	os << "Line Manager Iteration: " << iteration++ << std::endl;

	if (!ToBeFilled.empty())
	{
		*AssemblyLine[first] += std::move(ToBeFilled.front());
		ToBeFilled.pop_front();
	}

	for (const auto &i : AssemblyLine)
	{
		i->runProcess(os);
	}

	for (const auto &i : AssemblyLine)
	{
		if (i->moveOrder())
		{
			CustomerOrder tmp;

			if (i->getCompleted(tmp))
			{
				Completed.push_back(std::move(tmp));
			}
		}
	}

	if (Completed.size() == m_cntCustomerOrder && ToBeFilled.empty())
	{
		return true;
	}
	else
		return false;
}

void LineManager::displayCompletedOrders(std::ostream &os) const
{
	for (const auto &i : Completed)
	{
		i.display(os);
	}
}

void LineManager::displayStations() const
{
	for (const auto &i : AssemblyLine)
	{
		i->display(std::cout);
	}
}

void LineManager::displayStationsSorted() const
{
	Workstation *ptr = AssemblyLine[first];

	while (ptr != nullptr)
	{
		ptr->display(std::cout);
		ptr = (Workstation *)ptr->getNextStation();
	}
}
