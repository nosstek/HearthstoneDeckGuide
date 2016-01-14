#include "stdafx.h"
#include <iostream>
#include "DeckConstructor.h"

#define DEBUG_INFO false

DeckConstructor::DeckConstructor()
{
}

DeckConstructor::DeckConstructor(CardsCollection player_collection)
{
	m_PlayerCollection = player_collection;
	m_Table = Table();
}

DeckConstructor::~DeckConstructor()
{
}

Deck DeckConstructor::FindOptimalDeck()
{
	return GeneticAlghoritmForDeck();
}

Deck DeckConstructor::GeneticAlghoritmForDeck()
{
	if (DEBUG_INFO) { std::cout << "Getting random deck\n"; }
	Deck new_deck = Deck::GetRandomDeckFromCollection(m_PlayerCollection);

	SimpleTable t = SimpleTable(new_deck);

	t.PlayMatch();

	std::cout << t.toStringResult() << std::endl << t.SummaryResult() << std::endl;

	return new_deck;
}