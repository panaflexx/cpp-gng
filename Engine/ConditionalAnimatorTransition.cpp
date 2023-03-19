#include "base.h"

#include "ConditionalAnimatorTransition.h"
#include "AnimatorRenderer.h"

ConditionalAnimatorTransition::ConditionalAnimatorTransition(const std::string& origin, const std::string& destination, std::map<std::string, int> conditions)
	: AnimatorTransition(origin, destination), m_Conditions{std::move(conditions)}
{
}

ConditionalAnimatorTransition::ConditionalAnimatorTransition(const std::string& origin, const std::string& destination,
	const std::string& condition, int targetValue)
		: ConditionalAnimatorTransition(origin, destination, std::map<std::string, int>{ { condition, targetValue} })
{
}

bool ConditionalAnimatorTransition::ShouldTransition()
{
	// Check if all required conditions match
	for (std::pair<std::string, int> pair : m_Conditions)
	{
		if (m_pAnimator->GetParameter(pair.first) == pair.second)
		{
			continue;
		}

		return false;
	}

	return true;
}
