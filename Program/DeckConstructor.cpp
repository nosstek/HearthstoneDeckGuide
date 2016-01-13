#include "stdafx.h"
#include "DeckConstructor.h"


DeckConstructor::DeckConstructor()
{
}

DeckConstructor::DeckConstructor(CardsCollection user_collection, Curve optimal_curve)
{
}

DeckConstructor::DeckConstructor(CardsCollection player_collection, CardsCollection player_deck, Curve optimal_curve, CardsCollection enemy_deck)
{
	m_PlayerCollection = player_collection;
	m_PlayerDeck = player_deck;
	m_OptimalCurve = optimal_curve;
	m_EnemyDeck = enemy_deck;

	m_Table = Table();
}


DeckConstructor::~DeckConstructor()
{
}

CardsCollection DeckConstructor::FindOptimalDeck()
{
	return GeneticAlghoritmForDeck();
}

CardsCollection DeckConstructor::GeneticAlghoritmForDeck()
{
	CardsCollection result_deck = m_PlayerDeck;
	double result = 0;
	bool finish_condition_fulfiled = true;
	do
	{
		CardsCollection new_deck = GetRandomDeckFromCollection();
		double average_result = 0;
		for (int i = 0; i < 100; ++i)
		{
			m_Table.PlayMatch();
			average_result;
		}
		double new_result = average_result;
		if (new_result > result)
			result_deck = new_deck;

	} while (finish_condition_fulfiled);

	return result_deck;
}

CardsCollection DeckConstructor::GetRandomDeckFromCollection()
{
	return m_PlayerDeck;
}
