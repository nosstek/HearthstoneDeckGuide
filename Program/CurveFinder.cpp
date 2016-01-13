#include "stdafx.h"
#include "CurveFinder.h"

#include "Card.h"

std::vector<SimpleCard> CurveFinder::m_SimpleCollection;

CurveFinder::CurveFinder()
{
}

CurveFinder::CurveFinder(CardsCollection player_collection)
{
	m_SimpleCollection.clear();
	m_SimpleCollection = player_collection.GetSimpleCollection();

	m_Table = SimpleTable(player_collection);
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
	int optimize_for_turn = 10;
	std::vector<SimpleCard> result_deck = m_SimpleCollection; //TODO
	Curve result_curve = Curve(result_deck);
	double result = result_curve.GetUsabilityFactor(optimize_for_turn);
	bool finish_condition_fulfiled = true;
	do
	{
		std::vector<SimpleCard> new_deck = GetRandomDeckFromCollection(m_SimpleCollection);

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

	Curve result_curve2 = Curve(result_deck); 

	return result_curve2;
}

std::vector<SimpleCard> CurveFinder::GetRandomDeckFromCollection(std::vector<SimpleCard> simple_collection)
{
	return simple_collection;
}



