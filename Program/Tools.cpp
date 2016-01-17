#include "stdafx.h"
#include "Tools.h"
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <algorithm>

#define COIN_ID 16

#define CARDS_IN_DECK 10

using namespace std;

std::mt19937_64 Tools::m_RandomMachine;

bool compareCards(const int &first, const int &second)
{
	return first > second;
}


void Tools::initialize()
{
	random_device rd;
	m_RandomMachine = mt19937_64(rd());
}

void Tools::ltf(const string & text)
{
	if (!LOG)
		return;

	ofstream log_file("log_file.txt", ios_base::out | ios_base::app);
	log_file << text << endl;
}

void Tools::ClearLogFile()
{
	if (!LOG)
		return;

	ofstream log_file("log_file.txt");
	log_file.clear();
}

int Tools::MoveCardFromCollectionToCollection(Collection* from_collection, Collection* to_collection, int card_id)
{
	if (card_id == -1)
		card_id = from_collection->GetRandomCard();

	//cout << "Card id: " << card_id << "\n";

	if (card_id > 0)
	{
		to_collection->AddCard(card_id);
		from_collection->RemoveCard(card_id);
	}

	return card_id;
}

pair<int, int> Tools::ReplaceCardsBetweenCollections(Collection* collection_first, Collection* collection_second, int card_id_first, int card_id_second)
{
	if (card_id_first == -1)
		card_id_first = collection_first->GetRandomCard();

	if (card_id_second == -1)
		card_id_second = collection_second->GetRandomCard();

	auto result = pair<int, int>(card_id_first, card_id_second);

	if (card_id_first > 0 && card_id_second > 0)
	{
		collection_first->RemoveCard(card_id_first);
		collection_second->RemoveCard(card_id_second);

		collection_second->AddCard(card_id_first);
		collection_first->AddCard(card_id_second);
	}

	return result;
}

Collection Tools::GetCommonPartOfTwoCollections(Collection collection_first, Collection collection_second)
{
	Collection result = Collection();

	//sort(begin(collection_first.m_Collection), end(collection_first.m_Collection));
	//sort(begin(collection_second.m_Collection), end(collection_second.m_Collection));

	collection_first.m_Collection.sort();
	collection_second.m_Collection.sort();


	for (auto it = begin(collection_first.m_Collection); it != end(collection_first.m_Collection); ++it)
		if (collection_second.RemoveCard(*it))
			result.AddCard(*it);

	return result;
}

Collection Tools::SubtractFromCollectionCollection(Collection collection_first, Collection collection_second)
{
	//cout << "Pierwsza talia:\n" << collection_first.toString(true) << "Druga talia:\n" << collection_second.toString(true);

	for (auto it = begin(collection_second.m_Collection); it != end(collection_second.m_Collection); ++it)
		collection_first.RemoveCard(*it);

	return collection_first;
}

Collection Tools::SumCollectionWithCollection(Collection collection_first, Collection collection_second)
{
	for (auto it = begin(collection_second.m_Collection); it != end(collection_second.m_Collection); ++it)
		collection_first.AddCard(*it);

	return collection_first;
}

Deck Tools::GetRandomDeckFromCollection(Collection collection, DeckClass dclass) //TODO: deck class!
{
	Collection random_collection = GetRandomCollectionFromCollection(collection, CARDS_IN_DECK);
	Deck random_deck = Deck(random_collection);
	return random_deck;
}

Collection Tools::GetRandomCollectionFromCollection(Collection collection, int collection_elements)
{
	Collection random_collection = Collection();

	for (int cards_count = 0; cards_count < collection_elements && !collection.m_Collection.empty(); ++cards_count)
	{
// 		cout << "CE: " << collection_elements << " CS: " << collection.m_Collection.size() << "\n";
// 		cout << "Getting #" << cards_count << " random card\n";
// 		cout << "CM: " << << "\n";
		Tools::MoveCardFromCollectionToCollection(&collection, &random_collection);	
	}
	return random_collection;
}

bool Tools::FlipTheCoin()
{
	uniform_int_distribution<int> dist(0, 1);
	int rand = dist(m_RandomMachine);
	return (bool)rand;
}

double Tools::GetRandomPercentage()
{
	uniform_real_distribution<double> dist(0.0, 1.0);
	double rand = dist(m_RandomMachine);
	return rand;
}

int Tools::GetRandomInteger(int from, int to)
{
	uniform_int_distribution<int> dist(from, to);
	int rand = dist(m_RandomMachine);
	return rand;
}

void Tools::AddCoinToCollection(Collection * to_collection)
{
	to_collection->AddCard(COIN_ID);
}
