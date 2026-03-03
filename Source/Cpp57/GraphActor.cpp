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

void AGraphActor::RunBFS()
{
    if (Nodes.Num() == 0 || !Nodes[0])
        return;

    // Build adjacency list (bidirectional)
    TMap<AActor *, TArray<AActor *>> Adjacency;
    for (const FGraphEdge &Edge : Edges)
    {
        if (Edge.From && Edge.To)
        {
            Adjacency.FindOrAdd(Edge.From).Add(Edge.To);
            Adjacency.FindOrAdd(Edge.To).Add(Edge.From);
        }
    }

    TSet<AActor *> Visited;
    TQueue<AActor *> Queue;

    AActor *Start = Nodes[0];
    Visited.Add(Start);
    Queue.Enqueue(Start);
    DrawDebugSphere(GetWorld(), Start->GetActorLocation(), 100.f, 16, FColor::Green, false, 5.f);

    while (!Queue.IsEmpty())
    {
        AActor *Current;
        Queue.Dequeue(Current);

        TArray<AActor *> *Neighbors = Adjacency.Find(Current);
        if (!Neighbors)
            continue;

        for (AActor *Neighbor : *Neighbors)
        {
            if (!Neighbor || Visited.Contains(Neighbor))
                continue;

            Visited.Add(Neighbor);
            Queue.Enqueue(Neighbor);

            DrawDebugSphere(GetWorld(), Neighbor->GetActorLocation(), 100.f, 16, FColor::Green, false, 5.f);
            DrawDebugLine(GetWorld(), Current->GetActorLocation(), Neighbor->GetActorLocation(), FColor::Green, false, 5.f);
        }
    }
}