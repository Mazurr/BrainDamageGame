// Fill out your copyright notice in the Description page of Project Settings.


#include "BDHUD.h"

void ABDHUD::BeginPlay()
{
	Super::BeginPlay();


	PlayerHUD = CreateWidget<UBDPlayerHUD>(GetWorld(), PlayerHUDClass);
	if (PlayerHUD != nullptr)
	{
		PlayerHUD->AddToViewport();
	}
}

void ABDHUD::ToggleInteractionWidgetVisibility(bool bIsVisible, FText* ObjectName)
{
	if (PlayerHUD != nullptr)
	{
		PlayerHUD->ToggleInteractionWidget(bIsVisible, ObjectName);
	}
}
