// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class TOONTANKS_API STest : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(STest)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	auto change_text(FString new_text) -> void;
private:
	TSharedPtr<STextBlock> test_display_text_;

	FString test_text_{ "Default" };
};
