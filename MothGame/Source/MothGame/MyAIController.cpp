// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"
#include "MyAICharacter.h"
#include "Engine/World.h"
#include "Engine.h"

AMyAIController::AMyAIController()
{

}

void  AMyAIController::BeginPlay()
{
	Super::BeginPlay();
	
}

void  AMyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	MoveToActor(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void AMyAIController::Move(FVector _move)
{
	
}

void  AMyAIController::Flee(FVector _move)
{

}


