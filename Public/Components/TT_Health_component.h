// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TT_Health_component.generated.h"

class ATT_Game_mode;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UTT_Health_component : public UActorComponent
{
	GENERATED_BODY()

public:	
	/// @brief: Sets default values for this component's properties
	UTT_Health_component();

protected:
	/// @brief: Called when the game starts
	virtual auto BeginPlay() -> void override;

	/// @brief: Called when the game starts
	/// @param:
	/// @param:
	/// @param:
	/// @param:
	UFUNCTION()
	void damage_taken(AActor* damaged_actor, float damage, const UDamageType* damage_type, class AController* instigator, AActor* damage_causer);

public:	
	/// @brief: Called every frame
	/// @param :
	/// @param:
	/// @param:
	virtual auto TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) -> void override;

private:
	/// @brief: Amount of damage taken on each hit from projectile.
	float damaged_{ 50.f }; 

	/// @brief: Current health of pawn.
	float health_{ 0.f };

	/// @brief: Maximum starting health of pawn.
	float max_health_{ 100.f };

	/// @brief: Reference to the game mode so we now to end game or not.
	ATT_Game_mode* toon_tanks_game_mode_ref_;
		
};
