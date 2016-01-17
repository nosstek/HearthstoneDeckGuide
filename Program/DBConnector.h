#pragma once

#include "mysql_connection.h"

#include <cppconn/resultset.h>

#include "Weapon.h"
#include "Player.h"

class DBConnector
{
public:
	static DBConnector s_DataBaseConnector;

	sql::Driver* m_Driver;
	sql::Connection* m_Con;
public:
	DBConnector();
	~DBConnector();

	sql::ResultSet* ProcessStatement(std::string s);
	sql::ResultSet* ProcessPreparedStatement(std::string s, int deck_id); //TODO: This is ugly
	sql::ResultSet* ProcessPreparedStatement(std::string s, int deck_id, Deck optimal_deck);  //TODO: This is ugly
	sql::ResultSet* ProcessPreparedStatement(std::string s, std::string name, int player_id, int class_id); //TODO: This is ugly

	static bool ImportAllCardsFromDatabase();
	static bool ImportAllEffectsFromDatabase();
	static bool ImportAllMinionsFromDatabase();
	static bool ImportAllWeaponsFromDatabase();
	static bool ImportPlayerCollection(Player& p);
	static bool ImportAllPlayersCollectionsFromDatabase();
	static bool ImportAllPlayersDecksFromDatabase(); // imports connection form deck_id to player_id
	static bool ImportAllDecksFromDatabase(); // imports connection form card_id to deck_id
	static bool ImportAllPlayersFromDatabase();
	static bool ImportAllFromDatabase();
	static bool PostDeck(int player_id, Deck optimal_deck);
};

