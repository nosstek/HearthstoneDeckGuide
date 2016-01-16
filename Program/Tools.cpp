#include "stdafx.h"
#include "Tools.h"
#include <iostream>
#include <fstream>
#include <string>
#include <random>

#define DEBUG_INFO false

#define COIN_ID 16

#define CARDS_IN_DECK 10

using namespace std;

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

int Tools::MoveCardFromCollectionToCollection(CardsCollection* from_collection, CardsCollection* to_collection, int card_id)
{
	if (card_id == -1)
		card_id = from_collection->GetRandomCard();

	if (card_id > 0)
	{
		to_collection->AddCard(card_id);
		from_collection->RemoveCard(card_id);
	}

	return card_id;
}

pair<int, int> Tools::ReplaceCardsBetweenCollections(CardsCollection* collection_first, CardsCollection* collection_second, int card_id_first, int card_id_second)
{
	if (card_id_first == -1)
		card_id_first = collection_first->GetRandomCard();

	if (card_id_second == -1)
		card_id_second = collection_second->GetRandomCard();

	pair<int, int> result = pair<int, int>(card_id_first, card_id_second);

	if (card_id_first > 0 && card_id_second > 0)
	{
		collection_first->RemoveCard(card_id_first);
		collection_second->RemoveCard(card_id_second);

		collection_second->AddCard(card_id_first);
		collection_first->AddCard(card_id_second);
	}

	return result;
}

CardsCollection Tools::GetCommonPartOfTwoCollections(CardsCollection collection_first, CardsCollection collection_second)
{
	CardsCollection result = CardsCollection();

	for (map<int, int>::const_iterator it = collection_first.m_Collection.begin(); it != collection_first.m_Collection.end(); ++it)
	{
		for (int card_quantity = it->second; card_quantity > 0; --card_quantity)
			if (collection_second.RemoveCard(it->first))
				result.AddCard(it->first);
	}

	return result;
}

CardsCollection Tools::SubtractFromCollectionCollection(CardsCollection collection_first, CardsCollection collection_second)
{
	for (map<int, int>::const_iterator it = collection_second.m_Collection.begin(); it != collection_second.m_Collection.end(); ++it)
	{
		for (int card_quantity = it->second; card_quantity > 0; --card_quantity)
			collection_first.RemoveCard(it->first);
	}

	return collection_first;
}

CardsCollection Tools::SumCollectionWithCollection(CardsCollection collection_first, CardsCollection collection_second)
{
	for (map<int, int>::const_iterator it = collection_second.m_Collection.begin(); it != collection_second.m_Collection.end(); ++it)
		collection_first.AddCard(it->first, it->second);

	return collection_first;
}

Deck Tools::GetRandomDeckFromCollection(CardsCollection collection, DeckClass dclass) //TODO: deck class!
{
	Deck random_deck = Deck();

	for (int cards_count = 0; cards_count != CARDS_IN_DECK && !collection.m_Collection.empty(); ++cards_count)
	{
		if (DEBUG_INFO) { cout << "Getting #" << cards_count << " random card\n"; }
		Tools::MoveCardFromCollectionToCollection(&collection, &random_deck);
	}
	return random_deck;
}

bool Tools::FlipTheCoin()
{
	uniform_int_distribution<int> dist(0, 1);
	int rand = dist(m_RandomMachine);
	return rand;
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
	double rand = dist(m_RandomMachine);
	return rand;
}

void Tools::AddCoinToCollection(CardsCollection * to_collection)
{
	to_collection->AddCard(COIN_ID);
}

std::mt19937_64 Tools::m_RandomMachine;

Tools::Tools()
{
}


Tools::~Tools()
{
}
