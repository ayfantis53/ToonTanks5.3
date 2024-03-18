// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Unreal includes
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/FloatingPawnMovement.h"

#include "CoreMinimal.h"
#include "TT_Base_pawn.h"
#include "TT_Tank.generated.h"

/**
 * 
 */
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class TOONTANKS_API ATT_Tank : public ATT_Base_pawn
{
	GENERATED_BODY()

public:
	/// @brief: Sets default values for this pawn's properties.
	ATT_Tank();

	/// @brief: Called to bind functionality to input.
	/// @param: Allows a Pawn to set up custom input bindings.
	virtual auto SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) -> void override;

	/// @brief: Called every frame
	/// @param: DeltaTime Time taken between the frames of the gameplay can differ.
	virtual auto Tick(float DeltaTime) -> void override;

	/// @brief:
	void handle_destruction();

	/// @brief: Tells us if tank is alive for GameMode.
	bool b_alive{ true };

protected:
	/// @brief: Called when the game starts or when spawned.
	virtual auto BeginPlay() -> void override;

private:
	/// @brief: Populates meshes with correct filepaths.
	auto set_up_meshes() -> void;

	/// @brief: Populates inputs filepaths.
	auto set_up_input() -> void;

	/// @brief: Moves tank forward and backward.
	/// @param:
	auto move_forward(const FInputActionValue& value) -> void;

	/// @brief: Side to Side Tank Motion.
	/// @param:
	auto turn(const FInputActionValue& value) -> void;

	/// @brief: Maintains fixed distance from parent, retracts the children in collision, and spring back when not.
	UPROPERTY()
	USpringArmComponent* spring_arm_;

	/// @brief: Represents a camera viewpoint and settings.
	UPROPERTY()
	UCameraComponent* camera_;

	///@ brief: Updates position in tick, provides simple movement for any Pawn class. 
	UPROPERTY()
	UFloatingPawnMovement* floating_pawn_movement_;

	/// @brief: Mapping Context for input, passed to player subsystem.
	UPROPERTY()
	UInputMappingContext* tank_mapping_context_;

	/// @brief: Mapping Context for forward move input, passed to player subsystem.
	UPROPERTY()
	UInputAction* move_action_;

	/// @brief: Mapping Context for turning movement input, passed to player subsystem.
	UPROPERTY()
	UInputAction* turn_action_;

	/// @brief: Mapping Context for shooting input, passed to player subsystem.
	UPROPERTY()
	UInputAction* fire_action_;

	/// @brief: Speed of tank for player.
	float speed_{ 300.f };

	/// @brief: TurnRate of tank for player.
	float turn_rate_{ 120.f };

	/// @brief: Reference to player controller.
	APlayerController* player_controller_ref_;

};
