// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEnemyAttack.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Engine/Engine.h"
#include "Engine/Classes/GameFramework/Actor.h"
#include "ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"

// Sets default values
AMyEnemyAttack::AMyEnemyAttack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AttackBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
}

AMyEnemyAttack::AMyEnemyAttack(int _iDam)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	iDamage = _iDam;
	AttackBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
}

void AMyEnemyAttack::Hit(class UPrimitiveComponent* OverLappedComponent, AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Collision!")));
}

void  AMyEnemyAttack::Destroy()
{
	delete this;
}

// Called when the game starts or when spawned
void AMyEnemyAttack::BeginPlay()
{
	Super::BeginPlay();
	
	AttackBox->SetBoxExtent(FVector::FVector(10.0f, 10.0f, 10.0f));
	AttackBox->OnComponentBeginOverlap.AddDynamic(this, &AMyEnemyAttack::Hit);
}

// Called every frame
void AMyEnemyAttack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

