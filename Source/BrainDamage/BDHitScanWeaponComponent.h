// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BDWeaponComponent.h"
#include "BDHitScanWeaponComponent.generated.h"

/**
 * 
 */
UCLASS()
class BRAINDAMAGE_API UBDHitScanWeaponComponent : public UBDWeaponComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
		float HitScanForceFeedback = 100.0f;

public:

	virtual void Use();
	
};
