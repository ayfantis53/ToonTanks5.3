// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Test_wrapper.h"
#include "UI/STest.h"

TSharedRef<SWidget> UTest_wrapper::RebuildWidget()
{
	return SNew(STest);
}
