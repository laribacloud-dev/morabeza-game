#include "MORABEZAGameMode.h"
#include "MORABEZACharacter.h"
#include "MORABEZAPlayerState.h"

AMORABEZAGameMode::AMORABEZAGameMode()
{
    DefaultPawnClass = AMORABEZACharacter::StaticClass();
    PlayerStateClass = AMORABEZAPlayerState::StaticClass();
}
