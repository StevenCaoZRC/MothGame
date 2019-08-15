// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEnemyRangedAttack.h"
#include "Engine/Classes/Kismet/KismetMathLibrary.h"
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
AMyEnemyRangedAttack::AMyEnemyRangedAttack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(50.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("ESmack");
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AMyEnemyRangedAttack::Hit);// set up a notification for when this component hits something blocking

	// Players can't walk on it
	//CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	//CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	iDamage = 10.0;

}

// Called when the game starts or when spawned
void AMyEnemyRangedAttack::BeginPlay()
{
	Super::BeginPlay();
	
	FVector ProjLoc = this->GetActorLocation();
	FVector PlayerLoc = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	FRotator ERot = UKismetMathLibrary::FindLookAtRotation(ProjLoc, PlayerLoc);
	this->SetActorRotation(ERot);
}

// Called every frame
void AMyEnemyRangedAttack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DespawnTime = DespawnTime + DeltaTime;

	if (DespawnTime >= MaxDespawnTime)
	{
		Destroy();
	}

	FVector Movement = this->GetActorForwardVector() * 10.0f;
	this->SetActorLocation(Movement + this->GetActorLocation());

}

void AMyEnemyRangedAttack::Hit(class UPrimitiveComponent* OverLappedComponent, AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	

	if (OtherActor == GetWorld()->GetFirstPlayerController()->GetPawn())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Collision!")));
		Destroy();
		Cast<AMothGameCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn())->TakeDamage(10);
	}
	
}

