#include "DemoTimers3.h"
#include "TimerManager.h"
#include <coroutine>

// Return type for fire-and-forget game-thread coroutines.
// initial_suspend/final_suspend both return suspend_never, so the coroutine
// starts immediately and destroys its own frame on completion.
struct FActorTask {
  struct promise_type {
    FActorTask get_return_object() { return {}; }
    std::suspend_never initial_suspend() { return {}; }
    std::suspend_never final_suspend() noexcept { return {}; }
    void return_void() {}
    void unhandled_exception() {}
  };
};

// Awaitable that suspends the coroutine and resumes it after `Seconds`.
// Uses CreateWeakLambda so the resume is a no-op if the actor is destroyed
// before the timer fires.
struct FDelay {
  AActor *Actor;
  float Seconds;

  bool await_ready() const { return false; }

  void await_suspend(std::coroutine_handle<> Handle) const {
    FTimerHandle TimerHandle;
    Actor->GetWorldTimerManager().SetTimer(
        TimerHandle,
        FTimerDelegate::CreateWeakLambda(
            Actor, [Handle]() mutable { Handle.resume(); }),
        Seconds, false);
  }

  void await_resume() const {}
};

static FActorTask Run(ADemoTimers3 *Self) {
  int i = 10;
  UE_LOG(LogTemp, Log, TEXT("[timers] 3... i=%d"), i);
  co_await FDelay{Self, 3.0f};
  i++;
  UE_LOG(LogTemp, Log, TEXT("[timers] ...3 i=%d"), i);
}

ADemoTimers3::ADemoTimers3() { PrimaryActorTick.bCanEverTick = true; }

void ADemoTimers3::BeginPlay() {
  Super::BeginPlay();
  Run(this);
}
