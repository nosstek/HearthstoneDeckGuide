#include "stdafx.h"

#include "CardsCollection.h"
#include "Card.h"

#include <string>

CardsCollection::CardsCollection()
{
	m_Collection.clear();
}

CardsCollection::~CardsCollection()
{
}

bool CardsCollection::AddCard(int id, int quantity)
{
	if (quantity <= 0 || quantity > 2)
		return false;

	auto search = m_Collection.find(id);
	if (search != m_Collection.end() && (search->second + quantity) <= 2)
		search->second += quantity;
	else
		m_Collection[id] = quantity;

	return true;
}

bool CardsCollection::RemoveCard(int id, int quantity)
{
	if (quantity <= 0 || quantity > 2)
		return false;

	auto search = m_Collection.find(id);
	if (search != m_Collection.end() && (search->second - quantity) >= 0)
	{
		search->second -= quantity;
		if (search->second == 0)
			m_Collection.erase(id);
	}

	return true;
}

std::vector<SimpleCard> CardsCollection::GetSimpleCollection()
{
	std::vector<SimpleCard> result;
	for (std::map<int, int>::const_iterator it = m_Collection.begin(); it != m_Collection.end(); ++it)
		result.push_back(SimpleCard(Card::s_AllCards[it->first].m_BaseCost, it->second, Card::s_AllCards[it->first].m_Overload, Card::s_AllCards[it->first].DrawsCard()));
	return result;
}

std::string CardsCollection::toString() const
{
	std::string s;
	for (std::map<int, int>::const_iterator it = m_Collection.begin(); it != m_Collection.end(); ++it)
		s += std::to_string(it->first) + "\t" + std::to_string(it->second) + "\n";

	return s;
}