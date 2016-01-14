#include "stdafx.h"
#include <iostream>

#include "Table.h"

#include "Curve.h"

using namespace std;

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
	random_device rd;
	m_RandomMachine = mt19937_64(rd());
}

bool SimpleTable::FlipTheCoin()
{
	return false;
}

void SimpleTable::StartGame()
{
	m_ImFirst = FlipTheCoin();
	int draw_first_cards = m_ImFirst ? 4 : 3;

	for (int i = 0; i < draw_first_cards; ++i)
	{
		int rc = m_PlayerDeck.GetRandomCard();
		
		m_PlayerHand.AddCard(rc);
		m_PlayerDeck.RemoveCard(rc);
	}

	//TODO: if (!m_ImFirst) AddCoinToHand();
}

void SimpleTable::PlayMatch()
{
	std::cout << "Playing on the table\n";
	initialize();

	StartGame();

	for (int i = 1; i < 10; ++i)
	{
		int rc = m_PlayerDeck.GetRandomCard();

		m_PlayerHand.AddCard(rc);
		m_PlayerDeck.RemoveCard(rc);

		Curve cv = Curve(m_PlayerHand);
		m_Result[i] = cv.GetUsabilityFactor(i);

		//TODO: Play card

		//TODO: Card effects

		//TODO: Hero ability

		std::cout.precision(5);
		std::cout << "Turn " << i << ": " << std::fixed << m_Result[i] << std::endl << cv.toString() << std::endl;
	}
}

std::string SimpleTable::toStringResult()
{
	std::string s;
	for (map<int, double>::const_iterator it = m_Result.begin(); it != m_Result.end(); ++it)
		s += std::to_string(it->first) + "\t" + to_string(it->second) + "\n";

	return s;
}

double SimpleTable::SummaryResult()
{
	double result = 0;
	for (map<int, double>::const_iterator it = m_Result.begin(); it != m_Result.end(); ++it)
		result += it->second;
	return result;
}

Table::Table()
{
}

Table::~Table()
{
}

//TODO: Big table!

