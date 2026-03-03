#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GraphActor.generated.h"

USTRUCT(BlueprintType)
struct FGraphEdge
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    AActor *From = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    AActor *To = nullptr;
};

UCLASS()
class CPP57_API AGraphActor : public AActor
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<AActor *> Nodes;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FGraphEdge> Edges;
};
