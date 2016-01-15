#include "stdafx.h"
#include <iostream>
#include <fstream>

#include "Tools.h"

#include "Table.h"
#include "Card.h"
#include "Curve.h"

using namespace std;

// Logger.
void log(const std::string &text)
{
	Tools::log(text);
}

SimpleTable::SimpleTable()
{
}

SimpleTable::~SimpleTable()
{
}

// Clears log file and result set, initializes TablePlayer.
void SimpleTable::initialize()
{
	Tools::ClearLogFile();
	m_Turn = 0;

	m_Player.initialize();
	m_PlayerResult.clear();
	
}

// Flips the coin.
bool SimpleTable::FlipTheCoin()
{
	m_ImFirst = Tools::FlipTheCoin();
	log(m_ImFirst ? "I'm first" : "I'm second");
	return m_ImFirst;
}

void SimpleTable::StartGame()
{
	FlipTheCoin();
	DrawStartingHand();
	//TODO: Change starting hand = redraw
}

void SimpleTable::DrawStartingHand()
{
	log("Draw player's starting hand");
	DrawStartingHand(m_Player, m_ImFirst);
}

void SimpleTable::DrawStartingHand(TablePlayer &tplayer, bool am_i_first)
{
	int draw_first_cards = am_i_first ? 3 : 4;

	log("Cards draw:");
	for (int i = 0; i < draw_first_cards; ++i)
	{
		int card_draw = Tools::MoveCardFromCollectionToCollection(&tplayer.m_Deck, &tplayer.m_Hand);

		log(Card::s_AllCards[card_draw].toString());
	}

	if (!am_i_first)
	{
		Tools::AddCoinToCollection(&tplayer.m_Hand);
		log("Added coin to hand");
	}
}

bool SimpleTable::GameEndConditionFulfilled()
{
	return m_Turn < 10;
}

bool SimpleTable::PlayMatch()
{
	std::cout << "Playing on the table\n";
	initialize();

	StartGame();

	for (m_Turn = 1; GameEndConditionFulfilled(); ++m_Turn)
	{
		log("Turn: " + to_string(m_Turn) + " ###############################");
		PlayTurn(m_Turn);
	}
	return true;
}

void SimpleTable::PlayTurn(int turn)
{
	log("Player's turn -------------------------------------" + m_Player.toString());
	PlayTurn(m_Player, turn, m_PlayerResult);
}

void SimpleTable::PlayTurn(TablePlayer & tplayer, int turn, std::map<int, double> result)
{
	{ //Start turn;
		tplayer.m_ActionPoints = turn;

		int card_draw = Tools::MoveCardFromCollectionToCollection(&tplayer.m_Deck, &tplayer.m_Hand);

		{ // Curve statistics
			Curve cv = Curve(tplayer.m_Hand);
			result[turn] = cv.GetUsabilityFactor(turn);

			std::cout.precision(5);
			std::cout << "Turn " << turn << ": " << std::fixed << result[turn] << std::endl << cv.toString() << std::endl;
		}

		log(to_string(tplayer.m_ActionPoints) + " action point(s)\nCard draw: " +
			(card_draw >= 0 ? Card::s_AllCards[card_draw].toString() : "No card draw") +
			"\nHand: " + to_string(tplayer.m_Hand.GetCardsCount()) + " Cards\n" + tplayer.m_Hand.toString(true));
	}

	{ // Choose card
		for (int card_cost = tplayer.m_ActionPoints; card_cost >= 0; --card_cost)
		{
			for (map<int, int>::const_iterator it = tplayer.m_Hand.m_Collection.begin(); it != tplayer.m_Hand.m_Collection.end();)
			{
				if (Card::s_AllCards[it->first].m_BaseCost == card_cost)
				{
					//TODO: Hero ability
					int card_id_to_play = it->first;
					if (tplayer.m_Hand.m_Collection[card_id_to_play] == 1)
						++it;
					PlayCard(tplayer, card_id_to_play); //TODO: Optimal card play - now its the most expencive;
					tplayer.m_ActionPoints -= card_cost;
					card_cost = tplayer.m_ActionPoints;

					log(to_string(tplayer.m_ActionPoints) + " action point(s)\nCard played: "
						+ Card::s_AllCards[card_id_to_play].toString() +
						"\nHand: " + to_string(tplayer.m_Hand.GetCardsCount()) + " Cards\n" + tplayer.m_Hand.toString(true));
				}
				else
				{
					++it;
				}
			}
			//TODO: if (tplayer.m_ActionPoints ==2) UseHeroAbility();
		}
	}
	// No more moves available - end turn
}

void SimpleTable::PlayCard(TablePlayer & tplayer, int card_id_to_play)
{
	tplayer.m_Hand.RemoveCard(card_id_to_play);
	ApplyCardEffect(card_id_to_play);
}

void SimpleTable::ApplyCardEffect(int card_id_to_play)
{
	//TODO: Card effects
}

std::string SimpleTable::toStringResult(map<int, double> result) 
{
	std::string s;
	for (map<int, double>::const_iterator it = result.begin(); it != result.end(); ++it)
		s += std::to_string(it->first) + "\t" + to_string(it->second) + "\n";

	return s;
}

double SimpleTable::SummaryResult(map<int, double> result)
{
	double summary = 0;
	for (map<int, double>::const_iterator it = result.begin(); it != result.end(); ++it)
		summary += it->second;

	return summary;
}

Table::Table()
{
}

Table::~Table()
{
}

void Table::initialize()
{
	__super::initialize();

	m_Enemy.initialize();
	m_EnemyResult.clear();
}

bool Table::GameEndConditionFulfilled()
{
	//TODO: End game condition
	return __super::GameEndConditionFulfilled();
}

void Table::DrawStartingHand()
{
	__super::DrawStartingHand();
	log("Draw enemy's starting hand");
	__super::DrawStartingHand(m_Enemy, !m_ImFirst);
}

void Table::PlayTurn(int turn)
{
	if (m_ImFirst)
		__super::PlayTurn(turn);

	log("Enemy's turn -------------------------------------" + m_Enemy.toString());
	__super::PlayTurn(m_Enemy, turn, m_EnemyResult);

	if (!m_ImFirst)
		__super::PlayTurn(turn);
}

void Table::ApplyCardEffect(int card_id_to_play)
{
	__super::ApplyCardEffect(card_id_to_play);
	//TODO: Card effects
}