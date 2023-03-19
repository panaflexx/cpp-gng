#pragma once
#include "AnimatorTransition.h"

class AnimatorAnimationEndTransition final : public AnimatorTransition
{
public:
    explicit AnimatorAnimationEndTransition(const std::string& origin, const std::string& destination);

    bool ShouldTransition() override;
};

