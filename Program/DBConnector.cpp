/* Standard C++ includes */
#include "stdafx.h"
#include "DBConnector.h"

#include <stdlib.h>
#include <iostream>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/statement.h>

#include "Card.h"
#include "Effect.h"
#include "Minion.h"


using namespace std;
//using namespace sql;

static std::string DB_URL = "192.168.1.102:3306";
static std::string DB_USER = "root";
static std::string DB_PASSWORD = "cokolwiek";

DBConnector DBConnector::s_DataBaseConnector;

DBConnector::DBConnector()
{
	//cout << "DBConnector()" << endl;

	try {
		sql::Driver *driver;
		/* Create a connection */
		driver = get_driver_instance();
		m_Con = driver->connect("tcp://" + DB_URL, DB_USER, DB_PASSWORD);
		/* Connect to the MySQL test database */
		m_Con->setSchema("Hearthstone");
	}
	catch (sql::SQLException &e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}

	cout << endl;
}

DBConnector::~DBConnector()
{
	//cout << "~DBConnector()" << endl;
	delete m_Con;
}

sql::ResultSet* DBConnector::ProcessStatement(std::string s)
{
	try {
		sql::Driver *driver;
		/* Create a connection */
		driver = get_driver_instance();
		m_Con = driver->connect("tcp://" + DB_URL, DB_USER, DB_PASSWORD);
		/* Connect to the MySQL test database */
		m_Con->setSchema("Hearthstone");


		sql::Statement *stmt;
		stmt = m_Con->createStatement();
		sql::ResultSet *res;
		res = stmt->executeQuery(s);
		return res;
	}
	catch (sql::SQLException &e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}
	return NULL;
}

bool DBConnector::ImportAllCardsFromDatabase()
{
	string s = "SELECT * FROM Card";

	sql::ResultSet* res = DBConnector::s_DataBaseConnector.ProcessStatement(s);

	if (!res)
		return false;

	Card::s_AllCards.clear();

	while (res->next())
	{
		int card_id = res->getInt("id");
		Card card_from_database = Card(
			card_id,
			res->getString("name"),
			res->getString("description"),
			res->getInt("base_cost"),
			res->getInt("overload"),
			(CardType)res->getInt("CardType_id"),
			(CardQuality)res->getInt("CardQuality_id"),
			(Card::CardClass)res->getInt("Class_id"));

		Card::s_AllCards[card_id] = card_from_database;
	}
	delete res;

	return true;
}

bool DBConnector::ImportAllEffectsFromDatabase()
{
	string s = "SELECT * FROM Effect";

	sql::ResultSet* res = DBConnector::s_DataBaseConnector.ProcessStatement(s);

	if (!res)
		return false;

	Effect::s_AllEffects.clear();

	while (res->next())
	{
		int effect_id = res->getInt("id");
		Effect effect_from_database = Effect(
			effect_id,
			(EffectType)res->getInt("EffectType_id"),
			(Target)res->getInt("Target_id"),
			res->getInt("power"),
			res->getInt("duration"),
			(Condition)res->getInt("Condition_id"));

		Effect::s_AllEffects[effect_id] = effect_from_database;
	}
	delete res;

	return true;
}

bool DBConnector::ImportAllMinionsFromDatabase()
{
	string s = "SELECT * FROM Minion";

	sql::ResultSet* res = DBConnector::s_DataBaseConnector.ProcessStatement(s);

	if (!res)
		return false;

	Minion::s_AllMinions.clear();

	while (res->next())
	{
		int minion_id = res->getInt("id");
		Minion minion_from_database = Minion(
			minion_id,
			res->getString("name"),
			res->getInt("attack"),
			res->getInt("durability"),
			res->getBoolean("windfury"));

		Minion::s_AllMinions[minion_id] = minion_from_database;
	}
	delete res;

	return true;
}

bool DBConnector::ImportAllWeaponsFromDatabase()
{
	string s = "SELECT * FROM Weapon";

	sql::ResultSet* res = DBConnector::s_DataBaseConnector.ProcessStatement(s);

	if (!res)
		return false;

	Weapon::s_AllWeapons.clear();

	while (res->next())
	{
		int weapon_id = res->getInt("id");
		Weapon weapon_from_database = Weapon(
			weapon_id,
			res->getString("name"),
			res->getInt("attack"),
			res->getInt("durability"),
			res->getBoolean("windfury"));

		Weapon::s_AllWeapons[weapon_id] = weapon_from_database;
	}
	delete res;

	return true;
}

bool DBConnector::ImportPlayerCollection(Player& p)
{
	int player_id = p.m_Id;
	string s = "SELECT `Players_with_cards`.`Card_id`, `Players_with_cards`.`card_quantity` FROM `Players_with_cards` WHERE(`Players_with_cards`.`Player_id` = " + std::to_string(player_id) + ")";

	sql::ResultSet* res = DBConnector::s_DataBaseConnector.ProcessStatement(s);

	if (!res)
		return false;

	p.m_Collection.m_Collection.clear();
	while (res->next())
	{
		int card_id = res->getInt("Card_id");
		int card_quantity = res->getInt("card_quantity");

		p.m_Collection.AddCard(card_id, card_quantity);
	}
	delete res;

	return true;
}

bool DBConnector::ImportAllPlayersCollectionsFromDatabase()
{
	for (std::map<int, Player>::iterator it = Player::s_AllPlayers.begin(); it != Player::s_AllPlayers.end(); ++it)
		ImportPlayerCollection(it->second);

	return true;
}

bool DBConnector::ImportAllPlayersFromDatabase()
{
	string s = "SELECT * FROM Player";

	sql::ResultSet* res = DBConnector::s_DataBaseConnector.ProcessStatement(s);

	if (!res)
		return false;

	Player::s_AllPlayers.clear();
	while (res->next())
	{
		int player_id = res->getInt("id");
		Player player_from_database = Player(
			player_id,
			res->getString("name"));

		Player::s_AllPlayers[player_id] = player_from_database;
	}
	delete res;

	return true;
}

bool DBConnector::FixAllDataConnections()
{
	return true;
}

bool DBConnector::ImportAllFromDatabase()
{
	ImportAllCardsFromDatabase();
	ImportAllEffectsFromDatabase();
	ImportAllWeaponsFromDatabase();
	ImportAllMinionsFromDatabase();
	ImportAllPlayersFromDatabase();
	ImportAllPlayersCollectionsFromDatabase();

	FixAllDataConnections();

	return true;
}

bool DBConnector::PostOptimalDeck(int player_id, CardsCollection optimal_deck)
{
	return true;
}

