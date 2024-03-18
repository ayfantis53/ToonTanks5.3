// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/TT_Health_component.h"
#include "TT_Game_mode.h"

#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties.
UTT_Health_component::UTT_Health_component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts.
auto UTT_Health_component::BeginPlay() -> void
{
	Super::BeginPlay();

	// Initialize Full health at Start of Game.
	health_ = max_health_;

	// Bind Function to Unreal Delegate.
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UTT_Health_component::damage_taken);

	toon_tanks_game_mode_ref_ = Cast<ATT_Game_mode>(UGameplayStatics::GetGameMode(this));
	
}

auto UTT_Health_component::damage_taken(AActor* damaged_actor, float damage, const UDamageType* damage_type, class AController* instigator, AActor* damage_causer) -> void
{
	if (damage <= 0.f)
	{
		return;
	}

	health_ -= damage;

	if (health_ <= 0.f && toon_tanks_game_mode_ref_)
	{
		toon_tanks_game_mode_ref_->actor_died(damaged_actor);
	}
}


// Called every frame.
auto UTT_Health_component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) -> void
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

