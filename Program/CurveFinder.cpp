#include "stdafx.h"
#include <iostream>

#include "CurveFinder.h"
#include "Card.h"

#define DEBUG_INFO false

CardsCollection CurveFinder::m_Collection;
Deck CurveFinder::m_Deck;

CurveFinder::CurveFinder()
{
}

CurveFinder::CurveFinder(CardsCollection player_collection)
{
	m_Collection = player_collection;

	m_Deck.m_Collection.clear();
}

CurveFinder::CurveFinder(CardsCollection player_collection, Deck player_deck)
{
	m_Collection = player_collection;
	m_Deck = player_deck;
}

CurveFinder::~CurveFinder()
{
}

Curve CurveFinder::FindOptimalCurve()
{
	return GeneticAlghoritmForCurve();
}

Curve CurveFinder::GeneticAlghoritmForCurve()
{
	if (DEBUG_INFO) { std::cout << "Getting random deck\n"; }
	Deck new_deck = Deck::GetRandomDeckFromCollection(m_Collection);

	SimpleTable t = SimpleTable(new_deck);
	
	t.PlayMatch();

	std::cout << t.toStringResult() << std::endl << t.SummaryResult() << std::endl;

	Curve result_curve = Curve(new_deck);

	return result_curve;
}


