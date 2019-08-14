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
	fDistance = GetDistanceToPlayer();

	if (fDistance > 200.0f)
	{
		Move();
	}
	WithinVision();
	Super::Tick(DeltaTime);
	
}

void AMyAIController::Move()
{
	

	if (m_Baddie->isAlert && m_Baddie->iEnemyType != m_Baddie->RANGED && !m_Baddie->isAttacking)
	{
		MoveToActor(GetWorld()->GetFirstPlayerController()->GetPawn(), 50.0f);
	}
	else if (m_Baddie->isAlert && m_Baddie->iEnemyType == m_Baddie->RANGED && !m_Baddie->isAttacking)
	{
		MoveToActor(GetWorld()->GetFirstPlayerController()->GetPawn(), 1000.0f);
	}

	if (fDistance < 200.0f && m_Baddie->isAlert == true && !m_Baddie->isAttacking &&!m_Baddie->isHit) //&& //!m_Baddie->isPrepared)
	{
		m_Baddie->isAttacking = true;
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT(" FUCK ")));
	}
}

void AMyAIController::WithinVision()
{
	if (!m_Baddie->isAlert)
	{
		FHitResult Hit(ForceInit);
		FCollisionQueryParams CollisionParams;
		FVector Start = m_Baddie->GetActorLocation();
		FVector LineStart = (m_Baddie->GetActorForwardVector() * 200) + Start;
		FVector LineEnd = LineStart + (m_Baddie->GetActorForwardVector() * 500.0f);
		DrawDebugLine(GetWorld(), LineStart, LineEnd, FColor::Green, true, 2.0f, false, 4.0f);
		
		bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, LineStart, LineEnd, ECC_WorldDynamic, CollisionParams);

		if (Hit.GetActor() == GetWorld()->GetFirstPlayerController()->GetPawn())
		{
			m_Baddie->isAlert = true;
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT(" FUCK ")));
		}
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


