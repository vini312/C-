
#ifndef STATION_H
#define STATION_H

#include <iostream>
#include <string>

class Station {
	int m_statitionId{ 0 };
	std::string m_itemName{ 0 };
	std::string m_desc{ 0 };
	size_t m_serialNumber{ 0 };
	size_t m_qty{ 0 };
	static size_t m_widthField;
	static size_t id_generator;

public:
	Station(const std::string& line);
	const std::string& getItemName() const;
	unsigned int getNextSerialNumber();
	unsigned int getQuantity() const;
	void updateQuantity();
	void display(std::ostream& os, bool full) const;

};

#endif // !STATION_H
