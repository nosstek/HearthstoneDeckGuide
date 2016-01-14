#pragma once

#include <map>
#include <random>

#include "CardsCollection.h"

class SimpleTable
{
public:
	Deck m_PlayerDeck;
	CardsCollection m_PlayerHand;

	int m_Turn;

	bool m_ImFirst;

	std::mt19937_64 m_RandomMachine;

	std::map<int, double> m_Result;

public:
	SimpleTable();
	SimpleTable(Deck player_deck) { m_PlayerDeck = player_deck; }
	~SimpleTable();

	void initialize();

	bool FlipTheCoin();
	void StartGame();

	void PlayMatch();

	std::string toStringResult();

	double SummaryResult();
};


class Table : public SimpleTable
{
	Table(Deck player_deck, Deck enemy_deck) { m_PlayerDeck = player_deck; m_EnemyDeck = enemy_deck; }

	Deck m_EnemyDeck;
	CardsCollection m_EnemyHand;
public:
	Table();
	~Table();
};

