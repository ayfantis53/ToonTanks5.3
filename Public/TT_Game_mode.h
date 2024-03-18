// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TT_Game_mode.generated.h"

class ATT_Tank;
class ATT_Player_controller;
/**
 * 
 */
UCLASS()
class TOONTANKS_API ATT_Game_mode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	/// @brief: Sets default values for this component's properties
	ATT_Game_mode();

	/// @brief: Dissapears Pawn when destroyed.
	/// @param:
	auto actor_died(AActor* dead_actor) -> void;

protected:
	/// @brief: Called when the game starts or when spawned.
	virtual auto BeginPlay() -> void override;

private:
	/// @brief: Displays Start game widget
	auto start_game() -> void;

	/// @brief:
	auto game_over(bool b_won_game) -> void;

	/// @brief: Deletes widget from screen.
	auto remove_widget() -> void;

	/// @brief: Displays countdown widget and disables player input until countdown finished
	auto handle_game_start() -> void;

	/// @brief: Finds out how many towers are left in the game.
	auto get_target_tower_count() -> int32;

	/// @brief: a reference to the tank pawn or player.
	ATT_Tank* tank_ref_;

	/// @brief: a reference to the player controller.
	ATT_Player_controller* toon_tanks_player_controller_ref_;

	/// @brief: reference to start game widget.
	TSharedPtr<class STT_Start_game_widget> start_game_widget_ref_;

	/// @brief: ptr to widget that holds the start game widget.
	TSharedPtr<SWidget> start_game_widget_container_;

	/// @brief: reference to end game widget.
	TSharedPtr<class STT_End_game_widget> end_game_widget_ref_;

	/// @brief: ptr to widget that holds the end game widget.
	TSharedPtr<SWidget> end_game_widget_container_;

	/// @brief: Amount of seconds it takes to countdown the game start.
	float start_delay_{ 5.0f };

	/// @brief: How many towers we have to kill left in game to win.
	int32 target_towers_{ 0 };
};
