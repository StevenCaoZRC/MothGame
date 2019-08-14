// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Classes/Animation/AnimBlueprint.h"
#include "GameFramework/Character.h"
#include "MyAICharacter.generated.h"


UCLASS()
class MOTHGAME_API AMyAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyAICharacter();

	enum ENEMYTYPE
	{
		BASE = 1,
		RANGED,
		HEAVY
	};

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	UFUNCTION(BlueprintCallable)
	void DamageEnemy(float _fDam);

	void CheckAlive();

	void CheckInterest(float _Delta);

	UPROPERTY(BlueprintReadWrite)
	FVector vecOPos;

	UPROPERTY(BlueprintReadWrite)
	float fSpeed = 0.0f;

	UPROPERTY(BlueprintReadWrite)
	bool isAlert = false;

	UPROPERTY(BlueprintReadWrite)
	bool isHit = false;

	UPROPERTY(BlueprintReadWrite)
	bool isAttacking = false;

	UPROPERTY(BlueprintReadWrite)
	bool isDead = false;

	UPROPERTY(BlueprintReadWrite)
	bool isDying =false;

	UPROPERTY(BlueprintReadWrite)
	bool isPrepared = false;

	UPROPERTY(BlueprintReadWrite)
	int iEnemyType;

	UPROPERTY(BlueprintReadWrite)
	float fDistance = 1000.0f;

	UPROPERTY(BlueprintReadWrite)
	float fHealth = 100.0f;

	float fCurrentInterest = 0.0f;

	float fLoseInterest = 5.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	class UAnimBlueprintGeneratedClass* Anim;
	class USkeletalMesh* Skeleton;

};
