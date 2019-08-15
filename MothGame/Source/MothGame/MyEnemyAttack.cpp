// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEnemyAttack.h"
#include "MyAICharacter.h"
#include "MothGameCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Engine/Engine.h"
#include "Engine/Classes/GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/World.h"
#include "ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"

// Sets default values
AMyEnemyAttack::AMyEnemyAttack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(50.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("ESmack");
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AMyEnemyAttack::Hit);// set up a notification for when this component hits something blocking

	// Players can't walk on it
	//CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	//CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	iDamage = 10.0;
}

AMyEnemyAttack::AMyEnemyAttack(int _iDam)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(50.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("ESmack");
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AMyEnemyAttack::Hit);// set up a notification for when this component hits something blocking

	// Players can't walk on it
	//CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	//CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	iDamage = _iDam;
}

void AMyEnemyAttack::Hit(class UPrimitiveComponent* OverLappedComponent, AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == GetWorld()->GetFirstPlayerController()->GetPawn())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Collision!")));
		Cast<AMothGameCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn())->TakeDamage(10);
		Destroy();
	}
	
}

void  AMyEnemyAttack::OnDestroy()
{
	Destroy();
}

