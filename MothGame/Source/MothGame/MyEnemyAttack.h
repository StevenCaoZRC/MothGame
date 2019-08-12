// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "MyEnemyAttack.generated.h"

UCLASS()
class MOTHGAME_API AMyEnemyAttack : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyEnemyAttack();
	AMyEnemyAttack(int _iDam);

	UFUNCTION()
	void Hit(class UPrimitiveComponent* OverLappedComponent, AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void Destroy();

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UBoxComponent* AttackBox;
	int iDamage;
};
