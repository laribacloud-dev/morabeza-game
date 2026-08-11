#include "MORABEZAPlayerState.h"

AMORABEZAPlayerState::AMORABEZAPlayerState()
{
    Money = 500;
    Reputation = 0;
}

void AMORABEZAPlayerState::AddMoney(int32 Amount)
{
    if (Amount > 0)
    {
        Money += Amount;
    }
}

bool AMORABEZAPlayerState::SpendMoney(int32 Amount)
{
    if (Amount <= 0 || Money < Amount)
    {
        return false;
    }

    Money -= Amount;
    return true;
}

void AMORABEZAPlayerState::AddReputation(int32 Amount)
{
    Reputation = FMath::Max(0, Reputation + Amount);
}
