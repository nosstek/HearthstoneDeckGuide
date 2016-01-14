#include "stdafx.h"
#include <iostream>

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

std::string CardsCollection::toString() const
{
	string s;
	for (map<int, int>::const_iterator it = m_Collection.begin(); it != m_Collection.end(); ++it)
		s += to_string(it->first) + "\t" + to_string(it->second) + "\n";

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

Deck Deck::GetRandomDeckFromCollection(CardsCollection collection, DeckClass dclass) //TODO: deck class!
{
	int target_cards_count = 5;
	CardsCollection random_deck;

	for (int cards_count = 0; cards_count != target_cards_count && !collection.m_Collection.empty(); ++cards_count)
	{
		if (DEBUG_INFO) { std::cout << "Getting #" << cards_count << " random card\n"; }
		int random_card = collection.GetRandomCard();

		random_deck.AddCard(random_card);
		collection.RemoveCard(random_card);
	}
	return random_deck;
}

string Deck::toString() const
{
	string s = to_string(m_Id) + "\t" + m_Name + "\t" + to_string(m_Class) + "\t" + to_string(m_WinRate) + "\n";

	return s + __super::toString();
}
