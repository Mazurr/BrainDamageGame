// Copyright Epic Games, Inc. All Rights Reserved.


#include "BDWeaponComponent.h"
#include "BrainDamageCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"

void UBDWeaponComponent::Use()
{
	if (OwnerCharacter == nullptr || OwnerCharacter->GetController() == nullptr)
	{
		return;
	}

	// Try and play the sound if specified
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, OwnerCharacter->GetActorLocation());
	}

	// Try and play a firing animation if specified
	if (FireAnimation != nullptr)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = OwnerCharacter->GetMesh1P()->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}

void UBDWeaponComponent::AttachWeapon(ABrainDamageCharacter* TargetCharacter)
{
	OwnerCharacter = TargetCharacter;
	if (OwnerCharacter != nullptr)
	{
		//Attach the weapon to the First Person Character
		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
		GetOwner()->AttachToComponent(OwnerCharacter->GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint")));
	}
}

void UBDWeaponComponent::DetachWeapon()
{
	GetOwner()->DetachRootComponentFromParent();
}
