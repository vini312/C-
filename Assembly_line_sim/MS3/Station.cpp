
#include <iomanip>
#include "Station.h"
#include "Utilities.h"

using namespace std;

size_t Station::m_widthField = 0;
size_t Station::id_generator = 0;


Station::Station(const string& line)
{
    Utilities util;
    size_t startPos = 0;
    bool more;

    m_statitionId = ++id_generator;

    m_itemName = util.extractToken(line, startPos, more);
    startPos += m_itemName.size() + 1;

    m_serialNumber = stoi(util.extractToken(line, startPos, more));
    startPos += to_string(m_serialNumber).size() + 1;

    m_qty = stoi(util.extractToken(line, startPos, more));
    startPos += to_string(m_qty).size() + 1;

    if(m_widthField < util.getFieldWidth())
        Station::m_widthField = util.getFieldWidth();

    m_desc = util.extractToken(line, startPos, more);
}

const string& Station::getItemName() const
{
	return m_itemName;
}

unsigned int Station::getNextSerialNumber()
{
	return m_serialNumber++;
}

unsigned int Station::getQuantity() const
{
	return m_qty;
}

void Station::updateQuantity()
{
	if (m_qty > 0 && m_qty--);
}

void Station::display(ostream& os, bool full) const
{
    os << "[" << std::setfill('0') << std::setw(3) << right << m_statitionId
        << "] Item: " << std::setfill(' ') << std::setw(m_widthField) << left << m_itemName
        << " [" << std::setfill('0') << std::setw(6) << right << m_serialNumber << "]";
    if (full)
        os << std::setfill(' ') << " Quantity: " << setw(m_widthField) << left << m_qty
            << " Description: " << m_desc;
    os << endl;
}
