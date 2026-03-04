#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DemoGraph.generated.h"

USTRUCT(BlueprintType)
struct FBiUnwEdge {
  GENERATED_BODY()

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  AActor *From;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  AActor *To;
};

UCLASS()
class CPP57_API ADemoGraph : public AActor {
  GENERATED_BODY()

public:
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Graph")
  TArray<FBiUnwEdge> Edges;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Graph")
  AActor *Start;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Graph")
  AActor *End;

  UFUNCTION(BlueprintCallable, CallInEditor, Category = "Graph")
  void DebugEdges();

  UFUNCTION(BlueprintCallable, CallInEditor, Category = "Graph")
  void BFS();

  UFUNCTION(BlueprintCallable, CallInEditor, Category = "Graph")
  void PathFind();
};
