#pragma once

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <random>

#include "Card.h"
#include "Effect.h"
#include "Player.h"
#include "Minion.h"
#include "Weapon.h"
#include "CardsCollection.h"
#include "Curve.h"
#include "CurveFinder.h"
#include "DeckConstructor.h"

#include "DBConnector.h"

using namespace std;


string DisplayAllCards()
{
	std::string s;
	for (std::map<int, Card>::const_iterator it = Card::s_AllCards.begin(); it != Card::s_AllCards.end(); ++it)
		s += it->second.toString();

	return s;
}

string DisplayAllPlayers()
{
	std::string s;
	for (std::map<int, Player>::const_iterator it = Player::s_AllPlayers.begin(); it != Player::s_AllPlayers.end(); ++it)
		s += it->second.toString();

	return s;
}

string DisplayAllEffects()
{
	std::string s;
	for (std::map<int, Effect>::const_iterator it = Effect::s_AllEffects.begin(); it != Effect::s_AllEffects.end(); ++it)
		s += it->second.toString();

	return s;
}

string DisplayAllMinions()
{
	std::string s;
	for (std::map<int, Minion>::const_iterator it = Minion::s_AllMinions.begin(); it != Minion::s_AllMinions.end(); ++it)
		s += it->second.toString();

	return s;
}

string DisplayAllWeapons()
{
	std::string s;
	for (std::map<int, Weapon>::const_iterator it = Weapon::s_AllWeapons.begin(); it != Weapon::s_AllWeapons.end(); ++it)
		s += it->second.toString();

	return s;
}

string DisplayAllDecks()
{
	std::string s;
	for (std::map<int, Deck>::const_iterator it = Deck::s_AllDecks.begin(); it != Deck::s_AllDecks.end(); ++it)
		s += it->second.toString();

	return s;
}


void debugtest()
{
	cout << DisplayAllCards() << endl;
	cout << DisplayAllPlayers() << endl;
	cout << DisplayAllEffects() << endl;
	cout << DisplayAllMinions() << endl;
	cout << DisplayAllWeapons() << endl;
	cout << DisplayAllDecks() << endl;

	cout << "Import:\n"
		<< Card::s_AllCards.size() << " Cards\n"
		<< Player::s_AllPlayers.size() << " Players\n"
		<< Effect::s_AllEffects.size() << " Effects\n"
		<< Minion::s_AllMinions.size() << " Minions\n"
		<< Weapon::s_AllWeapons.size() << " Weapons\n"
		<< Deck::s_AllDecks.size() << " Decks\n"
		<< endl;
}

void initialize()
{
	DBConnector::s_DataBaseConnector = DBConnector();

	DBConnector::ImportAllFromDatabase();
}

void TheMostImportantPart()
{
	int player_id = 1;
	
	CardsCollection player_collection = Player::s_AllPlayers[player_id].GetCollection();
	CardsCollection player_deck = Player::s_AllPlayers[player_id].GetDeck();

	cout << "Collection: " << endl << player_collection.toString() << endl;
	cout << "Deck: " << endl << player_deck.toString() << endl;

	Curve curv = Curve(player_collection);

	cout << "Collection curve: " << endl << curv.toString() << endl;

	//CurveFinder cv = CurveFinder(player_collection);

	//Curve optimal_curve = cv.FindOptimalCurve();

	//DeckConstructor db = DeckConstructor(player_collection, optimal_curve);

	//CardsCollection optimal_deck = db.FindOptimalDeck();

	//DBConnector::PostOptimalDeck(player_id, optimal_deck);
}

int main()
{
	initialize();

	debugtest();

	TheMostImportantPart();

	system("pause");

	return 0;
}

