// Fill out your copyright notice in the Description page of Project Settings.


#include "BDHitScanWeaponComponent.h"
#include "BrainDamageCharacter.h"
#include "Camera/CameraComponent.h"

void UBDHitScanWeaponComponent::Use()
{
	if (GetWorld() == nullptr
		|| OwnerCharacter == nullptr
		|| OwnerCharacter->GetFirstPersonCameraComponent() == nullptr)
	{
		return;
	}

	FHitResult* HitResult = new FHitResult();
	FVector StartTrace = OwnerCharacter->GetFirstPersonCameraComponent()->GetComponentLocation();
	FVector ForwardVector = OwnerCharacter->GetFirstPersonCameraComponent()->GetForwardVector();
	FVector EndTrace = ((ForwardVector * 20000.f) + StartTrace);
	FCollisionQueryParams* TraceParams = new FCollisionQueryParams();

	if (GetWorld()->LineTraceSingleByChannel(*HitResult, StartTrace, EndTrace, ECC_Visibility, *TraceParams))
	{
		//DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Green, false, 5.f);

		AActor* HitActor = HitResult->GetActor();
		if (HitActor != nullptr && !HitActor->IsPendingKill())
		{
			if (HitResult->GetComponent() != nullptr && HitResult->GetComponent()->IsSimulatingPhysics())
			{
				//Add inpulse to move physical obejects to see response
				HitResult->GetComponent()->AddImpulseAtLocation(ForwardVector * HitScanForceFeedback, HitResult->Location);
			}
		}
	}

	Super::Use();
}