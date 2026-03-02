// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SimpleGraph.generated.h"

UCLASS()
class CPP57_API ASimpleGraph : public AActor
{
	GENERATED_BODY()

public:
	ASimpleGraph();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
