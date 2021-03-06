#pragma once

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <random>

#include "Tools.h"
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
	for (auto it = Card::s_AllCards.begin(); it != Card::s_AllCards.end(); ++it)
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
	for (auto it = Deck::s_AllDecks.begin(); it != Deck::s_AllDecks.end(); ++it)
		s += it->second.toString();

	return s;
}

string DisplayAllPlayerDecks(int player_id)
{
	Player p = Player::s_AllPlayers[player_id];
	string s;

	for (map<int, string>::const_iterator it = p.m_Deck.begin(); it != p.m_Deck.end(); ++it)
		s += Deck::s_AllDecks[it->first].toString();

	return s;
}

void debugtest()
{
	if (DEBUG_INFO) {
		cout << "All Cards:\nid\tbc\tname\n" << DisplayAllCards() << endl;
		cout << "All Players:\n" << DisplayAllPlayers() << endl;
		cout << "All Effects:\n" << DisplayAllEffects() << endl;
		cout << "All Minions:\n" << DisplayAllMinions() << endl;
		cout << "All Weapons:\n" << DisplayAllWeapons() << endl;
		cout << "All Decks:\n" << DisplayAllDecks() << endl;
	}

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
	Tools::initialize();

	DBConnector::s_DataBaseConnector = DBConnector();

	DBConnector::ImportAllFromDatabase();
}

int ChoosePlayer()
{
	cout << "All Players:\n" << DisplayAllPlayers() << endl;

	cout << "Choose player by id: ";
	int player_id;
	cin >> player_id;
	return player_id;
}

int ChooseDeck(int player_id)
{
	cout << "All player's decks:\n" << DisplayAllPlayerDecks(player_id) << endl;
	cout << "Choose deck by id: ";
	int deck_id;
	cin >> deck_id;
	return deck_id;
}

void MutationTest(int player_id, int deck_id)
{
	Collection player_collection = Player::s_AllPlayers[player_id].GetCollection();
	Collection cc = Deck::s_AllDecks[deck_id];;
	DeckWithSupplement dws = DeckWithSupplement(cc, player_collection);

	cout << "Start: " << endl;
	cout << "Collection: " << endl << player_collection.toString(true) << endl;
	cout << "Deck: " << endl << dws.m_Deck.Collection::toString(true) << endl;
	cout << "Suplement: " << endl << dws.m_Supplement.Collection::toString(true) << endl;

	DeckWithSupplement mutated = GeneticDeckConstructor::Mutation(dws);

	cout << "Mutated: " << endl;
	cout << "Deck: " << endl << mutated.m_Deck.Collection::toString(true) << endl;
	cout << "Suplement: " << endl << mutated.m_Supplement.Collection::toString(true) << endl;
}

void CrossoverTest(int player_id, int deck_id)
{
	Collection player_collection = Player::s_AllPlayers[player_id].GetCollection();
	Collection cc = Deck::s_AllDecks[deck_id];;
	DeckWithSupplement dws = DeckWithSupplement(cc, player_collection);

	cout << "Start: " << endl;
	cout << "Collection: " << endl << player_collection.toString(true) << endl;
	cout << "Deck: " << endl << dws.m_Deck.Collection::toString(true) << endl;
	cout << "Suplement: " << endl << dws.m_Supplement.Collection::toString(true) << endl;

	DeckWithSupplement mutated = GeneticDeckConstructor::Mutation(dws);

	cout << "Mutated: " << endl;
	cout << "Deck: " << endl << mutated.m_Deck.Collection::toString(true) << endl;
	cout << "Suplement: " << endl << mutated.m_Supplement.Collection::toString(true) << endl;

	auto result = std::pair<DeckWithSupplement, DeckWithSupplement>(GeneticDeckConstructor::Crossover(dws, mutated));

	cout << "X1: " << endl;
	cout << "Deck: " << endl << result.first.m_Deck.Collection::toString(true) << endl;
	cout << "Suplement: " << endl << result.first.m_Supplement.Collection::toString(true) << endl;

	cout << "X2: " << endl;
	cout << "Deck: " << endl << result.second.m_Deck.Collection::toString(true) << endl;
	cout << "Suplement: " << endl << result.second.m_Supplement.Collection::toString(true) << endl;
}

void GetClassCollectionFromCollectionTest(Collection collection, DeckClass dclass = none)
{
	if (dclass = none)
	{
		for (int i = _first; i <= _last; ++i)
			cout << "Collection for class: " << i << endl << Tools::GetAllCardsForClassFromCollection(collection, (DeckClass)i).toString(true) << endl;
	}
	else
	{
		cout << "Collection for class: " << dclass << endl << Tools::GetAllCardsForClassFromCollection(collection, dclass).toString(true) << endl;
	}
}

void TestSingleBattle(int player_id, int deck_id)
{
	Collection player_collection = Player::s_AllPlayers[player_id].GetCollection();
	Deck player_deck = Deck::s_AllDecks[deck_id];
	Deck enemy_deck = Deck::s_AllDecks[107];

	Collection player_deck_class_collection = Tools::GetAllCardsForClassFromCollection(player_collection, player_deck.m_Class);

	player_deck_class_collection.SortCollection();
	player_deck.SortCollection();
	enemy_deck.SortCollection();

	if (DEBUG_INFO)
	{
		cout << "Collection: " << endl << player_collection.toString(true) << endl;
		cout << "Class collection: " << endl << player_deck_class_collection.toString(true) << endl;
		cout << "Deck: " << endl << player_deck.Collection::toString(true) << endl;
		cout << "Enemy Deck: " << endl << enemy_deck.Collection::toString(true) << endl;
	}
	Curve collection_curve = Curve(player_deck_class_collection);
	if (DEBUG_INFO) cout << "Collection curve: " << endl << collection_curve.toString() << endl;

	Curve deck_curve = Curve(player_deck);
	if (DEBUG_INFO) cout << "Deck curve: " << endl << deck_curve.toString() << endl;

	GeneticDeckConstructor gdc = DeckConstructor(player_deck_class_collection, player_deck);
	bool find_curve = false;
	if (find_curve)
	{
		CurveFinder cv = CurveFinder(player_deck_class_collection, player_deck);
		Curve optimal_curve = cv.FindOptimalCurve();
		if (DEBUG_INFO) cout << "Optimal curve: " << endl << optimal_curve.toString() << endl;
		gdc.m_OptimalCurve = optimal_curve;
	}

	GeneticDeckConstructor::s_GenerationsLimit = 0;
	GeneticDeckConstructor::s_EvaluationPrecision = 1;
	GeneticDeckConstructor::s_PopulationSize = 1;

	Deck optimal_deck = gdc.FindOptimalDeck();

	//DBConnector::PostDeck(player_id, player_deck);
}

void TheMostImportantPart(int player_id, int deck_id)
{	
	Collection player_collection = Player::s_AllPlayers[player_id].GetCollection();
	Deck player_deck = Deck::s_AllDecks[deck_id];
	Deck enemy_deck = Deck::s_AllDecks[107];

	Collection player_deck_class_collection = Tools::GetAllCardsForClassFromCollection(player_collection, player_deck.m_Class);

	player_deck_class_collection.SortCollection();
	player_deck.SortCollection();
	enemy_deck.SortCollection();

	if (DEBUG_INFO)
	{
		cout << "Collection: " << endl << player_collection.toString(true) << endl;
		cout << "Class collection: " << endl << player_deck_class_collection.toString(true) << endl;
		cout << "Deck: " << endl << player_deck.Collection::toString(true) << endl;
		cout << "Enemy Deck: " << endl << enemy_deck.Collection::toString(true) << endl;
	}
	Curve collection_curve = Curve(player_deck_class_collection);
	if (DEBUG_INFO) cout << "Collection curve: " << endl << collection_curve.toString() << endl;

	Curve deck_curve = Curve(player_deck);
	if (DEBUG_INFO) cout << "Deck curve: " << endl << deck_curve.toString() << endl;

	GeneticDeckConstructor gdc = DeckConstructor(player_deck_class_collection, player_deck);
	bool find_curve = false;
	if (find_curve)
	{
		CurveFinder cv = CurveFinder(player_deck_class_collection, player_deck);
		Curve optimal_curve = cv.FindOptimalCurve();
		if (DEBUG_INFO) cout << "Optimal curve: " << endl << optimal_curve.toString() << endl;
		gdc.m_OptimalCurve = optimal_curve;
	}

	Deck optimal_deck = gdc.FindOptimalDeck();

	//DBConnector::PostDeck(player_id, player_deck);
}



int main()
{
	cout << "HearthstoneDeckGuide" << endl;

	initialize();

	debugtest();

// 	int player_id = ChoosePlayer();
// 	int deck_id = ChooseDeck(player_id);

	TestSingleBattle(1, 108);

	//TheMostImportantPart(1, 108);

	system("pause");

	return 0;
}

