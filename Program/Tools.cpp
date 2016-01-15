#include "stdafx.h"
#include "Tools.h"
#include <iostream>
#include <fstream>
#include <string>
#include <random>

#define DEBUG_INFO false

#define COIN_ID 16

using namespace std;

void Tools::initialize()
{
	random_device rd;
	m_RandomMachine = mt19937_64(rd());
}

void Tools::log(const string & text)
{
	ofstream log_file("log_file.txt", ios_base::out | ios_base::app);
	log_file << text << endl;
}

void Tools::ClearLogFile()
{
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

Deck Tools::GetRandomDeckFromCollection(CardsCollection collection, DeckClass dclass) //TODO: deck class!
{
	int target_cards_count = 5;
	Deck random_deck;

	for (int cards_count = 0; cards_count != target_cards_count && !collection.m_Collection.empty(); ++cards_count)
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
