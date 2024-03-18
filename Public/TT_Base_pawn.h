// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Unreal includes
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TT_Base_pawn.generated.h"

class ATT_Projectile;
class UTT_Health_component;

UCLASS()
class TOONTANKS_API ATT_Base_pawn : public APawn
{
	GENERATED_BODY()

public:
	/// @brief: Sets default values for this pawn's properties
	ATT_Base_pawn();

	/// @brief: Getters and Setters for derived classes.
	FORCEINLINE UCapsuleComponent*    get_capsule_comp()           { return capsule_comp_; }
	FORCEINLINE UStaticMeshComponent* get_base_mesh()              { return base_mesh_; }
	FORCEINLINE UStaticMeshComponent* get_turret_mesh()            { return turret_mesh_; }
	FORCEINLINE USceneComponent*      get_projectile_spawn_point() { return projectile_spawn_point_; }

protected:
	/// @brief: Rotate turret to wherever child pawn needs to aim
	/// @param:
	auto rotate_turret(FVector look_at_target) -> void;

	/// @brief: Fires projectile from cannon
	auto fire() -> void;

	/// @brief: Destroys pawn if health goes to zero
	auto handle_destruction() -> void;

private:
	/// @brief: Construction helpers to set all UPROPERTIES
	auto set_up_base_pawn() -> void;

	/// @brief: Used mainly to define collisions and transform of an object.
	UPROPERTY()
	UCapsuleComponent* capsule_comp_;

	/// @brief: Basic unit used to create Tank base world geometry for levels.
	UPROPERTY()
	UStaticMeshComponent* base_mesh_;

	/// @brief: Basic unit used to create Tank turret world geometry for levels.
	UPROPERTY()
	UStaticMeshComponent* turret_mesh_;

	/// @brief: Actor Component that exists at a specific physical position in the world for bullets.
	UPROPERTY()
	USceneComponent* projectile_spawn_point_;

	/// @brief: Component that keeps track if we should be alive or not.
	UPROPERTY()
	UTT_Health_component* health_component_;

	UPROPERTY()
	class UWidgetComponent* test_;

	/// @brief: Sets animation for when tank or tower dies.
	UPROPERTY()
	UParticleSystem* death_particles_;

	/// @brief: Sets sound for for when tank or tower dies.
	UPROPERTY()
	USoundBase* death_sound_;

	/// @brief: Sets Camera shake for when tank or tower dies.
	UPROPERTY()
	TSubclassOf<UCameraShakeBase> death_camera_shake_class_;
};
