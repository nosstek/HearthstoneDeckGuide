#include "stdafx.h"
#include "Curve.h"
#include "Card.h"

Curve::Curve()
{
}

void Curve::SumUpForCurve(CardsCollection collection)
{
	m_Curve.clear();

	for (std::map<int, int>::const_iterator it = collection.m_Collection.begin(); it != collection.m_Collection.end(); ++it)
	{
		int card_id = it->first;
		int cost = GetCardCost(card_id);
		m_Curve[cost] += it->second;
	}
}

void Curve::SumUpForCurve(std::vector<SimpleCard> simple_collection)
{
	m_Curve.clear();

	for (int i = 0; i < simple_collection.size(); ++i)
	{
		int cost = simple_collection[i].m_BaseCost;
		m_Curve[cost] += simple_collection[i].m_Quantity;
	}
}

double Curve::GetUsabilityFactor(int turn)
{
	double result = 0;
	for (int i = turn; i > 0; --i)
	{
		double di = i;
		double dt = turn;
		result += m_Curve[i] * (di / dt);
	}

	return result;
}

Curve::~Curve()
{
}

int Curve::GetCardCost(int card_id)
{
	return Card::s_AllCards[card_id].m_BaseCost;
}

std::string Curve::toString()
{
	std::string s;
	for (std::map<int, int>::const_iterator it = m_Curve.begin(); it != m_Curve.end(); ++it)
		s += std::to_string(it->first) + "\t" + std::to_string(it->second) + "\n";

	return s;
}
