// Fill out your copyright notice in the Description page of Project Settings.


#include "BDPlayerHUD.h"
#include "Components/TextBlock.h"

void UBDPlayerHUD::ToggleInteractionWidget(bool bIsVisible, FText* ObjectName)
{
	if (bPrevInteractioWidgetVisibility == bIsVisible) { return; }

	bPrevInteractioWidgetVisibility = bIsVisible;

	if (InteractionText != nullptr)
	{
		InteractionText->SetVisibility(bIsVisible ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Collapsed);

		if (ObjectName != nullptr)
		{
			FFormatNamedArguments Arguments;
			Arguments.Add(TEXT("ItemName"), *ObjectName);

			InteractionText->SetText(FText::Format(NSLOCTEXT("InteractionText", "InteractionText", "Pick up {ItemName}"), Arguments));
		}
	}
}
