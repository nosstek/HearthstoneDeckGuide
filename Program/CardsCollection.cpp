#include "stdafx.h"
#include <iostream>

#include "Tools.h"
#include "CardsCollection.h"
#include "Card.h"

#include <string>

using namespace std;

// bool CardsCollection::AddCard(int id, int quantity)
// {
// 	if (id < 0)
// 		return false;
// 
// 	if (quantity <= 0 || quantity > 2)
// 		return false;
// 
// 	auto search = m_Collection.find(id);
// 	if (search != m_Collection.end())
// 	{
// 		if ((search->second + quantity) > 2)
// 			return false;
// 
// 		search->second += quantity;
// 	}
// 	else
// 		m_Collection[id] = quantity;
// 
// 	return true;
// }
// 
// bool CardsCollection::RemoveCard(int id, int quantity)
// {
// 	if (id < 0)
// 		return false;
// 
// 	if (quantity <= 0 || quantity > 2)
// 		return false;
// 
// 	auto search = m_Collection.find(id);
// 	if (search != m_Collection.end())
// 	{
// 		if ((search->second - quantity) < 0)
// 			return false;
// 
// 		search->second -= quantity;
// 
// 		if (search->second == 0)
// 			m_Collection.erase(id);
// 
// 		return true;
// 	}
// 
// 	return false;
// }
// 
// int CardsCollection::GetRandomCard(bool remove_card)
// {
// 	if (DEBUG_INFO) { cout << "Collection size: " << m_Collection.size() << endl; }
// 	if (m_Collection.empty())
// 		return -1;
// 
// 	int rand = Tools::GetRandomInteger(0, m_Collection.size() - 1);
// 
// 	map<int, int>::const_iterator it = m_Collection.begin();
// 	advance(it, rand);
// 
// 	int random_card_id = it->first;
// 	if (remove_card)
// 		RemoveCard(random_card_id);
// 
// 	if (DEBUG_INFO) { cout << "Random: " << rand << " Card id: " << it->first << endl; }
// 
// 	return random_card_id;
// }
// 
// bool CardsCollection::AddCollection(CardsCollection ccolection, int number_of_elements)
// {
// 	bool result = true;
// 	if (number_of_elements == -1)
// 	{
// 		for (map<int, int>::const_iterator it = ccolection.m_Collection.begin(); it != ccolection.m_Collection.end(); ++it)
// 			result = result * AddCard(it->first, it->second);
// 	}
// 	else
// 	{
// 		if (number_of_elements > ccolection.GetCardsCount())
// 			return false;
// 
// 		for (int i = 0; i < number_of_elements; ++i)
// 			result = result * AddCard(ccolection.GetRandomCard(true));
// 	}
// 
// 	return result;
// }
// 
// bool CardsCollection::RemoveCollection(CardsCollection ccolection, int number_of_elements)
// {
// 	bool result = true;
// 	if (number_of_elements == -1)
// 	{
// 		for (map<int, int>::const_iterator it = ccolection.m_Collection.begin(); it != ccolection.m_Collection.end(); ++it)
// 			result = result * RemoveCard(it->first, it->second);
// 	}
// 	else
// 	{
// 		if (number_of_elements > ccolection.GetCardsCount())
// 			return false;
// 
// 		for (int i = 0; i < number_of_elements; ++i)
// 			result = result * RemoveCard(ccolection.GetRandomCard(true));
// 	}
// 
// 	return result;
// }
// 
// int CardsCollection::GetCardsCount()
// {
// 	int cards_count = 0;
// 	for (map<int, int>::const_iterator it = m_Collection.begin(); it != m_Collection.end(); ++it)
// 		cards_count += it->second;
// 	return cards_count;
// }
// 
// std::string CardsCollection::toString(bool with_cards_details) const
// {
// 	string s = "id\tbc\tname\n";
// 	for (map<int, int>::const_iterator it = m_Collection.begin(); it != m_Collection.end(); ++it)
// 		s += (with_cards_details ? Card::s_AllCards[it->first].toString() : to_string(it->first)) + "\t\tx" + to_string(it->second) + "\n";
// 
// 	return s;
// }
// 
// vector<int> CardsCollection::TransladeCollectionToSimpleCollection()
// {
// 	vector<int> result;
// 	for (map<int, int>::const_iterator it = m_Collection.begin(); it != m_Collection.end(); ++it)
// 	{
// 		for (int i = 0; i < it->second; ++i)
// 			result.push_back(it->first);
// 	}
// 	return result;
// }


bool Collection::AddCard(int card_id)
{
	if (GetCardQuantity(card_id) > 2)
	{
		cout << "ERROR: Already 2 cards in deck!\n";
		return false;
	}

	//cout << "Added card " << card_id << "\n";
	m_Collection.push_back(card_id);
	return true;
}

bool Collection::RemoveCard(int card_id)
{
	auto it = find(begin(m_Collection), end(m_Collection), card_id);
	if (it == end(m_Collection))
	{
		//cout << "ERROR: no card to delete!\n";
		return false;
	}
	else
		m_Collection.erase(it);

	//cout << "Removed card " << card_id << "\n";
	return true;
}

int Collection::GetRandomCard(bool remove_card)
{
	if (GetCardsCount() <= 0)
		return -1;

	int r = Tools::GetRandomInteger(GetCardsCount() - 1);
	if (r >= m_Collection.size())
		cout << "ERROR: random number is greater than collection size!\n";

	auto it = begin(m_Collection);
	advance(it, r);

	int card = *it;

	if (remove_card)
		m_Collection.erase(it);

	return card;
}

int Collection::GetCardQuantity(int card_id) const
{
	return  (int)count(begin(m_Collection), end(m_Collection), card_id);
}

bool Collection::AddCollection(Collection col, int number_of_elements)
{
	if (number_of_elements == -1)
	{
		m_Collection.insert(end(m_Collection), begin(col.m_Collection), end(col.m_Collection));
	}
	else if (col.m_Collection.size() > number_of_elements)
	{
		for (int i = 0; i < number_of_elements; ++i)
		{
			if (!AddCard(col.GetRandomCard(true)))
				return false;
		}
	}
	else
	{
		return false;
	}

	return true;
}

bool Collection::RemoveCollection(Collection col, int number_of_elements)
{
	if (number_of_elements == -1)
	{
		for (auto it = begin(col.m_Collection); it != end(col.m_Collection); ++it)
		{
			if (!RemoveCard(*it))
				return false;
		}
	}
	else
	{
		for (int i = 0; i < number_of_elements; ++i)
		{
			if (!RemoveCard(col.GetRandomCard(true)))
				return false;
		}
	}

	return true;
}

string Collection::toString(bool with_cards_details) const
{
	string s = "id\tbc\tname\tcards: " + to_string(GetCardsCount()) + "\n";
	for (auto it = begin(m_Collection); it != end(m_Collection); ++it)
		s += (with_cards_details ? Card::s_AllCards[*it].toString() : to_string(*it) + "\n");

	return s;
}

map<int, Deck> Deck::s_AllDecks;

Deck::Deck()
{
	m_Id = -1;
	m_Name = "";
	m_Class = none;

	m_Wins = 0;
	m_Looses = 0;
}

Deck::Deck(const Collection &collection)
{
	m_Collection = collection.m_Collection;

	m_Id = -1;
	m_Name = "";
	m_Class = none;

	m_Wins = 0;
	m_Looses = 0;
}

Deck::Deck(int id, std::string name, DeckClass deck_class, int wins, int looses)
{
	m_Id = id;
	m_Name = name;
	m_Class = deck_class;

	m_Wins = wins;
	m_Looses = looses;
}

double Deck::GetWinRatio() const 
{
	if (m_Wins == 0)
		return 0.0;

	double wins = (double)m_Wins;
	double looses = (double)m_Looses;

	return wins / (wins + looses);
}

std::string Deck::toString(bool with_cards_details) const
{
	string s = "id: " + to_string(m_Id) + "\tname: " + m_Name + "\tcls: " + to_string(m_Class) + "\twin: " + to_string(m_Wins) + "\tlos: " + to_string(m_Looses) + "\trat: " + to_string(GetWinRatio()) + "\n";

	return s + (with_cards_details ? __super::toString(with_cards_details) : "");
}

DeckWithSupplement::DeckWithSupplement(Collection player_deck, Collection player_collection, bool deck_already_substracted_from_collection)
{
	m_Deck.m_Collection = player_deck.m_Collection;
	
	m_Supplement = deck_already_substracted_from_collection ?
		player_collection : Tools::SubtractFromCollectionCollection(player_collection, player_deck);
}

DeckWithSupplement::DeckWithSupplement(Deck player_deck, Collection player_collection, bool deck_already_substracted_from_collection)
{
	m_Deck = player_deck;
	m_Supplement = deck_already_substracted_from_collection ?
		player_collection : Tools::SubtractFromCollectionCollection(player_collection, player_deck);
}

bool DeckWithSupplement::AddCard(int id)
{
	if (m_Deck.AddCard(id))
		return m_Supplement.RemoveCard(id);

	return false;
}

bool DeckWithSupplement::RemoveCard(int id)
{
	if (m_Deck.RemoveCard(id))
		return m_Supplement.AddCard(id);

	return false;
}

string DeckWithSupplement::toString(bool with_cards_details) const
{
	return "Deck: " + m_Deck.toString(with_cards_details) + "Supplement: " + m_Supplement.toString(with_cards_details);
}
