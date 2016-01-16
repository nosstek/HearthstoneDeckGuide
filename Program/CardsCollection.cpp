#include "stdafx.h"
#include <iostream>

#include "Tools.h"
#include "CardsCollection.h"
#include "Card.h"

#include <string>

#define DEBUG_INFO false

using namespace std;

bool CardsCollection::AddCard(int id, int quantity)
{
	if (id < 0)
		return false;

	if (quantity <= 0 || quantity > 2)
		return false;

	auto search = m_Collection.find(id);
	if (search != m_Collection.end())
	{
		if ((search->second + quantity) > 2)
			return false;

		search->second += quantity;
	}
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
	if (search != m_Collection.end())
	{
		if ((search->second - quantity) < 0)
			return false;

		search->second -= quantity;

		if (search->second == 0)
			m_Collection.erase(id);

		return true;
	}

	return false;
}

int CardsCollection::GetRandomCard(bool remove_card)
{
	if (DEBUG_INFO) { cout << "Collection size: " << m_Collection.size() << endl; }
	if (m_Collection.empty())
		return -1;

	int rand = Tools::GetRandomInteger(0, m_Collection.size() - 1);

	map<int, int>::const_iterator it = m_Collection.begin();
	advance(it, rand);

	int random_card_id = it->first;
	if (remove_card)
		RemoveCard(random_card_id);

	if (DEBUG_INFO) { cout << "Random: " << rand << " Card id: " << it->first << endl; }

	return random_card_id;
}

bool CardsCollection::AddCollection(CardsCollection ccolection, int number_of_elements)
{
	bool result = true;
	if (number_of_elements == -1)
	{
		for (map<int, int>::const_iterator it = ccolection.m_Collection.begin(); it != ccolection.m_Collection.end(); ++it)
			result = result * AddCard(it->first, it->second);
	}
	else
	{
		if (number_of_elements > ccolection.GetCardsCount())
			return false;

		for (int i = 0; i < number_of_elements; ++i)
			result = result * AddCard(ccolection.GetRandomCard(true));
	}

	return result;
}

bool CardsCollection::RemoveCollection(CardsCollection ccolection, int number_of_elements)
{
	bool result = true;
	if (number_of_elements == -1)
	{
		for (map<int, int>::const_iterator it = ccolection.m_Collection.begin(); it != ccolection.m_Collection.end(); ++it)
			result = result * RemoveCard(it->first, it->second);
	}
	else
	{
		if (number_of_elements > ccolection.GetCardsCount())
			return false;

		for (int i = 0; i < number_of_elements; ++i)
			result = result * RemoveCard(ccolection.GetRandomCard(true));
	}

	return result;
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

Deck::Deck(int deck_id, std::string name, DeckClass dclass, int wins, int looses)
{
	m_Id = deck_id;
	m_Name = name;
	m_Class = dclass;

	m_Wins = wins;
	m_Looses = looses;
}

double Deck::GetWinRatio() const 
{
	double wins = (double)m_Wins;
	double looses = (double)m_Looses;

	return wins / (wins + looses);
}

string Deck::toString() const
{
	string s = "id: " + to_string(m_Id) + "\tname: " + m_Name + "\tcls: " + to_string(m_Class) + "\twin: " + to_string(m_Wins) + "\tlos: " + to_string(m_Looses) + "\trat: " + to_string(GetWinRatio()) + "\n";

	return s + __super::toString();
}

DeckWithSupplement::DeckWithSupplement(CardsCollection player_deck, CardsCollection player_collection, bool deck_already_substracted_from_collection)
{
	m_Deck.m_Collection = player_deck.m_Collection;

	m_Supplement = deck_already_substracted_from_collection ?
		player_collection : Tools::SubtractFromCollectionCollection(player_collection, player_deck);
}

DeckWithSupplement::DeckWithSupplement(Deck player_deck, CardsCollection player_collection, bool deck_already_substracted_from_collection)
{
	m_Deck = player_deck;
	m_Supplement = deck_already_substracted_from_collection ?
		player_collection : Tools::SubtractFromCollectionCollection(player_collection, player_deck);
}

bool DeckWithSupplement::AddCard(int id, int quantity)
{
	if (m_Deck.AddCard(id, quantity))
		return m_Supplement.RemoveCard(id, quantity);

	return false;
}

bool DeckWithSupplement::RemoveCard(int id, int quantity)
{
	if (m_Deck.RemoveCard(id, quantity))
		return m_Supplement.AddCard(id, quantity);

	return false;
}