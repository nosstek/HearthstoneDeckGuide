#include "stdafx.h"
#include "Effect.h"

std::map<int, Effect> Effect::s_AllEffects;

Effect::Effect()
{
}

Effect::Effect(int eid, EffectType etype, Target etarget, int epower, int eduration, Condition econdition)
{
	m_Id = eid;
	m_Type = etype;
	m_Target = etarget;
	m_Power = epower;
	m_Duration = eduration;
	m_Condition = econdition;
}

Effect::~Effect()
{
}

std::string Effect::toString() const
{
	std::string s = std::to_string(m_Id) + "\n";
	return s;
}

