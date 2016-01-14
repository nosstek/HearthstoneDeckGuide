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
	void SumUpForCurve(CardsCollection col);

	double GetUsabilityFactor(int turn); // Number of cards that can be played on this turn (hero power is counted as a card) divided per action points used.

	virtual ~Curve();

	int GetCardCost(int card_id);

	std::string toString();
};

