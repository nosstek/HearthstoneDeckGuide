#pragma once
#include "CardsCollection.h"
#include "Curve.h"
#include "Table.h"

class CurveFinder
{
public:
	static Collection m_Collection;
	static Deck m_Deck;

	SimpleTable m_Table;

	CurveFinder();
	CurveFinder(Collection player_collection);
	CurveFinder(Collection player_collection, Deck player_deck);
	virtual ~CurveFinder();

	Curve FindOptimalCurve();
	Curve GeneticAlghoritmForCurve();
};

