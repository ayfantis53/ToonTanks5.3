// Fill out your copyright notice in the Description page of Project Settings.


#include "TT_Base_pawn.h"
#include "TT_Projectile.h"
#include "FX/TT_Camera_shake_death.h"
#include "Components/TT_Health_component.h"

#include "Particles/ParticleSystem.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
//#include "DrawDebugHelpers.h"

#include "UI/STest.h"

// Sets default values
ATT_Base_pawn::ATT_Base_pawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	capsule_comp_ = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	capsule_comp_->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	SetRootComponent(capsule_comp_);

	base_mesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	base_mesh_->SetupAttachment(capsule_comp_);

	turret_mesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	turret_mesh_->SetupAttachment(base_mesh_);

	projectile_spawn_point_ = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	projectile_spawn_point_->SetupAttachment(turret_mesh_);

	health_component_ = CreateDefaultSubobject<UTT_Health_component>(TEXT("Health Component"));

	//
	test_ = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget Test"));
	test_->SetSlateWidget(SNew(STest));
	test_->SetRelativeLocation(FVector(150.f, 100.f, 190.f));
	test_->SetWidgetSpace(EWidgetSpace::Screen);
	test_->SetupAttachment(base_mesh_);
	//

	set_up_base_pawn();
}

auto ATT_Base_pawn::set_up_base_pawn() -> void
{
	// Set Death Particles.
	static  ConstructorHelpers::FObjectFinder<UParticleSystem>death_particle_path(TEXT("/Game/Assets/Effects/P_DeathEffect.P_DeathEffect"));
	if (death_particle_path.Succeeded())
	{
		death_particles_ = death_particle_path.Object;
	}

	// Set Death Sound.
	static  ConstructorHelpers::FObjectFinder<USoundBase>death_sound_path(TEXT("/Game/Assets/Audio/Explode_Audio.Explode_Audio"));
	if (death_sound_path.Succeeded())
	{
		death_sound_ = death_sound_path.Object;
	}

	// Set Camera Shake.
}
	

// Rotates Pawn's turret in direction it will fire in.
auto ATT_Base_pawn::rotate_turret(FVector look_at_target) -> void
{
	FVector to_target = look_at_target - turret_mesh_->GetComponentLocation();
	FRotator look_at_rotation = FRotator(0.f, to_target.Rotation().Yaw, 0.f);

	turret_mesh_->SetWorldRotation(FMath::RInterpTo(turret_mesh_->GetComponentRotation(), look_at_rotation, UGameplayStatics::GetWorldDeltaSeconds(this), 13.f));
}

// Allows pawn to Fire projectile.
auto ATT_Base_pawn::fire() -> void
{
	FVector location = projectile_spawn_point_->GetComponentLocation();
	FRotator rotation = projectile_spawn_point_->GetComponentRotation();

	ATT_Projectile* projectile = GetWorld()->SpawnActor<ATT_Projectile>(location, rotation);

	// Let Projectile know who is firing it.
	projectile->SetOwner(this);

	//DrawDebugSphere(GetWorld(), location, 25.f, 12, FColor::Red, false, 3.f);
	auto game_text_ = FString(TEXT("FIRED!!!"));
	TSharedPtr<SWidget> widget = test_->GetSlateWidget();
	if (widget->GetType() == "STest")
	{
		STest* objectWidget = static_cast<STest*>(widget.Get());
		objectWidget->change_text(game_text_);
	}
}

auto ATT_Base_pawn::handle_destruction() -> void
{
	if (death_particles_)
	{
		// Death Particle Effects.
		UGameplayStatics::SpawnEmitterAtLocation(this, death_particles_, GetActorLocation(), GetActorRotation());
	}
	if (death_sound_)
	{
		// Death Sound Effects
		UGameplayStatics::PlaySoundAtLocation(this, death_sound_, GetActorLocation(), GetActorRotation());
	}
	// Camera Shake Anim.
	GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(UTT_Camera_shake_death::StaticClass());
}
