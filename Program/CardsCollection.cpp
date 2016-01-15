#include "stdafx.h"
#include <iostream>

#include "Tools.h"
#include "CardsCollection.h"
#include "Card.h"

#include <string>

#define DEBUG_INFO false

using namespace std;

CardsCollection::CardsCollection()
{
	m_Collection.clear();

	random_device rd;
	m_RandomMachine = mt19937_64(rd());
}

CardsCollection::~CardsCollection()
{
}

bool CardsCollection::AddCard(int id, int quantity)
{
	if (id < 0)
		return false;

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
	if (id < 0)
		return false;

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

int CardsCollection::GetRandomCard()
{
	if (DEBUG_INFO) { cout << "Collection size: " << m_Collection.size() << endl; }
	if (m_Collection.empty())
		return -1;

	uniform_int_distribution<int> dist(0, m_Collection.size() - 1);
	int rand = dist(m_RandomMachine);

	map<int, int>::const_iterator it = m_Collection.begin();
	advance(it, rand);

	if (DEBUG_INFO) { cout << "Random: " << rand << " Card id: " << it->first << endl; }

	return it->first;
}

int CardsCollection::GetCardsCount()
{
	int cards_count = 0;
	for (map<int, int>::const_iterator it = m_Collection.begin(); it != m_Collection.end(); ++it)
		cards_count += it->second;
	return cards_count;
}

std::string CardsCollection::toString(bool with_cards_details) const
{
	string s = "id\tbc\tname\n";
	for (map<int, int>::const_iterator it = m_Collection.begin(); it != m_Collection.end(); ++it)
		s += (with_cards_details ? Card::s_AllCards[it->first].toString() : to_string(it->first)) + "\t\tx" + to_string(it->second) + "\n";

	return s;
}

map<int, Deck> Deck::s_AllDecks;

Deck::Deck(int deck_id, std::string name, float win_rate, DeckClass dclass)
{
	m_Id = deck_id;
	m_Name = name;
	m_WinRate = win_rate;
	m_Class = dclass;
}

string Deck::toString() const
{
	string s = to_string(m_Id) + "\t" + m_Name + "\t" + to_string(m_Class) + "\t" + to_string(m_WinRate) + "\n";

	return s + __super::toString();
}
