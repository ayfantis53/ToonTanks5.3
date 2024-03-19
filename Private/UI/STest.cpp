// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/STest.h"
#include "SlateOptMacros.h"
#include "SlateExtras.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void STest::Construct(const FArguments& InArgs)
{

	ChildSlot
	[
		// Populate the widget
		SNew(SCanvas)
			+ SCanvas::Slot()
			.Size(FVector2D(300, 150))
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
		[
			SNew(SOverlay)
				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
			[
				SNew(SColorBlock)
					.Color(FLinearColor::Black)
			]

				+ SOverlay::Slot()
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
			[
				SAssignNew(test_display_text_, STextBlock)
					.ColorAndOpacity(FLinearColor::White)
					.Text(FText::FromString(test_text_))
			]
			
		]
	];
}

auto STest::change_text(FString new_text) -> void
{
	test_text_ = new_text;

	test_display_text_->SetText(FText::FromString(test_text_));
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
