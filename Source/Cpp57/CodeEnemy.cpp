// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeEnemy.h"
#include "AIController.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Navigation/PathFollowingComponent.h"
#include "TimerManager.h"

ACodeEnemy::ACodeEnemy()
{
  PrimaryActorTick.bCanEverTick = false;
}

void ACodeEnemy::BeginPlay()
{
  Super::BeginPlay();

  Chase();
}

void ACodeEnemy::Chase()
{
  AAIController *AIController = Cast<AAIController>(GetController());
  if (!AIController)
  {
    return;
  }

  ACharacter *PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
  if (!PlayerCharacter)
  {
    return;
  }

  FAIMoveRequest MoveRequest;
  MoveRequest.SetGoalActor(PlayerCharacter);
  MoveRequest.SetAcceptanceRadius(AcceptanceRadius);
  MoveRequest.SetUsePathfinding(true);

  FNavPathSharedPtr NavPath;
  AIController->MoveTo(MoveRequest, &NavPath);

  // Remove previous binding if exists
  if (MoveCompletedHandle.IsValid())
  {
    AIController->GetPathFollowingComponent()->OnRequestFinished.Remove(MoveCompletedHandle);
  }

  // Bind to the move completed delegate
  MoveCompletedHandle = AIController->GetPathFollowingComponent()->OnRequestFinished.AddUObject(
      this, &ACodeEnemy::OnMoveCompleted);
}

void ACodeEnemy::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult &Result)
{
  if (!Result.IsSuccess())
  {
    return;
  }

  // Play the attack animation
  if (AttackAnimation)
  {
    GetMesh()->PlayAnimation(AttackAnimation, false);
  }

  // Delay then go to idle
  FTimerHandle TimerHandle;
  GetWorldTimerManager().SetTimer(TimerHandle, this, &ACodeEnemy::Idle, AttackAnimationDelay, false);
}

void ACodeEnemy::Idle()
{
  USkeletalMeshComponent *MeshComp = GetMesh();
  if (!MeshComp)
  {
    return;
  }

  // Revert to animation blueprint mode
  MeshComp->SetAnimationMode(EAnimationMode::AnimationBlueprint);

  // Set the specific animation blueprint class
  if (AnimBlueprintClass)
  {
    MeshComp->SetAnimInstanceClass(AnimBlueprintClass);
  }

  // Delay then chase again (loop)
  FTimerHandle TimerHandle;
  GetWorldTimerManager().SetTimer(TimerHandle, this, &ACodeEnemy::Chase, IdleDelay, false);
}
