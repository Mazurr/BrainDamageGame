// Fill out your copyright notice in the Description page of Project Settings.


#include "BDWeaponInventoryItem.h"
#include "BDWeaponComponent.h"
#include "BDWeaponComponent.h"
#include "BrainDamageCharacter.h"

void ABDWeaponInventoryItem::UseItem()
{
	if (WeaponComponentPointer != nullptr)
	{
		WeaponComponentPointer->Use();
	}
}

void ABDWeaponInventoryItem::StopUseItem()
{
	Super::StopUseItem();

	if (WeaponComponentPointer != nullptr)
	{
		WeaponComponentPointer->DetachWeapon();
	}
}

void ABDWeaponInventoryItem::Interact(AActor* InstigatorActor)
{
	Super::Interact(InstigatorActor);

	ABrainDamageCharacter* InstigatorCharacter = Cast<ABrainDamageCharacter>(InstigatorActor);
	if (InstigatorCharacter != nullptr && WeaponComponentPointer != nullptr)
	{
		InstigatorCharacter->SetHoldingItem(this);
		WeaponComponentPointer->AttachWeapon(InstigatorCharacter);
	}
}