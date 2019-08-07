// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameManager.h"
#include "MothGameCharacter.h"
#include "MyAICharacter.h"
#include "Engine/World.h"
#include "Engine.h"
#include "MyAIController.h"

// Sets default values
AMyGameManager::AMyGameManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyGameManager::BeginPlay()
{


	Super::BeginPlay();
	GetWorld()->SpawnActor<AMyAIController>(AMyAIController::StaticClass());
	GetWorld()->SpawnActor<AMyAICharacter>(AMyAICharacter::StaticClass(), FVector(1000, 1000, 1000), FRotator::ZeroRotator);
}

// Called every frame
void AMyGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

