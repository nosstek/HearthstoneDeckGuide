#pragma once

#include <string>
#include <map>

class Minion;
class Weapon;

enum EffectType
{
	damage = 1,
	spelldamage,
	mech
};

enum Target
{
	single = 1,
	all,
	friendly,
	enemy
};

enum Condition
{
	is_friendly = 1,
	is_enemy
};

class Effect
{
	int m_Id;
	EffectType m_Type;
	Target m_Target;
	int m_Power;
	int m_Duration;
	Condition m_Condition;
	Minion* m_Minion;
	Weapon* m_Weapon;

public:
	static std::map<int, Effect> s_AllEffects;

	Effect();
	Effect(int eid, EffectType etype, Target etarget, int epower, int eduration, Condition econdition);
	~Effect();

	std::string toString() const;
};

