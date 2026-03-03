#include "GraphActor.h"
#include "DrawDebugHelpers.h"

void AGraphActor::DrawDebug()
{
    for (AActor *Node : Nodes)
    {
        if (Node)
        {
            const FVector Location = Node->GetActorLocation();
            DrawDebugSphere(GetWorld(), Location, 100.f, 16, FColor::Cyan, false, 5.f);
        }
    }
    for (auto Edge : Edges)
    {
        if (Edge.From && Edge.To)
        {
            DrawDebugLine(GetWorld(), Edge.From->GetActorLocation(), Edge.To->GetActorLocation(), FColor::Emerald, false, 5.f);
        }
    }
}
