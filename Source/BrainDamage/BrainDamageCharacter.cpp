// Copyright Epic Games, Inc. All Rights Reserved.

#include "BrainDamageCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "GameFramework/PlayerState.h"
#include "BDHUD.h"
#include "BDInventoryItem.h"


//////////////////////////////////////////////////////////////////////////
// ABrainDamageCharacter

ABrainDamageCharacter::ABrainDamageCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	TurnRateGamepad = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

}

void ABrainDamageCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

}

//////////////////////////////////////////////////////////////////////////// Input

void ABrainDamageCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("PrimaryAction", IE_Pressed, this, &ABrainDamageCharacter::OnLeftMouseUse);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ABrainDamageCharacter::OnInteract);

	// Bind movement events
	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &ABrainDamageCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &ABrainDamageCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "Mouse" versions handle devices that provide an absolute delta, such as a mouse.
	// "Gamepad" versions are for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn Right / Left Gamepad", this, &ABrainDamageCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("Look Up / Down Gamepad", this, &ABrainDamageCharacter::LookUpAtRate);
}

void ABrainDamageCharacter::OnLeftMouseUse()
{
	if (HoldingInenvtoryItem != nullptr)
	{
		HoldingInenvtoryItem->UseItem();
	}
}

void ABrainDamageCharacter::OnInteract()
{
	if (InteractingItem != nullptr && InteractingItem->CanInteract())
	{
		InteractingItem->Interact(this);
	}
}

void ABrainDamageCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ABrainDamageCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ABrainDamageCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void ABrainDamageCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void ABrainDamageCharacter::ToggleInteractionMessage()
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC != nullptr)
	{
		ABDHUD* HUD = Cast<ABDHUD>(PC->GetHUD());
		if (HUD != nullptr)
		{
			HUD->ToggleInteractionWidgetVisibility(InteractingItem != nullptr, InteractingItem == nullptr ? nullptr : InteractingItem->GetItemName());
		}
	}
}

void ABrainDamageCharacter::SetHoldingItem(ABDInventoryItem* NewItem)
{
	RemoveHoldingItem();
	HoldingInenvtoryItem = NewItem;
}

void ABrainDamageCharacter::RemoveHoldingItem()
{
	if (HoldingInenvtoryItem != nullptr)
	{
		HoldingInenvtoryItem->StopUseItem();
		HoldingInenvtoryItem = nullptr;
	}
}

void ABrainDamageCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult Hit;
	FVector Start = FirstPersonCameraComponent->GetComponentLocation();

	FVector ForwardVector = FirstPersonCameraComponent->GetForwardVector();
	FVector UpVector = FirstPersonCameraComponent->GetUpVector();
	FVector End = ((ForwardVector * 250.f) + Start);
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	//DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 5.f);

	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, CollisionParams))
	{
		if (Hit.GetActor()->GetClass()->ImplementsInterface(UBDInteractionInterface::StaticClass()))
		{
			InteractingItem = Cast<ABDInventoryItem>(Hit.GetActor());
		}
		else
		{
			InteractingItem = nullptr;
		}
	}
	else
	{
		InteractingItem = nullptr;
	}

	ToggleInteractionMessage();
}
