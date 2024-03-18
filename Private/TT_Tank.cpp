// Fill out your copyright notice in the Description page of Project Settings.


#include "TT_Tank.h"

#include "Engine/StaticMesh.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ATT_Tank::ATT_Tank()
{
    set_up_meshes();
    set_up_input();
    
    // Set Capsule Component Properties
    get_capsule_comp()->SetCapsuleHalfHeight(79.f);
    get_capsule_comp()->SetCapsuleRadius(74.27f);

    // Set Projectile Spawn Properties
    get_projectile_spawn_point()->SetRelativeLocation(FVector(150.f, 10.f, 90.f));

    // get camera setup correctly
    spring_arm_ = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    spring_arm_->TargetArmLength = 600.f;
    spring_arm_->SetRelativeRotation(FRotator(-33.f, 0.f, 0.f));
    spring_arm_->bEnableCameraLag = true;
    spring_arm_->CameraLagSpeed = 4.f;
    spring_arm_->bEnableCameraRotationLag = true;
    spring_arm_->CameraRotationLagSpeed = 4.f;
    spring_arm_->SetupAttachment(RootComponent);

    camera_ = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    camera_->SetupAttachment(spring_arm_);

    // need to make tank actually move
    floating_pawn_movement_ = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Floating Pawn Movement"));

}

// Called when the game starts or when spawned
auto ATT_Tank::BeginPlay() -> void
{
    Super::BeginPlay();

    player_controller_ref_ = Cast<APlayerController>(GetController());

    // Add input mapping context
    if (player_controller_ref_)
    {
        // store the enhanced input subsystem for getting which key is triggered.
        if (const auto enhanced_input_subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(player_controller_ref_->GetLocalPlayer()))
        {
            enhanced_input_subsystem->AddMappingContext(tank_mapping_context_, 0);
        }
    }

}

auto ATT_Tank::set_up_meshes() -> void
{
    // Set base mesh.
    static  ConstructorHelpers::FObjectFinder<UStaticMesh> base_mesh_path(TEXT("StaticMesh'/Game/Assets/Meshes/SM_TankBase.SM_TankBase'"));
    if (base_mesh_path.Succeeded())
    {
        get_base_mesh()->SetStaticMesh(base_mesh_path.Object);
        get_base_mesh()->SetRelativeLocation(FVector(0.f, 0.f, -77.f));
    }

    // Set turret mesh.
    static  ConstructorHelpers::FObjectFinder<UStaticMesh> turret_mesh_path(TEXT("StaticMesh'/Game/Assets/Meshes/SM_TankTurret.SM_TankTurret'"));
    if (turret_mesh_path.Succeeded())
    {
        get_turret_mesh()->SetStaticMesh(turret_mesh_path.Object);
    }

}

auto ATT_Tank::set_up_input() -> void
{
    // Set tank mapping context.
    static  ConstructorHelpers::FObjectFinder<UInputMappingContext> tank_mapping_context_path(TEXT("/Game/Inputs/IMC_TankContext.IMC_TankContext"));
    if (tank_mapping_context_path.Succeeded())
    {
        tank_mapping_context_ = tank_mapping_context_path.Object;
    }

    // Set move input action.
    static  ConstructorHelpers::FObjectFinder<UInputAction> move_action_path(TEXT("/Game/Inputs/Actions/IA_Move.IA_Move"));
    if (move_action_path.Succeeded())
    {
        move_action_ = move_action_path.Object;
    }

    // Set turn input action.
    static  ConstructorHelpers::FObjectFinder<UInputAction> turn_action_path(TEXT("/Game/Inputs/Actions/IA_Turn.IA_Turn"));
    if (turn_action_path.Succeeded())
    {
        turn_action_ = turn_action_path.Object;
    }

    // Set fire input action.
    static  ConstructorHelpers::FObjectFinder<UInputAction> fire_action_path(TEXT("/Game/Inputs/Actions/IA_Fire.IA_Fire"));
    if (fire_action_path.Succeeded())
    {
        fire_action_ = fire_action_path.Object;
    }

}

// Called to bind functionality to input.
auto ATT_Tank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) -> void
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // set up action bindings.
    if (UEnhancedInputComponent* enhanced_input_component = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        // moving forward and backward.
        enhanced_input_component->BindAction(move_action_, ETriggerEvent::Triggered, this, &ATT_Tank::move_forward);

        // turning side to side.
        enhanced_input_component->BindAction(turn_action_, ETriggerEvent::Triggered, this, &ATT_Tank::turn);

        // turning side to side.
        enhanced_input_component->BindAction(fire_action_, ETriggerEvent::Triggered, this, &ATT_Tank::fire);
    }

}

void ATT_Tank::handle_destruction()
{
    Super::handle_destruction();

    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);

    b_alive = false;
}

auto ATT_Tank::move_forward(const FInputActionValue& value) -> void
{
    // input is a float
    float direction_input = value.Get<float>();

    if (Controller && (direction_input != 0.f))
    {
        FVector forward_move = GetActorForwardVector();
        AddMovementInput(forward_move, direction_input * speed_ * UGameplayStatics::GetWorldDeltaSeconds(this));
    }

}

auto ATT_Tank::turn(const FInputActionValue& value) -> void
{
    // input is a float.
    float turn_input = value.Get<float>();

    FRotator DeltaRotation = FRotator::ZeroRotator;
    DeltaRotation.Yaw = turn_input * turn_rate_ * UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalRotation(DeltaRotation, true);
}

// Called every frame.
auto ATT_Tank::Tick(float DeltaTime) -> void
{
    Super::Tick(DeltaTime);

    if (player_controller_ref_)
    {
        // turret turning.
        FHitResult hit_result;
        player_controller_ref_->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, hit_result);
        rotate_turret(hit_result.ImpactPoint);

    }

}

