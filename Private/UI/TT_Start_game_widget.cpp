// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/TT_Start_game_widget.h"
#include "Widgets/Layout/SConstraintCanvas.h"
#include "SlateOptMacros.h"

#include <cmath>


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
auto STT_Start_game_widget::Construct(const FArguments& InArgs) -> void
{
	// Widget Design
	ChildSlot
	[
		// Populate the widget.
		SNew(SConstraintCanvas)
			+ SConstraintCanvas::Slot()
			.AutoSize(true)
			.Anchors(FAnchors(0.5, 0.5, 0.5, 0.5))
			.Offset(FVector2d(0, -320))
		[
			// Our Text for widget.
			SAssignNew(display_text_, STextBlock)
				.Font(FSlateFontInfo(FPaths::EngineContentDir() / roboto_path_, 42))
				.ColorAndOpacity(FLinearColor::White)
				.ShadowColorAndOpacity(FLinearColor(0, 0, 0, 1))
				.ShadowOffset(FVector2D(2.f, 2.f))
				.Text(FText::FromString(start_game_text_))
		]
	];

}

auto STT_Start_game_widget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) -> void
{
	SCompoundWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);

	// Populate the game time to countdown timer.
	count_down_ = count_down_ - InDeltaTime;
	int result = static_cast<int>(ceil(count_down_));

	// Change text based on the countdown
	switch (result)
	{
	case 0:
		start_game_text_ = FString(TEXT("Go!!!"));
		if (display_text_.IsValid())
		{
			display_text_->SetText(FText::FromString(start_game_text_));
		}
		break;
	case 1:
		start_game_text_ = FString(TEXT("1"));
		if (display_text_.IsValid())
		{
			display_text_->SetText(FText::FromString(start_game_text_));
		}
		break;
	case 2:
		start_game_text_ = FString(TEXT("2"));
		if (display_text_.IsValid())
		{
			display_text_->SetText(FText::FromString(start_game_text_));
		}
		break;
	case 3:
		start_game_text_ = FString(TEXT("3"));
		if (display_text_.IsValid())
		{
			display_text_->SetText(FText::FromString(start_game_text_));
		}
		break;
	case 4:
		start_game_text_ = FString(TEXT("Get Ready!!!"));
		if (display_text_.IsValid())
		{
			display_text_->SetText(FText::FromString(start_game_text_));
		}
		break;
	default:
		start_game_text_ = FString(TEXT(" ERROR "));
		if (display_text_.IsValid())
		{
			display_text_->SetText(FText::FromString(start_game_text_));
		} 
		break;
	}
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
