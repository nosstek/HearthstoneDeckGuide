#include "stdafx.h"
#include "DBConnector.h"

#include <stdlib.h>
#include <iostream>
#include <fstream>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include "Card.h"
#include "Effect.h"
#include "Minion.h"


using namespace std;
using namespace sql;

const static string DB_INFO_FILE_NAME = "dbinfo.txt";
static ifstream DB_INFO(DB_INFO_FILE_NAME);

static string DB_URL;
static string DB_USER;
static string DB_PASSWORD;
static string DB_NAME;

DBConnector DBConnector::s_DataBaseConnector;

DBConnector::DBConnector()
{
	if (DB_INFO.is_open())
	{ 
		getline(DB_INFO, DB_URL);
		getline(DB_INFO, DB_USER);
		getline(DB_INFO, DB_PASSWORD);
		getline(DB_INFO, DB_NAME);
	}

	try {
		Driver *driver;
		driver = get_driver_instance();
		m_Con = driver->connect("tcp://" + DB_URL, DB_USER, DB_PASSWORD);
		m_Con->setSchema(DB_NAME);
	}
	catch (SQLException &e) {
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
	delete m_Con;
}

ResultSet* DBConnector::ProcessStatement(string s)
{
	try {
		Driver *driver;
		driver = get_driver_instance();
		m_Con = driver->connect("tcp://" + DB_URL, DB_USER, DB_PASSWORD);
		m_Con->setSchema(DB_NAME);

		Statement *stmt;
		stmt = m_Con->createStatement();
		ResultSet *res;
		res = stmt->executeQuery(s);
		return res;
	}
	catch (SQLException &e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}
	return NULL;
}

ResultSet* DBConnector::ProcessPreparedStatement(std::string s, int deck_id)
{
	try {
		Driver *driver;
		driver = get_driver_instance();
		m_Con = driver->connect("tcp://" + DB_URL, DB_USER, DB_PASSWORD);
		m_Con->setSchema(DB_NAME);

		PreparedStatement *pstmt;
		pstmt = m_Con->prepareStatement(s);
		pstmt->setInt(1, deck_id);
		pstmt->executeUpdate();
	}
	catch (SQLException &e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}
	return NULL;
}

ResultSet* DBConnector::ProcessPreparedStatement(std::string s, int deck_id, Deck optimal_deck)
{
	//sort(begin(optimal_deck.m_Collection), end(optimal_deck.m_Collection));

	optimal_deck.m_Collection.sort();

	try {
		Driver *driver;
		driver = get_driver_instance();
		m_Con = driver->connect("tcp://" + DB_URL, DB_USER, DB_PASSWORD);
		m_Con->setSchema(DB_NAME);

		PreparedStatement *pstmt;
		pstmt = m_Con->prepareStatement(s);

		for (auto it = begin(optimal_deck.m_Collection); it != end(optimal_deck.m_Collection); )
		{
			int card_id = *it;
			int card_quantity = optimal_deck.GetCardQuantity(card_id);
			pstmt->setInt(1, deck_id);
			pstmt->setInt(2, card_id);
			pstmt->setInt(3, card_quantity);
			pstmt->executeUpdate();
			advance(it, card_quantity);
		}
	}
	catch (SQLException &e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}
	return NULL;
}

ResultSet* DBConnector::ProcessPreparedStatement(string s, string name, int player_id, int class_id)
{
	try {
		Driver *driver;
		driver = get_driver_instance();
		m_Con = driver->connect("tcp://" + DB_URL, DB_USER, DB_PASSWORD);
		m_Con->setSchema(DB_NAME);

		PreparedStatement *pstmt;
		pstmt = m_Con->prepareStatement(s);
		pstmt->setString(1, name);
		pstmt->setInt(2, player_id);
		pstmt->setInt(3, class_id);
		pstmt->executeUpdate();
	}
	catch (SQLException &e) {
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

	ResultSet* res = DBConnector::s_DataBaseConnector.ProcessStatement(s);

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

	ResultSet* res = DBConnector::s_DataBaseConnector.ProcessStatement(s);

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

	ResultSet* res = DBConnector::s_DataBaseConnector.ProcessStatement(s);

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

	ResultSet* res = DBConnector::s_DataBaseConnector.ProcessStatement(s);

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
	string s = "SELECT `Players_with_cards`.`Card_id`, `Players_with_cards`.`card_quantity` FROM `Players_with_cards` WHERE(`Players_with_cards`.`Player_id` = " + to_string(player_id) + ")";

	ResultSet* res = DBConnector::s_DataBaseConnector.ProcessStatement(s);

	if (!res)
		return false;

	p.m_Collection.m_Collection.clear();
	while (res->next())
	{
		int card_id = res->getInt("Card_id");
		int card_quantity = res->getInt("card_quantity");

		for (int i = 0; i < card_quantity; ++i)
			p.m_Collection.AddCard(card_id);
	}
	delete res;

	return true;
}

bool DBConnector::ImportAllPlayersCollectionsFromDatabase()
{
	for (map<int, Player>::iterator it = Player::s_AllPlayers.begin(); it != Player::s_AllPlayers.end(); ++it)
		ImportPlayerCollection(it->second);

	return true;
}

bool DBConnector::ImportAllPlayersDecksFromDatabase()
{
	string s = "SELECT * FROM Deck";

	ResultSet* res = DBConnector::s_DataBaseConnector.ProcessStatement(s);

	if (!res)
		return false;



	Deck::s_AllDecks.clear();
	while (res->next())
	{
		int deck_id = res->getInt("id");
		string deck_name = res->getString("name");
		int player_id = res->getInt("Player_id");
		int class_id = res->getInt("Class_id");
		Deck d = Deck(deck_id, deck_name, DeckClass(class_id));
		Deck::s_AllDecks[deck_id] = d;
		Player::s_AllPlayers[player_id].m_Deck[deck_id] = deck_name;
	}
	delete res;

	return true;
}

bool DBConnector::ImportAllDecksFromDatabase()
{
	string s = "SELECT * FROM Decks_with_cards";

	ResultSet* res = DBConnector::s_DataBaseConnector.ProcessStatement(s);

	if (!res)
		return false;

	while (res->next())
	{
		int deck_id = res->getInt("Deck_id");
		int card_id = res->getInt("Card_id");
		int card_quantity = res->getInt("card_quantity");

		for (int i = 0; i < card_quantity; ++i)
			Deck::s_AllDecks[deck_id].AddCard(card_id);
	}
	delete res;

	return true;
}

bool DBConnector::ImportAllPlayersFromDatabase()
{
	string s = "SELECT * FROM Player";

	ResultSet* res = DBConnector::s_DataBaseConnector.ProcessStatement(s);

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

bool DBConnector::ImportAllFromDatabase()
{
	ImportAllCardsFromDatabase();
	ImportAllEffectsFromDatabase();
	ImportAllWeaponsFromDatabase();
	ImportAllMinionsFromDatabase();
	ImportAllPlayersFromDatabase();
	ImportAllPlayersCollectionsFromDatabase();
	ImportAllPlayersDecksFromDatabase();
	ImportAllDecksFromDatabase();

	

	return true;
}

bool DBConnector::PostDeck(int player_id, Deck optimal_deck) //TODO: This is ugly...
{

	string s = "SELECT * FROM  `Deck` WHERE (`Deck`.`Player_id` = " + to_string(player_id) + " AND `Deck`.`name` = 'GuideDeck')";

	ResultSet* res = DBConnector::s_DataBaseConnector.ProcessStatement(s);

	int deck_id = -1;
	if (res)
	{
		while (res->next())
			deck_id = res->getInt("id");
	}

	cout << "DECKID: " << deck_id;

	if (deck_id > 0)
	{
		s = "DELETE FROM `Hearthstone`.`Deck` WHERE `Deck`.`id` = ?";
		DBConnector::s_DataBaseConnector.ProcessPreparedStatement(s, deck_id);
	}

	{
		s = "INSERT INTO Deck (name, Player_id, Class_id) VALUES (?, ?, ?)";
		DBConnector::s_DataBaseConnector.ProcessPreparedStatement(s, "GuideDeck", player_id, 1);

		s = "SELECT * FROM  `Deck` WHERE (`Deck`.`Player_id` = " + to_string(player_id) + " AND `Deck`.`name` = 'GuideDeck')";

		res = DBConnector::s_DataBaseConnector.ProcessStatement(s);

		deck_id = -1;
		if (res)
		{
			while (res->next())
				deck_id = res->getInt("id");
		}

		cout << "DECKID: " << deck_id;

		s = "INSERT INTO Decks_with_cards (Deck_id, Card_id, card_quantity) VALUES (?, ?, ?)";
		DBConnector::s_DataBaseConnector.ProcessPreparedStatement(s, deck_id, optimal_deck);
	}

	delete res;

	return true;
}

