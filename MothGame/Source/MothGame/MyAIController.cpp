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
	//fDistance = GetDistanceToPlayer();
}

void  AMyAIController::Tick(float DeltaTime)
{
	Move();
	Super::Tick(DeltaTime);
	
}

void AMyAIController::Move()
{
	fDistance = GetDistanceToPlayer();

	if (m_Baddie->isAlert && m_Baddie->iEnemyType != m_Baddie->RANGED && !m_Baddie->isAttacking)
	{
		MoveToActor(GetWorld()->GetFirstPlayerController()->GetPawn(), 50.0f);
	}
	else if (m_Baddie->isAlert && m_Baddie->iEnemyType == m_Baddie->RANGED && !m_Baddie->isAttacking)
	{
		MoveToActor(GetWorld()->GetFirstPlayerController()->GetPawn(), 1000.0f);
	}

	if (fDistance < 200.0f)
	{
		m_Baddie->isAttacking = true;
		FString Temp = FString::SanitizeFloat(fDistance);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT(" FUCK ")));
	}
}

void  AMyAIController::Flee(FVector _move)
{

}

float AMyAIController::GetDistanceToPlayer()
{
	FVector Temp = m_Baddie->GetActorLocation() - GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	m_Baddie->fDistance = Temp.Size();
	return Temp.Size();
}


