// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BDPlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class BRAINDAMAGE_API UBDPlayerHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* InteractionText;

	void ToggleInteractionWidget(bool bIsVisible, FText* ObjectName);

private:
	bool bPrevInteractioWidgetVisibility = false;
};
