// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BDWeaponComponent.h"
#include "BDProjectileWeaponComponent.generated.h"

/**
 * 
 */
UCLASS()
class BRAINDAMAGE_API UBDProjectileWeaponComponent : public UBDWeaponComponent
{
	GENERATED_BODY()
	
public:

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class ABrainDamageProjectile> ProjectileClass;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

public:
	UBDProjectileWeaponComponent();

	virtual void Use();
};
