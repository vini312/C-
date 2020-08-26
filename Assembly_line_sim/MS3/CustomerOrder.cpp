#include <iomanip>
#include <algorithm>
#include "CustomerOrder.h"
#include "Utilities.h"

using namespace std;

size_t CustomerOrder::m_widthField = 0;

CustomerOrder::CustomerOrder() {}

CustomerOrder::CustomerOrder(string& line)
{
    Utilities util;
    size_t startPos = 0;
    bool more;

    m_name = util.extractToken(line, startPos, more);
    startPos += m_name.size() + 1;

    m_product = util.extractToken(line, startPos, more);
    startPos += m_product.size() + 1;

    string itemsLine = line.substr(startPos);
    m_cntItem = count(itemsLine.begin(), itemsLine.end(), util.getDelimiter()) + 1;

    if (m_cntItem > 0)
    {
        m_lstItem = new Item * [m_cntItem];

        for (size_t i = 0; i < m_cntItem; i++)
        {
            m_lstItem[i] = new Item(util.extractToken(line, startPos, more));
            startPos += m_lstItem[i]->m_itemName.size() + 1;
        }
    }

    if (m_widthField < util.getFieldWidth())
        CustomerOrder::m_widthField = util.getFieldWidth();
}

CustomerOrder::CustomerOrder(const CustomerOrder& other)
{
    throw "Copy Not allowed";
}

CustomerOrder::CustomerOrder(CustomerOrder&& other) noexcept
{
    *this = move(other);
}

CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other)
{
    if (this != &other)
    {
        for (size_t i = 0; i < m_cntItem; i++)
            delete m_lstItem[i];
        delete[] m_lstItem;
        m_name = other.m_name;
        m_product = other.m_product;
        m_cntItem = other.m_cntItem;

        m_lstItem = other.m_lstItem;
        other.m_lstItem = nullptr;
        other.m_cntItem = 0;
    }

    return *this;
}

CustomerOrder::~CustomerOrder()
{
    for (size_t i = 0; i < m_cntItem; i++)
        delete m_lstItem[i];
    delete[] m_lstItem;
}

bool CustomerOrder::isOrderFilled() const
{
    size_t i = 0;
    while (i < m_cntItem && m_lstItem[i++]->m_isFilled);
    
    return m_lstItem[i - 1]->m_isFilled;
}

bool CustomerOrder::isItemFilled(string item) const
{
    bool filled = true;
    for (size_t i = 0; i < m_cntItem; i++)
    {
        if (m_lstItem[i]->m_itemName == item)
        {
            filled = m_lstItem[i]->m_isFilled;
        }
    }
    return filled;
}

void CustomerOrder::fillItem(Station& station, ostream& os)
{
    for (size_t i = 0; i < m_cntItem; i++)
    {
        if (station.getItemName() == m_lstItem[i]->m_itemName)
        {
            if (station.getQuantity())
            {
                station.updateQuantity();
                m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                m_lstItem[i]->m_isFilled = true;
                os << "    Filled " 
                    << m_name << ", "
                    << m_product << " [" 
                    << station.getItemName() << "]" 
                    << std::endl;
            }
            else
            {
                os << "Unable to fill " 
                    << m_name << ", "
                    << m_product << "[" 
                    << station.getItemName() << "]" 
                    << std::endl;
            }
        }
    }
}

void CustomerOrder::display(ostream& os) const
{
    os << m_name << " - " << m_product << std::endl;

    for (size_t i = 0; i < m_cntItem; i++)
    {
        os << "[" << setw(6) << setfill('0') << right
            << m_lstItem[i]->m_serialNumber << "] "
            << setw(m_widthField) << setfill(' ') << left
            << m_lstItem[i]->m_itemName;

        if (m_lstItem[i]->m_isFilled)
            os << " - FILLED";
        else
            os << " - MISSING";

        os << std::endl;
    }
}
