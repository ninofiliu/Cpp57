#include "SimpleGraph.h"

ASimpleGraph::ASimpleGraph()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASimpleGraph::BeginPlay()
{
	Super::BeginPlay();
}

void ASimpleGraph::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
