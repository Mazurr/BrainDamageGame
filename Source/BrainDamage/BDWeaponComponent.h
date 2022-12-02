// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BDWeaponComponent.generated.h"

class ABrainDamageCharacter;

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BRAINDAMAGE_API UBDWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* FireSound;
	
	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

protected:
	/** The Character holding this weapon*/
	ABrainDamageCharacter* OwnerCharacter;

public:
	void AttachWeapon(ABrainDamageCharacter* TargetCharacter);

	void DetachWeapon();

	virtual void Use();
};
