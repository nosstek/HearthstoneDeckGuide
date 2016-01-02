#include "stdafx.h"
#include <iostream>

#include "Table.h"

#include "Curve.h"

SimpleTable::SimpleTable()
{
}

SimpleTable::~SimpleTable()
{
}

void SimpleTable::initialize()
{
	m_Result.clear();
	m_Turn = 0;

	m_SimpleDeck.clear();
	m_SimpleDeck = m_PlayerDeck.GetSimpleCollection();
	m_SimpleHand.clear();

	std::random_device rd;
	m_RandomMachine = std::mt19937_64(rd());
}

bool SimpleTable::FlipTheCoin()
{
	std::uniform_real_distribution<double> dist(0.0, 1.0);
	return dist(m_RandomMachine) > 0.5 ? true : false;
}

void SimpleTable::StartGame()
{
	m_ImFirst = FlipTheCoin();
	int draw_first_cards = m_ImFirst ? 3 : 4;

	for (int i = 0; i < draw_first_cards; ++i)
	{
		std::uniform_int_distribution<int> dist(0, m_SimpleDeck.size());
		int rand = dist(m_RandomMachine);
		m_SimpleHand.push_back(m_SimpleDeck[rand]);
		//m_SimpleDeck.erase(m_SimpleDeck.begin() + rand);
		
	}
	Curve cv = Curve(m_SimpleHand);
	std::cout << "Starting hand: " << std::endl << cv.toString() << std::endl;

	//if (!m_ImFirst) AddCoinToHand();

}

void SimpleTable::PlayMatch()
{
	initialize();

	StartGame();

	for (int i = 1; i < 10; ++i)
	{
		std::uniform_int_distribution<int> dist(0, m_SimpleDeck.size());
		int rand = dist(m_RandomMachine);
		m_SimpleHand.push_back(m_SimpleDeck[rand]);
		//m_SimpleDeck.erase(m_SimpleDeck.begin() + rand);
		Curve cv = Curve(m_SimpleHand);
		m_Result[i] = cv.GetUsabilityFactor(i);

		std::cout.precision(10);
		std::cout << "Turn " << i << ": " << std::fixed << cv.GetUsabilityFactor(i) << std::endl << cv.toString() << std::endl;
	}
}


Table::Table()
{
}

Table::~Table()
{
}


