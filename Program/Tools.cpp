#include "stdafx.h"
#include "Tools.h"
#include <iostream>

#include "CardsCollection.h"

#define DEBUG_INFO false

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
		if (DEBUG_INFO) { std::cout << "Getting #" << cards_count << " random card\n"; }
		Tools::MoveCardFromCollectionToCollection(&collection, &random_deck);
	}
	return random_deck;
}

Tools::Tools()
{
}


Tools::~Tools()
{
}
