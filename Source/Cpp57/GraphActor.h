#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMesh.h"
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
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Graph")
    TArray<AActor *> Nodes;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Graph")
    TArray<FGraphEdge> Edges;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Graph")
    UStaticMesh *EdgeMesh = nullptr;

    UFUNCTION(CallInEditor, Category = "Graph")
    void ConstructEdges();

    UFUNCTION(CallInEditor, Category = "Graph")
    void DrawDebug();

    UFUNCTION(CallInEditor, Category = "Graph")
    void RunBFS();
};
