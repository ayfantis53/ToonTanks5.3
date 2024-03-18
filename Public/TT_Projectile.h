// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TT_Projectile.generated.h"

class USoundBase;
class UParticleSystem;
class ULegacyCameraShake;
class UStaticMeshComponent;
class UParticleSystemComponent;
class UProjectileMovementComponent;

UCLASS()
class TOONTANKS_API ATT_Projectile : public AActor
{
	GENERATED_BODY()
	
public:	
	/// @brief: Sets default values for this actor's properties
	ATT_Projectile();

protected:
	/// @brief: Called when the game starts or when spawned
	virtual auto BeginPlay() -> void override;

public:	
	/// @brief: Called every frame
	/// @param:
	virtual auto Tick(float DeltaTime) -> void override;

private:
	/// @brief: Construction helpers to set all UPROPERTIES
	auto set_up_projectile() -> void;

	/// @brief: how to deal with objects getting hit by projectile.
	UFUNCTION()
	void on_hit(UPrimitiveComponent* hit_comp, AActor* other_actor, UPrimitiveComponent* other_comp, FVector normal_impulse, const FHitResult& hit);

	/// @brief: Basic unit used to create Projectile world geometry for levels.
	UPROPERTY()
	UStaticMeshComponent* projectile_mesh_;

	/// @brief: Necessary so we can move pawn around level.
	UPROPERTY()
	UProjectileMovementComponent* projectile_movement_component_;

	/// @brief: Sets animation for when we collide with another actor.
	UPROPERTY(VisibleAnywhere)
	UParticleSystem* hit_particles_;

	/// @brief: Sets animation for when projectile is in motion in game.
	UPROPERTY()
	UParticleSystemComponent* trail_particles_component_;

	/// @brief: Sets sound for when projectile is spawned.
	UPROPERTY()
	USoundBase* launch_sound_;

	/// @brief: Sets sound for one projectile collides with actor and is destroyed. 
	UPROPERTY()
	USoundBase* hit_sound_;

	/// @brief: Sets camera shake for when projectile hits an actor.
	UPROPERTY()
	ULegacyCameraShake* hit_camera_shake_class_;

	/// @brief: The amount of damage a pawn takes when colliding with a projectile.
	UPROPERTY()
	float damage_{ 50.f };
};
