#pragma once

#include <map>
#include <random>

#include "CardsCollection.h"

class SimpleTable
{
private:
	std::vector<SimpleCard> m_SimpleDeck;
	std::vector<SimpleCard> m_SimpleHand;

	Deck m_PlayerDeck;

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
};


class Table : public SimpleTable
{
public:
	Table();
	~Table();
};

