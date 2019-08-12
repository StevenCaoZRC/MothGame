// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "MothGameCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Public/TimerManager.h" //For The Timer 
//////////////////////////////////////////////////////////////////////////
// AMothGameCharacter

AMothGameCharacter::AMothGameCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Set up Update Funciton
	SetActorTickEnabled(true);
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.SetTickFunctionEnable(true);
	PrimaryActorTick.bStartWithTickEnabled = true;

	// set our turn rates for input
	BaseTurnRate = 45.0f;
	BaseLookUpRate = 45.0f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	// Init Movement Variables
	WalkingSpeed = 300.0f;
	RunningSpeed = 1000.0f;
	IsWalking = false;
	GetCharacterMovement()->MaxWalkSpeed = RunningSpeed;
	DashDistance = 10000.0f;
	DashCooldown = 1.0f;
	DashStop = 0.1f;
	DashAnimTime = 0.25f;
	CanDash = true;
	isDashing = false;

}

void AMothGameCharacter::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	
}

void AMothGameCharacter::Walk()
{
	if (!IsWalking)
	{
		IsWalking = true;
		GetCharacterMovement()->MaxWalkSpeed = RunningSpeed;
	}
	else
	{
		IsWalking = false;
		GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
	}
	
}

void AMothGameCharacter::Dash()
{
	if (CanDash)
	{
		isDashing = true;
		//Prevents Ground Friction
		GetCharacterMovement()->BrakingFrictionFactor = 0.0f;

		LaunchCharacter(FVector(GetActorForwardVector().X, //X
			GetActorForwardVector().Y,						//Y
			0).GetSafeNormal() * DashDistance,						//Z This is prevent Dashing Upwards
			true, 
			true);
		CanDash = false; //Prevent Spamming
	
		GetWorldTimerManager().SetTimer(UnusedHandle, this, &AMothGameCharacter::StopDashing, DashStop, false);
		GetWorldTimerManager().SetTimer(AnimHandle, this, &AMothGameCharacter::StopDashAnim, DashAnimTime, false);
	}
}

void AMothGameCharacter::StopDashing()
{
	GetCharacterMovement()->StopMovementImmediately();
	
	GetWorldTimerManager().SetTimer(UnusedHandle, this, &AMothGameCharacter::ResetDash, DashCooldown, false);

	GetCharacterMovement()->BrakingFrictionFactor = 2.0f;


	
}

void AMothGameCharacter::ResetDash()
{
	CanDash = true;
	//isDashing = false;
}

void AMothGameCharacter::StopDashAnim()
{
	isDashing = false;
}

//////////////////////////////////////////////////////////////////////////
// Input

void AMothGameCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &AMothGameCharacter::Dash);

	PlayerInputComponent->BindAction("Walk", IE_Pressed, this, &AMothGameCharacter::Walk);
	

	PlayerInputComponent->BindAxis("MoveForward", this, &AMothGameCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMothGameCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AMothGameCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMothGameCharacter::LookUpAtRate);

	
}


void AMothGameCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMothGameCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AMothGameCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AMothGameCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
