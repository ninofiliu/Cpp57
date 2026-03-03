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
	auto World = GetWorld();
	if (!World)
	{
		return;
	}
	for (int i = 0; i < Nodes.Num(); i++)
	{
		auto Node = Nodes[i];
		if (!IsValid(Node))
		{
			continue;
		}
		DrawDebugSphere(World, Node->GetActorLocation(), 100, 12, FColor::Emerald);
	}
	for (int i = 0; i < Edges.Num(); i++)
	{
		auto Edge = Edges[i];
		if (!IsValid(Edge.From) || !IsValid(Edge.To))
		{
			continue;
		}
		DrawDebugDirectionalArrow(World, Edge.From->GetActorLocation(), Edge.To->GetActorLocation(), 20, FColor::Cyan);
	}
}
