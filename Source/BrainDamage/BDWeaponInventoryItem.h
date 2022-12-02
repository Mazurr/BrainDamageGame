// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BDInventoryItem.h"
#include "BDWeaponInventoryItem.generated.h"

/**
 * 
 */
UCLASS()
class BRAINDAMAGE_API ABDWeaponInventoryItem : public ABDInventoryItem
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	class UBDWeaponComponent* WeaponComponentPointer;

public:
	virtual void UseItem() override;

	virtual void StopUseItem() override;

	virtual void Interact(AActor* InstigatorActor) override;
};
