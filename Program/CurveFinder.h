#pragma once
#include "CardsCollection.h"
#include "Curve.h"
#include "Table.h"

class CurveFinder
{
public:
	static CardsCollection m_Collection;
	static Deck m_Deck;

	SimpleTable m_Table;

	CurveFinder();
	CurveFinder(CardsCollection player_collection);
	CurveFinder(CardsCollection player_collection, Deck player_deck);
	virtual ~CurveFinder();

	Curve FindOptimalCurve();
	Curve GeneticAlghoritmForCurve();
};

