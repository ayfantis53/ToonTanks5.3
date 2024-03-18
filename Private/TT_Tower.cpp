// Fill out your copyright notice in the Description page of Project Settings.


#include "TT_Tower.h"

#include "TimerManager.h"
#include "Engine/StaticMesh.h"

// Sets default values.
ATT_Tower::ATT_Tower()
{
    // Set Capsule Component Properties.
    get_capsule_comp()->SetCapsuleHalfHeight(74.f);
    get_capsule_comp()->SetCapsuleRadius(32.f);

    // Set Projectile Spawn Properties.
    get_projectile_spawn_point()->SetRelativeLocation(FVector(90.f, 0.f, 95.f));

    set_up_meshes();

}

auto ATT_Tower::set_up_meshes() -> void
{
    // set path for Components.
    static  ConstructorHelpers::FObjectFinder<UStaticMesh> base_mesh_path(TEXT("/Game/Assets/Meshes/SM_TowerBase.SM_TowerBase"));
    if (base_mesh_path.Succeeded())
    {
        get_base_mesh()->SetStaticMesh(base_mesh_path.Object);
        get_base_mesh()->SetRelativeLocation(FVector(0.f, 0.f, -70.f));
    }

    static  ConstructorHelpers::FObjectFinder<UStaticMesh> turret_mesh_path(TEXT("/Game/Assets/Meshes/SM_TowerTurret.SM_TowerTurret"));
    if (turret_mesh_path.Succeeded())
    {
        get_turret_mesh()->SetStaticMesh(turret_mesh_path.Object);
    }
}

// Called when the game starts or when spawned.
auto ATT_Tower::BeginPlay() -> void
{
    Super::BeginPlay();

    tank_ref_ = Cast<ATT_Tank>(UGameplayStatics::GetPlayerPawn(this, 0));

    // bound a function to our timer to be called every 2 seconds.
    GetWorldTimerManager().SetTimer(fire_rate_timer_handle_, this, &ATT_Tower::check_fire_condition, fire_rate_, true);

}

auto ATT_Tower::check_fire_condition() -> void
{
    if (tank_ref_ == nullptr)
    {
        return;
    }

    if (in_fire_range() && tank_ref_->b_alive)
    {
        fire();
    }
}

auto ATT_Tower::in_fire_range() -> bool
{
    if (tank_ref_)
    {
        float distance = FVector::Dist(GetActorLocation(), tank_ref_->GetActorLocation());

        if (distance <= fire_range_)
        {
            return true;
        }
    }

    return false;
}

auto ATT_Tower::handle_destruction() -> void
{
    Super::handle_destruction();
    Destroy();
}

// Called every frame.
auto ATT_Tower::Tick(float DeltaTime) -> void
{
    Super::Tick(DeltaTime);

    if (in_fire_range())
    {
        rotate_turret(tank_ref_->GetActorLocation());
    }

}