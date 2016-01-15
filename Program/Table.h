#pragma once

#include <map>
#include <random>

#include "CardsCollection.h"

class SimpleTable
{
public:
	Deck m_PlayerDeck;
	CardsCollection m_PlayerHand;
	int m_PlayerActionPoints;
	std::map<int, double> m_PlayerResult;

	int m_Turn;
	bool m_ImFirst;

	std::mt19937_64 m_RandomMachine;

public:
	SimpleTable();
	SimpleTable(Deck player_deck) { m_PlayerDeck = player_deck; }
	~SimpleTable();

	void initialize();

	bool FlipTheCoin();
	void StartGame();

	virtual void DrawStartingHand();
	void DrawStartingHand(Deck &used_deck, CardsCollection &used_hand, bool am_i_first);

	bool PlayMatch();
	virtual void PlayTurn(int turn);
	void PlayTurn(Deck &used_deck, CardsCollection &used_hand, int &used_action_points, int turn, std::map<int, double> result);
	void PlayCard(CardsCollection &hand, int card_id_to_play);
	virtual void ApplyCardEffect(int card_id_to_play);

	static std::string toStringResult(std::map<int, double> result);

	static double SummaryResult(std::map<int, double> result);
};


class Table : public SimpleTable
{
public:
	Deck m_EnemyDeck;
	CardsCollection m_EnemyHand;
	int m_EnemyActionPoints;
	std::map<int, double> m_EnemyResult;
public:
	Table();
	Table(Deck player_deck, Deck enemy_deck) { m_PlayerDeck = player_deck; m_EnemyDeck = enemy_deck; }
	~Table();

	void DrawStartingHand() override;
	void PlayTurn(int turn) override;

	void ApplyCardEffect(int card_id_to_play) override;
};

