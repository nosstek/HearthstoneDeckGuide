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
	string s;
	for (map<int, Card>::const_iterator it = Card::s_AllCards.begin(); it != Card::s_AllCards.end(); ++it)
		s += it->second.toString();

	return s;
}

string DisplayAllPlayers()
{
	string s;
	for (map<int, Player>::const_iterator it = Player::s_AllPlayers.begin(); it != Player::s_AllPlayers.end(); ++it)
		s += it->second.toString();

	return s;
}

string DisplayAllEffects()
{
	string s;
	for (map<int, Effect>::const_iterator it = Effect::s_AllEffects.begin(); it != Effect::s_AllEffects.end(); ++it)
		s += it->second.toString();

	return s;
}

string DisplayAllMinions()
{
	string s;
	for (map<int, Minion>::const_iterator it = Minion::s_AllMinions.begin(); it != Minion::s_AllMinions.end(); ++it)
		s += it->second.toString();

	return s;
}

string DisplayAllWeapons()
{
	string s;
	for (map<int, Weapon>::const_iterator it = Weapon::s_AllWeapons.begin(); it != Weapon::s_AllWeapons.end(); ++it)
		s += it->second.toString();

	return s;
}

string DisplayAllDecks()
{
	string s;
	for (map<int, Deck>::const_iterator it = Deck::s_AllDecks.begin(); it != Deck::s_AllDecks.end(); ++it)
		s += it->second.toString();

	return s;
}

void debugtest()
{
	cout << "All Cards:\n" << DisplayAllCards() << endl;
	cout << "All Players:\n" << DisplayAllPlayers() << endl;
	cout << "All Effects:\n" << DisplayAllEffects() << endl;
	cout << "All Minions:\n" << DisplayAllMinions() << endl;
	cout << "All Weapons:\n" << DisplayAllWeapons() << endl;
	cout << "All Decks:\n" << DisplayAllDecks() << endl;

	cout << "Import summary:\n"
		<< Card::s_AllCards.size() << "\tCards\n"
		<< Player::s_AllPlayers.size() << "\tPlayers\n"
		<< Effect::s_AllEffects.size() << "\tEffects\n"
		<< Minion::s_AllMinions.size() << "\tMinions\n"
		<< Weapon::s_AllWeapons.size() << "\tWeapons\n"
		<< Deck::s_AllDecks.size() << "\tDecks\n"
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

 	Curve collection_curve = Curve(player_collection);
	cout << "Collection curve: " << endl << collection_curve.toString() << endl;

	Curve deck_curve = Curve(player_deck);
	cout << "Deck curve: " << endl << deck_curve.toString() << endl;

	DeckConstructor dc = DeckConstructor(player_collection);
	bool find_curve = true;
	if (find_curve)
	{
		CurveFinder cv = CurveFinder(player_collection, player_deck);
		Curve optimal_curve = cv.FindOptimalCurve();
		cout << "Optimal curve: " << endl << optimal_curve.toString() << endl;
		dc.m_OptimalCurve = optimal_curve;
	}

	Deck optimal_deck = dc.FindOptimalDeck();

	DBConnector::PostOptimalDeck(player_id, optimal_deck);
}

int main()
{
	cout << "HearthstoneDeckGuide" << endl;

	initialize();

	debugtest();

	TheMostImportantPart();

	system("pause");

	return 0;
}

