#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DemoTimers.generated.h"

UCLASS()
class CPP57_API ADemoTimers : public AActor {
  GENERATED_BODY()

public:
  ADemoTimers();

protected:
  virtual void BeginPlay() override;

public:
  virtual void Tick(float DeltaTime) override;
};
