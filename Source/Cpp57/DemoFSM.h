#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DemoFSM.generated.h"

UCLASS()
class CPP57_API ADemoFSM : public AActor {
  GENERATED_BODY()

public:
  ADemoFSM();
  virtual void Tick(float DeltaTime) override;

protected:
  virtual void BeginPlay() override;

private:
  void OnStateIdle();
  void OnStateAttack();
};