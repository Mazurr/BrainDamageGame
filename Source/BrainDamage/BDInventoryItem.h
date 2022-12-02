// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BDInteractionInterface.h"
#include "Components/BoxComponent.h"
#include "BDInventoryItem.generated.h"

UCLASS()
class BRAINDAMAGE_API ABDInventoryItem : public AActor, public IBDInteractionInterface
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	FText ItemName;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* ItemCollisonMesh;

public:	
	ABDInventoryItem();

	virtual void Interact(AActor* InstigatorActor) override;

	virtual FText* GetItemName() override;

	virtual bool CanInteract() override;

	virtual void UseItem();

	virtual void StopUseItem();
};
