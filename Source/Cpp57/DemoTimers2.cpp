#include "DemoTimers2.h"
#include "TimerManager.h"

ADemoTimers2::ADemoTimers2() { PrimaryActorTick.bCanEverTick = true; }

void ADemoTimers2::BeginPlay() {
  Super::BeginPlay();

  UE_LOG(LogTemp, Log, TEXT("[timers] 2..."));
  FTimerHandle DelayHandle;
  GetWorldTimerManager().SetTimer(DelayHandle, this, &ADemoTimers2::OnDelayEnd,
                                  3.0f, false);
}

void ADemoTimers2::OnDelayEnd() { UE_LOG(LogTemp, Log, TEXT("[timers] ...2")); }