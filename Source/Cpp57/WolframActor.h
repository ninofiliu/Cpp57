#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/Engine.h"
#include "WolframActor.generated.h"

UCLASS()
class CPP57_API AWolframActor : public AActor
{
    GENERATED_BODY()

public:
    AWolframActor();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

protected:
    // Rule for the cellular automaton (0-255), defaults to rule 30
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cellular Automaton", meta = (ClampMin = "0", ClampMax = "255"))
    int32 Rule = 30;

    // Array of cells
    TArray<bool> CellArray;

    // Apply Wolfram elementary cellular automaton rule
    void ApplyWolframRule();

    // Get next cell state based on three neighbors
    bool GetNextCellState(bool Left, bool Center, bool Right) const;

    // Log the current state of the cellular automaton
    void LogCellularState() const;
};