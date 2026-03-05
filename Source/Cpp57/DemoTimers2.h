#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DemoTimers2.generated.h"

UCLASS()
class CPP57_API ADemoTimers2 : public AActor {
  GENERATED_BODY()

public:
  ADemoTimers2();

protected:
  virtual void BeginPlay() override;

private:
  void OnDelayEnd();
};
