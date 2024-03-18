// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateBasics.h"

#include "TT_Game_mode.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class TOONTANKS_API STT_End_game_widget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(STT_End_game_widget)
	{}
	SLATE_END_ARGS()

	/// @brief: Constructs this widget with InArgs
	auto Construct(const FArguments& InArgs) -> void;

	/// @brief: sets text for game over from gamemode
	auto set_game_over_text(bool b_win) -> void;

private:
	/// @brief: Text for countdown display at start of game
	TSharedPtr<STextBlock > display_text_;

	/// @brief: Value for Start Game Text
	FString end_game_text_{ "GAME OVER!" };

	/// @brief: needed to set the widget text to Roboto
	inline const static FString roboto_path_{ "Slate/Fonts/Roboto-Bold.ttf" };
};
