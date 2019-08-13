// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MothGameCharacter.generated.h"

UCLASS(config=Game)
class AMothGameCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	AMothGameCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	//Walking Variables
	UPROPERTY(EditAnywhere, Category = "Movement")
	float WalkingSpeed;
	UPROPERTY(EditAnywhere, Category="Movement")
	float RunningSpeed;
	//Dashing Boolean for Animaiton and Logic
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	bool isDashing;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
		float dashDirectionY;
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
		float dashDirectionX;
	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	bool IgnoreMovement;

	void Tick(float deltaTime);
protected:
	/** Called for walk input */
	void Walk();
	bool IsWalking;

	/** Called for dash input */
	void Dash();
	void StopDashing();
	void ResetDash();
	void StopDashAnim();
	float DashCooldown;
	float DashDistance;
	float DashAnimTime;
	bool CanDash;
	float DashStop;
	FTimerHandle UnusedHandle;
	FTimerHandle AnimHandle;
	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);



protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

