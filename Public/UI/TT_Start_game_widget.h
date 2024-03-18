// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "SlateBasics.h"

/**
 * 
 */
class TOONTANKS_API STT_Start_game_widget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(STT_Start_game_widget)
	{}
	SLATE_END_ARGS()

	/// @brief: Constructs this widget with InArgs
	void Construct(const FArguments& InArgs);

protected:
	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

private:
	/// @brief: Time it takes for the countdown
	float count_down_{ 4.f };

	/// @brief: Text for countdown display at start of game
	TSharedPtr<STextBlock > display_text_;

	/// @brief: Value for Start Game Text
	FString start_game_text_{ "" };

	/// @brief: needed to set the widget text to Roboto
	inline const static FString roboto_path_{ "Slate/Fonts/Roboto-Bold.ttf" };
};
