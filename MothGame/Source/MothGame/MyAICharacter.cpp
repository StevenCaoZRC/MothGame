// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAICharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Engine/Classes/Animation/AnimBlueprint.h"
#include "Engine/Classes/GameFramework/Character.h"
#include "ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMyAICharacter::AMyAICharacter()
{

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
	GetCharacterMovement()->MaxWalkSpeed = 700.0f;
	GetCharacterMovement()->MaxAcceleration = 250.0f;
}

// Called when the game starts or when spawned
void AMyAICharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyAICharacter::Tick(float DeltaTime)
{
	fSpeed = GetVelocity().Size();
	CheckInterest(DeltaTime);
	
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input

void AMyAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyAICharacter::DamageEnemy(float _fDam)
{
	fHealth = fHealth - _fDam;
}

void AMyAICharacter::CheckAlive()
{
	if (fHealth <= 0.0f)
	{
		isDying = true;
	}
}

void AMyAICharacter::CheckInterest(float _Delta)
{
	if ((isAttacking == false) && (isAlert == true))
	{
		fCurrentInterest = fCurrentInterest + _Delta;

		if (fCurrentInterest >= fLoseInterest)
		{
			isAlert = false;
			fCurrentInterest = 0.0f;
			GetCharacterMovement()->MaxWalkSpeed = 100.0f;
		}
	}
}

