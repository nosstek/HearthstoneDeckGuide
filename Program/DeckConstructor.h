#pragma once

#include "CardsCollection.h"
#include "Curve.h"
#include "Table.h"


class DeckConstructor
{
public:
	CardsCollection m_PlayerCollection;
	Deck m_PlayerDeck;
	Curve m_OptimalCurve;

	Table m_Table;

public:
	DeckConstructor();
	DeckConstructor(CardsCollection player_collection);
	
	virtual ~DeckConstructor();

	Deck FindOptimalDeck();
	Deck GeneticAlghoritmForDeck();
};

