// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BDPlayerHUD.h"
#include "BDHUD.generated.h"

/**
 * 
 */
UCLASS()
class BRAINDAMAGE_API ABDHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> PlayerHUDClass;

	UPROPERTY(Transient)
	UBDPlayerHUD* PlayerHUD;

public:
	virtual void BeginPlay() override;

	void ToggleInteractionWidgetVisibility(bool bIsVisible, FText* ObjectName);
};
