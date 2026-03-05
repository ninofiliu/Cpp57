#include "DemoFSM.h"

ADemoFSM::ADemoFSM() { PrimaryActorTick.bCanEverTick = true; }

void ADemoFSM::BeginPlay() {
  Super::BeginPlay();
  OnStateIdle();
}

void ADemoFSM::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

void ADemoFSM::OnStateIdle() {
  UE_LOG(LogTemp, Log, TEXT("[timers] begin idle"));
  FTimerHandle DelayHandle;
  GetWorldTimerManager().SetTimer(DelayHandle, this, &ADemoFSM::OnStateAttack,
                                  3.0f, false);
}

void ADemoFSM::OnStateAttack() {
  UE_LOG(LogTemp, Log, TEXT("[timers] begin attack"));
  FTimerHandle DelayHandle;
  GetWorldTimerManager().SetTimer(DelayHandle, this, &ADemoFSM::OnStateIdle,
                                  3.0f, false);
}