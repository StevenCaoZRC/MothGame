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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float fSpeed = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool isAlert = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool isAttacking = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool isDead = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool isDying =false;

	UPROPERTY(EditAnywhere)
	int iEnemyType;

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
