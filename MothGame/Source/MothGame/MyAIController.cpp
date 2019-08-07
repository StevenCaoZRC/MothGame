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
	//m_Baddie = GetWorld()->SpawnActor<AMyAICharacter>(AMyAICharacter::StaticClass(), FVector(-770.002563, 370.000000, 226.001602), FRotator::ZeroRotator);
	//this->Possess(m_Baddie);
	MoveToActor(GetWorld()->GetFirstPlayerController()->GetPawn());
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


