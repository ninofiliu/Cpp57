#include "WolframActor.h"

AWolframActor::AWolframActor()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AWolframActor::BeginPlay()
{
    Super::BeginPlay();

    // Initialize array of length 128, all false except index 64
    CellArray.SetNum(128);
    for (int32 i = 0; i < CellArray.Num(); i++)
    {
        CellArray[i] = (i == 64); // Only index 16 is true, rest are false
    }

    // Log initial state
    LogCellularState();
}

void AWolframActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Apply Wolfram rule and log result each frame
    ApplyWolframRule();
    LogCellularState();
}

void AWolframActor::ApplyWolframRule()
{
    // Create a copy to store the next generation
    TArray<bool> NextGeneration;
    NextGeneration.SetNum(CellArray.Num());

    // Apply rule to each cell
    for (int32 i = 0; i < CellArray.Num(); i++)
    {
        // Get neighbors (with wrapping for boundary conditions)
        bool LeftNeighbor = CellArray[(i - 1 + CellArray.Num()) % CellArray.Num()];
        bool Center = CellArray[i];
        bool RightNeighbor = CellArray[(i + 1) % CellArray.Num()];

        // Calculate next state
        NextGeneration[i] = GetNextCellState(LeftNeighbor, Center, RightNeighbor);
    }

    // Update the cell array
    CellArray = NextGeneration;
}

bool AWolframActor::GetNextCellState(bool Left, bool Center, bool Right) const
{
    // Convert the three neighbors to a 3-bit number (0-7)
    int32 Pattern = (Left ? 4 : 0) + (Center ? 2 : 0) + (Right ? 1 : 0);
    // -> Left|Center|Right
    // ex: false/true/true -> 0+2+1 -> 0b011 = pattern

    // The rule number tells us which patterns result in a live cell
    // We check if the bit at position 'Pattern' is set in the rule number

    /**
     * ex:
     * rule: 30
     * left: true
     * center: false
     * right: true
     *
     * pattern: 0b101 = 5
     *
     * 1 << Pattern: 0b00000001 << 5 = 0b00100000
     * rule, en binaire:               0b00011110
     * rule & (1 << pattern)           0b00000000
     */

    return (Rule & (1 << Pattern)) != 0;
}

void AWolframActor::LogCellularState() const
{
    FString StateString = "";

    for (bool Cell : CellArray)
    {
        StateString += Cell ? "X" : " ";
    }

    UE_LOG(LogTemp, Warning, TEXT("%s"), *StateString);
}