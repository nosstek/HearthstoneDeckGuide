#pragma once

#include "CardsCollection.h"
#include "Curve.h"
#include "Table.h"


class DeckConstructor
{
	CardsCollection m_PlayerCollection;
	CardsCollection m_PlayerDeck;
	CardsCollection m_EnemyDeck;
	Curve m_OptimalCurve;

	Table m_Table;

public:
	DeckConstructor();
	DeckConstructor(CardsCollection user_collection, Curve optimal_curve);
	DeckConstructor(CardsCollection player_collection, CardsCollection player_deck, Curve optimal_curve, CardsCollection enemy_deck);
	
	virtual ~DeckConstructor();

	CardsCollection FindOptimalDeck();
	CardsCollection GeneticAlghoritmForDeck();
	CardsCollection GetRandomDeckFromCollection();
};

