// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BDInteractionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBDInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BRAINDAMAGE_API IBDInteractionInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	virtual void Interact(AActor* InstigatorActor) = 0;

	virtual FText* GetItemName() = 0;

	virtual bool CanInteract() = 0;
};
