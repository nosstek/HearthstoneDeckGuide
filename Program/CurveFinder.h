#pragma once

#include "CardsCollection.h"
#include "Curve.h"
#include "Table.h"

class CurveFinder
{
public:
	static std::vector<SimpleCard> m_SimpleCollection;

	SimpleTable m_Table;

	CurveFinder();
	CurveFinder(CardsCollection player_collection);
	virtual ~CurveFinder();
	
	Curve FindOptimalCurve();

	Curve GeneticAlghoritmForCurve();
	std::vector<SimpleCard> GetRandomDeckFromCollection(std::vector<SimpleCard> simple_collection);
};

