
#ifndef CUSTOMEROEDER_H
#define CUSTOMEROEDER_H

#include<iostream>
#include<string>
#include "Station.h"

struct Item {
	std::string m_itemName;
	unsigned int m_serialNumber = 0;
	bool m_isFilled = false;

	Item(const std::string& src) : m_itemName(src) {};
};

class CustomerOrder {
	std::string m_name{ 0 };
	std::string m_product{ 0 };
	unsigned int m_cntItem{ 0 };
	Item** m_lstItem{ 0 };
	static size_t m_widthField;
public:
	CustomerOrder();
	CustomerOrder(std::string& line);
	CustomerOrder(const CustomerOrder& other);
	CustomerOrder& operator=(const CustomerOrder& other) = delete;
	CustomerOrder(CustomerOrder&& other) noexcept;
	CustomerOrder& operator=(CustomerOrder&& other);
	~CustomerOrder();
	bool isOrderFilled() const;
	bool isItemFilled(std::string item) const;
	void fillItem(Station& station, std::ostream& os);
	void display(std::ostream& os) const;
};

#endif // !CUSTOMEROEDER_H