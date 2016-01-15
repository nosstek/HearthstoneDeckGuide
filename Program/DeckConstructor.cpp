#include "stdafx.h"
#include <iostream>
#include "Tools.h"
#include "DeckConstructor.h"

#define DEBUG_INFO false

DeckConstructor::DeckConstructor()
{
}

DeckConstructor::DeckConstructor(CardsCollection player_collection)
{
	m_PlayerCollection = player_collection;
	m_PlayerDeck = Tools::GetRandomDeckFromCollection(m_PlayerCollection);
	m_Table = Table();
}

DeckConstructor::DeckConstructor(CardsCollection player_collection, Deck player_deck)
{
	m_PlayerCollection = player_collection;
	m_PlayerDeck = player_deck;
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
	Deck new_deck = Tools::GetRandomDeckFromCollection(m_PlayerCollection);

	Table t = Table(new_deck, m_PlayerDeck);

	t.PlayMatch();

	std::cout << t.toStringResult(t.m_PlayerResult) << std::endl << t.SummaryResult(t.m_PlayerResult) << std::endl;

	return new_deck;
}