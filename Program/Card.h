#pragma once

#include <string>
#include <map>

#include "Effect.h"

enum CardType
{
	spell = 1,
	minion,
	weapon
};

enum CardQuality
{
	base = 1,
	common,
	uncommon,
	rare,
	epic,
	legendary
};

class Card
{
public:
	static std::map<int,Card> s_AllCards;

	int m_Id;
	std::string m_Name;
	std::string m_Description;
	int m_BaseCost;
	int m_Overload;
	CardType m_Type;
	CardQuality m_Quality;

	enum CardClass
	{
		druid = 1,
		hunter,
		mage,
		paladin,
		priest,
		rogue,
		shaman,
		warlock,
		warrior,
		none,

		_last = none,
		_first = druid
	};

	CardClass m_Class;
	Effect* m_Effect;


public:
	Card();
	Card(int id, std::string name, std::string description, int bcost, int overload, CardType ctype, CardQuality cquality, CardClass cclass);

	std::string toString() const;

	virtual ~Card();

	int DrawsCard() const;
};

