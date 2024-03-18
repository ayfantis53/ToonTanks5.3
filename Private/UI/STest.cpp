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
			
		]
	];

}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
