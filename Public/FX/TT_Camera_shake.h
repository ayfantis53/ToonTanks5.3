// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LegacyCameraShake.h"
#include "TT_Camera_shake.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API UTT_Camera_shake : public ULegacyCameraShake
{
	GENERATED_BODY()
	
public:
	/// @brief: Sets default values for this actor's properties
	UTT_Camera_shake();
};
