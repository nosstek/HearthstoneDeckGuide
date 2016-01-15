#pragma once

#include "CardsCollection.h"

class TablePlayer
{
public:
	Deck m_Deck;
	CardsCollection m_Hand;
	int m_ActionPoints;
public:
	int m_Health;
	int m_Armor;

	int m_Weapon;

	DeckClass m_Class;
	int m_SpecialAbility;
	bool m_UsedAbility;
	int m_TimesUsedAbility;

	int m_NextFatigueDamage;

public:
	TablePlayer();
	TablePlayer(Deck player_deck);
	~TablePlayer() {}

	void initialize();

	std::string toString();
};

