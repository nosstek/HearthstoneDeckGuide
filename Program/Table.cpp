#include "stdafx.h"
#include <iostream>
#include <fstream>

#include "Tools.h"

#include "Table.h"
#include "Card.h"
#include "Curve.h"

using namespace std;

void log(const std::string &text)
{
	ofstream log_file(
		"log_file.txt", ios_base::out | ios_base::app);
	log_file << text << endl;
}

SimpleTable::SimpleTable()
{
}

SimpleTable::~SimpleTable()
{
}

void SimpleTable::initialize()
{
	ofstream log_file("log_file.txt");
	log_file.clear();

	m_PlayerResult.clear();
	m_Turn = 0;
	random_device rd;
	m_RandomMachine = mt19937_64(rd());
}

bool SimpleTable::FlipTheCoin()
{
	uniform_int_distribution<int> dist(0,1);
	int rand = dist(m_RandomMachine);
	log(rand ? "I'm first" : "I'm second");
	return rand;
}

void SimpleTable::StartGame()
{
	m_ImFirst = FlipTheCoin();
	DrawStartingHand();
	//TODO: Change starting hand
}

void SimpleTable::DrawStartingHand()
{
	log("Draw player's starting hand");
	DrawStartingHand(m_PlayerDeck, m_PlayerHand, m_ImFirst);
}

void SimpleTable::DrawStartingHand(Deck &used_deck, CardsCollection &used_hand, bool am_i_first)
{
	int draw_first_cards = am_i_first ? 3 : 4;

	log("Cards draw:");
	for (int i = 0; i < draw_first_cards; ++i)
	{
		int card_draw = Tools::MoveCardFromCollectionToCollection(&used_deck, &used_hand);

		log(Card::s_AllCards[card_draw].toString());
	}

	//TODO: if (!am_i_first) AddCoinToHand();
}

bool SimpleTable::PlayMatch()
{
	std::cout << "Playing on the table\n";
	initialize();

	StartGame();

	for (int turn = 1; turn < 10; ++turn)
	{
		log("Turn: " + to_string(turn) + " ###############################");
		PlayTurn(turn); //TODO: End game condition
	}
	return true;
}

void SimpleTable::PlayTurn(int turn)
{
	log("Player's turn -------------------------------------");
	PlayTurn(m_PlayerDeck, m_PlayerHand, m_PlayerActionPoints, turn, m_PlayerResult);
}

void SimpleTable::PlayTurn(Deck &used_deck, CardsCollection &used_hand, int &used_action_points, int turn, map<int, double> result)
{
	{ //Start turn;
		used_action_points = turn;

		int card_draw = Tools::MoveCardFromCollectionToCollection(&used_deck, &used_hand);
		Curve cv = Curve(used_hand);
		result[turn] = cv.GetUsabilityFactor(turn);

		std::cout.precision(5);
		std::cout << "Turn " << turn << ": " << std::fixed << result[turn] << std::endl << cv.toString() << std::endl;

		log(to_string(used_action_points) + " action point(s)\nCard draw: " + (card_draw >= 0 ? Card::s_AllCards[card_draw].toString() : "No card draw") + "\nHand: " + to_string(used_hand.GetCardsCount()) + " Cards\n" + used_hand.toString(true));
	}

	{ // Choose card
		for (int card_cost = used_action_points; card_cost >= 0; --card_cost)
		{	
			for (map<int, int>::const_iterator it = used_hand.m_Collection.begin(); it != used_hand.m_Collection.end();) // && !used_hand.m_Collection.empty(); is HACK: wtf it fails to go out if it = end?
			{
				if (Card::s_AllCards[it->first].m_BaseCost == card_cost)
				{
					//TODO: Hero ability
					int card_id_to_play = it->first;
					if (used_hand.m_Collection[card_id_to_play] == 1)
						++it;
					PlayCard(used_hand, card_id_to_play); //TODO: Optimal card play - now its the most expencive;
					used_action_points -= card_cost;
					if (card_cost > used_action_points)
						card_cost = used_action_points;

					log(to_string(used_action_points) + " action point(s)\nCard played: " + Card::s_AllCards[card_id_to_play].toString() + "\nHand: " + to_string(used_hand.GetCardsCount()) + " Cards\n" + used_hand.toString(true));
				}
				else
				{
					++it;
				}
			}
		}
	}
	// No more moves available - end turn
}

void SimpleTable::PlayCard(CardsCollection &hand, int card_id_to_play)
{
	hand.RemoveCard(card_id_to_play);
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

void Table::DrawStartingHand()
{
	__super::DrawStartingHand();
	log("Draw enemy's starting hand");
	__super::DrawStartingHand(m_EnemyDeck, m_EnemyHand, !m_ImFirst);
}

void Table::PlayTurn(int turn)
{
	if (m_ImFirst)
		__super::PlayTurn(turn);

	log("Enemy's turn -------------------------------------");
	__super::PlayTurn(m_EnemyDeck, m_EnemyHand, m_EnemyActionPoints, turn, m_EnemyResult);

	if (!m_ImFirst)
		__super::PlayTurn(turn);
}

void Table::ApplyCardEffect(int card_id_to_play)
{
	__super::ApplyCardEffect(card_id_to_play);
	//TODO: Card effects
}


//TODO: Big table!

