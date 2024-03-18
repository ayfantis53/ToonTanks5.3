// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Test_wrapper.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API UTest_wrapper : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;
};
