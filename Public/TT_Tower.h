// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TT_Tank.h"
#include "CoreMinimal.h"
#include "TT_Base_pawn.h"
#include "TT_Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATT_Tower : public ATT_Base_pawn
{
	GENERATED_BODY()
	
public:
	/// @brief: Sets default values for this pawn's properties.
	ATT_Tower();

protected:
	/// @brief: Called when the game starts or when spawned.
	virtual auto BeginPlay() -> void override;

public:
	/// @brief: Called every frame
	/// @param: DeltaTime Time taken between the frames of the gameplay can differ.
	virtual auto Tick(float DeltaTime) -> void override;

	/// @brief:
	auto handle_destruction() -> void;

private:
	/// @brief: Reference to tank so we can find its location.
	ATT_Tank* tank_ref_;

	/// @brief: Check if path is valid and sets path of mesh in content browser.
	auto set_up_meshes() -> void;

	/// @brief:
	float fire_range_{ 700.f };

	/// @brief: Unique handle that can be used to distinguish timers that have identical delegates
	FTimerHandle fire_rate_timer_handle_;

	/// @brief:
	float fire_rate_ = 2.f;

	/// @brief:
	auto check_fire_condition() -> void;

	/// @brief:
	auto in_fire_range() -> bool;

};
