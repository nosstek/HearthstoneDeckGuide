#include "stdafx.h"
#include <iostream>

#include "Tools.h"
#include "CurveFinder.h"
#include "Card.h"

Collection CurveFinder::m_Collection;
Deck CurveFinder::m_Deck;

CurveFinder::CurveFinder()
{
}

CurveFinder::CurveFinder(Collection player_collection)
{
	m_Collection = player_collection;

	m_Deck.m_Collection.clear();
}

CurveFinder::CurveFinder(Collection player_collection, Deck player_deck)
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
	Deck new_deck = Tools::GetRandomDeckFromCollection(m_Collection);

	SimpleTable t = SimpleTable(new_deck);
	
	t.PlayMatch();

	std::cout << t.toStringResult(t.m_PlayerResult) << std::endl << t.SummaryResult(t.m_PlayerResult) << std::endl;

	Curve result_curve = Curve(new_deck);

	return result_curve;
}


