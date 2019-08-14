// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "Engine/World.h"
#include "MyAICharacter.h"
#include "AIController.h"
#include "MyAIController.generated.h"

/**
 * 
 */
UCLASS()
class MOTHGAME_API AMyAIController : public AAIController
{
	GENERATED_BODY()
public:
	AMyAIController();
	//UFUNCTION(BlueprintCallable, Category = "AI")
	void Move();
	//UFUNCTION(BlueprintCallable, Category = "AI")
	void Flee(FVector _move);
	//UFUNCTION(BlueprintCallable, Category = "AI")

	float GetDistanceToPlayer();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	float fDistance;
	AMyAICharacter* m_Baddie;

};
