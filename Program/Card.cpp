#include "stdafx.h"
#include "Card.h"

std::map<int,Card> Card::s_AllCards;

Card::Card()
{
}

Card::Card(int id, std::string name, std::string description, int bcost, int overload, CardType ctype, CardQuality cquality, CardClass cclass)
{
	m_Id = id;
	m_Name = name;
	m_Description = description;
	m_BaseCost = bcost;
	m_Overload = overload;
	m_Type = ctype;
	m_Quality = cquality;
	m_Class = cclass;
}

std::string Card::toString() const
{
	std::string s = std::to_string(m_Id) + "\t"  + std::to_string(m_BaseCost) + "\t" + m_Name + "\n";
	return s;
}


Card::~Card()
{
}

int Card::DrawsCard() const
{
	return 0;
}
