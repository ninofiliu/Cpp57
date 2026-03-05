#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DemoTimers3.generated.h"

UCLASS()
class CPP57_API ADemoTimers3 : public AActor {
  GENERATED_BODY()
public:
  ADemoTimers3();

protected:
  virtual void BeginPlay() override;

public:
  virtual void Tick(float DeltaTime) override;
};
