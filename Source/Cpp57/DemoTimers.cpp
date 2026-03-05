#include "DemoTimers.h"
#include "TimerManager.h"

ADemoTimers::ADemoTimers() { PrimaryActorTick.bCanEverTick = true; }

void ADemoTimers::BeginPlay() {
  Super::BeginPlay();

  UE_LOG(LogTemp, Log, TEXT("[timers] 1..."));
  FTimerHandle DelayHandle;
  GetWorldTimerManager().SetTimer(
      DelayHandle,
      FTimerDelegate::CreateWeakLambda(
          this, [this]() { UE_LOG(LogTemp, Log, TEXT("[timers] ...1")); }),
      3.0f, false);
}
