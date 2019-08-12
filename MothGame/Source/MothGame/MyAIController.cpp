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
	m_Baddie = Cast<AMyAICharacter>(GetCharacter());
}

void  AMyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_Baddie->isAlert && m_Baddie->iEnemyType != m_Baddie->RANGED)
	{
		MoveToActor(GetWorld()->GetFirstPlayerController()->GetPawn(), 50.0f);
	}
	else
	{
		MoveToActor(GetWorld()->GetFirstPlayerController()->GetPawn(), 1000.0f);
	}
	
}

void AMyAIController::Move(FVector _move)
{
	
}

void  AMyAIController::Flee(FVector _move)
{

}


