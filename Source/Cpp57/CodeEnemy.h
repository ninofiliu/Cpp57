// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AITypes.h"
#include "CodeEnemy.generated.h"

struct FPathFollowingResult;

UCLASS()
class CPP57_API ACodeEnemy : public ACharacter
{
  GENERATED_BODY()

public:
  ACodeEnemy();

protected:
  virtual void BeginPlay() override;

  /** The animation to play when reaching the player */
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
  TObjectPtr<UAnimationAsset> AttackAnimation;

  /** The animation blueprint class to revert to after attack */
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
  TSubclassOf<UAnimInstance> AnimBlueprintClass;

  /** Acceptance radius for AI MoveTo */
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
  float AcceptanceRadius = 200.0f;

  /** Delay after attack animation before going to idle */
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
  float AttackAnimationDelay = 1.3f;

  /** Delay in idle state before chasing again */
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
  float IdleDelay = 5.0f;

  /** Called to start chasing the player */
  UFUNCTION(BlueprintCallable, Category = "AI")
  void Chase();

  /** Called to enter idle state and revert to animation blueprint */
  UFUNCTION(BlueprintCallable, Category = "AI")
  void Idle();

private:
  /** Callback when AI move completes */
  void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult &Result);

  /** Handle for the move completed delegate */
  FDelegateHandle MoveCompletedHandle;
};
