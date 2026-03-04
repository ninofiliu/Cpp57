#include "GraphActor.h"
#include "DrawDebugHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Algo/Reverse.h"

static const FName EdgeMeshTag = FName("GraphEdgeMesh");

void AGraphActor::ConstructEdges()
{
    if (!EdgeMesh)
        return;

    // Destroy previously spawned edge mesh components
    for (UActorComponent *Comp : GetComponentsByTag(UStaticMeshComponent::StaticClass(), EdgeMeshTag))
        Comp->DestroyComponent();

    // Track unique unordered pairs to skip duplicates (A,B) == (B,A)
    TSet<TPair<AActor *, AActor *>> SeenPairs;

    for (const FGraphEdge &Edge : Edges)
    {
        if (!Edge.From || !Edge.To || Edge.From == Edge.To)
            continue;

        // Canonical ordering so (A,B) and (B,A) map to the same key
        AActor *Key1 = Edge.From < Edge.To ? Edge.From : Edge.To;
        AActor *Key2 = Edge.From < Edge.To ? Edge.To : Edge.From;
        const TPair<AActor *, AActor *> Pair(Key1, Key2);
        if (SeenPairs.Contains(Pair))
            continue;
        SeenPairs.Add(Pair);

        const FVector LocA = Edge.From->GetActorLocation();
        const FVector LocB = Edge.To->GetActorLocation();
        const FVector Midpoint = (LocA + LocB) * 0.5f;
        const FVector Direction = (LocB - LocA).GetSafeNormal();
        const float Distance = FVector::Dist(LocA, LocB);

        // Default UE cylinder: radius 50 cm, height 100 cm, aligned along Z
        // Target: radius 10 cm (20 cm tube), height = Distance
        const FVector Scale(10.f / 50.f, 10.f / 50.f, Distance / 100.f);
        const FRotator Rotation = FRotationMatrix::MakeFromZ(Direction).Rotator();

        UStaticMeshComponent *MeshComp = NewObject<UStaticMeshComponent>(this);
        MeshComp->SetStaticMesh(EdgeMesh);
        MeshComp->ComponentTags.Add(EdgeMeshTag);
        MeshComp->RegisterComponent();
        AddInstanceComponent(MeshComp);
        MeshComp->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
        MeshComp->SetWorldTransform(FTransform(Rotation, Midpoint, Scale));
    }
}

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
    TMap<AActor *, AActor *> Froms;

    AActor *Start = Nodes[0];
    Visited.Add(Start);
    Queue.Enqueue(Start);

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

            Froms.Add(Neighbor, Current);
            Visited.Add(Neighbor);
            Queue.Enqueue(Neighbor);
        }
    }

    TArray<AActor *> Path;
    Path.Add(Nodes.Last());
    while (AActor **FromPtr = Froms.Find(Path.Last()))
    {
        Path.Add(*FromPtr);
    }
    Algo::Reverse(Path);

    for (auto Node : Path)
    {
        DrawDebugSphere(GetWorld(), Node->GetActorLocation(), 100.f, 16, FColor::Green, false, 5.f);
    }
}