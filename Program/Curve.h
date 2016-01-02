#pragma once

#include "CardsCollection.h"

#include <string>
#include <map>

class Curve
{
	std::map<int, int> m_Curve;
public:
	Curve();
	Curve(CardsCollection col) { SumUpForCurve(col); }
	Curve(std::vector<SimpleCard> simple_collection) { SumUpForCurve(simple_collection);  }
	void SumUpForCurve(CardsCollection col);
	void SumUpForCurve(std::vector<SimpleCard> m_SimpleDeck);

	double GetUsabilityFactor(int turn); // Number of cards that can be played on this turn (hero power is counted as a card) divided per action points used.

	virtual ~Curve();

	int GetCardCost(int card_id);

	std::string toString();
};

