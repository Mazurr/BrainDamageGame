// Fill out your copyright notice in the Description page of Project Settings.


#include "BDInventoryItem.h"

ABDInventoryItem::ABDInventoryItem()
{
	bReplicates = false;
	PrimaryActorTick.bCanEverTick = false;

	ItemCollisonMesh = CreateDefaultSubobject<UBoxComponent>(TEXT("InventoryItem"));

	if (ItemCollisonMesh != nullptr)
	{
		ItemCollisonMesh->BodyInstance.SetCollisionProfileName("IgnoreOnlyPawn");
		ItemCollisonMesh->SetMobility(EComponentMobility::Movable);
		ItemCollisonMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		ItemCollisonMesh->SetSimulatePhysics(true);
		RootComponent = ItemCollisonMesh;
	}
}

void ABDInventoryItem::Interact(AActor* InstigatorActor)
{
	if (ItemCollisonMesh != nullptr)
	{
		ItemCollisonMesh->SetSimulatePhysics(false);
	}
}

FText* ABDInventoryItem::GetItemName()
{
	return &ItemName;
}

bool ABDInventoryItem::CanInteract()
{
	return true;
}

void ABDInventoryItem::UseItem()
{
}

void ABDInventoryItem::StopUseItem()
{
	if (ItemCollisonMesh != nullptr)
	{
		ItemCollisonMesh->SetSimulatePhysics(true);
	}
}
