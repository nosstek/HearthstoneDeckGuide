#pragma once

#include <map>

#include "CardsCollection.h"
#include "TablePlayer.h"

class SimpleTable
{
public:
	TablePlayer m_Player;
 	std::map<int, double> m_PlayerResult;

	int m_Turn;
	bool m_ImFirst;

public:
	SimpleTable();
	SimpleTable(Deck player_deck) { m_Player.m_Deck = player_deck; }
	~SimpleTable();

	virtual void initialize();

	bool FlipTheCoin();
	void StartGame();

	virtual void DrawStartingHand();
	void DrawStartingHand(TablePlayer &tplayer, bool am_i_first);

	virtual bool GameEndConditionFulfilled();
	bool PlayMatch();
	
	virtual void PlayTurn(int turn);
	void PlayTurn(TablePlayer &tplayer, int turn, std::map<int, double> result);
	
	void PlayCard(TablePlayer &tplayer, int card_id_to_play);
	virtual void ApplyCardEffect(int card_id_to_play);

	static std::string toStringResult(std::map<int, double> result);

	static double SummaryResult(std::map<int, double> result);

	//Game effects mechanics

	void DrawRandomCardFromDeckToHand(TablePlayer &tplayer);
};

class Table : public SimpleTable
{
public:
 	TablePlayer m_Enemy;
	std::map<int, double> m_EnemyResult;
public:
	Table();
	Table(Deck player_deck, Deck enemy_deck) { m_Player.m_Deck = player_deck; m_Enemy.m_Deck = enemy_deck; }
	~Table();

	void initialize() override;

	bool GameEndConditionFulfilled() override;

	void DrawStartingHand() override;
	void PlayTurn(int turn) override;

	void ApplyCardEffect(int card_id_to_play) override;
};

