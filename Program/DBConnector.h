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

	static bool ImportAllCardsFromDatabase();
	static bool ImportAllEffectsFromDatabase();
	static bool ImportAllMinionsFromDatabase();
	static bool ImportAllWeaponsFromDatabase();
	static bool ImportPlayerCollection(Player& p);
	static bool ImportAllPlayersCollectionsFromDatabase();
	static bool ImportAllPlayersFromDatabase();
	static bool FixAllDataConnections();
	static bool ImportAllFromDatabase();
	static bool PostOptimalDeck(int player_id, CardsCollection optimal_deck);
};

