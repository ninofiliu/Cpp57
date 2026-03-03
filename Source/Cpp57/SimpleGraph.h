// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SimpleGraph.generated.h"

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
class CPP57_API ASimpleGraph : public AActor
{
	GENERATED_BODY()

public:
	ASimpleGraph();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SimpleGraph")
	TArray<AActor *> Nodes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SimpleGraph")
	TArray<FGraphEdge> Edges;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
