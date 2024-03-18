// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TT_Player_controller.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATT_Player_controller : public APlayerController
{
	GENERATED_BODY()
	
public:
	/// @brief: Sets default values for this component's properties
	ATT_Player_controller();

	/// @brief: Takes player control away if player dies so we cannot move once tank is technically destroyed.
	/// @param:
	auto set_player_enabled_state(bool b_player_enabled) -> void;
};
