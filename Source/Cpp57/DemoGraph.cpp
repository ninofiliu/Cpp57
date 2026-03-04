
#include "DemoGraph.h"

void ADemoGraph::DebugEdges() {
  for (auto Edge : Edges) {
    if (!Edge.From || !Edge.To) {
      UE_LOG(LogTemp, Error, TEXT("Edges should not have empty members"));
      continue;
    } else {
      DrawDebugLine(GetWorld(), Edge.From->GetActorLocation(),
                    Edge.To->GetActorLocation(), FColor::Green, false, 5.0f, 0,
                    3.0f);
    }
  }
}

void ADemoGraph::BFS() {
  // initial checks
  for (auto Edge : Edges) {
    if (!Edge.From || !Edge.To) {
      UE_LOG(LogTemp, Error, TEXT("Edges should not have empty members"));
      return;
    }
  }
  if (!Start) {
    UE_LOG(LogTemp, Error, TEXT("Start should be defined"));
    return;
  }

  // collect neighbors
  TMap<AActor *, TSet<AActor *>> Adjacency;
  for (auto Edge : Edges) {
    Adjacency.FindOrAdd(Edge.From).Add(Edge.To);
  }

  TSet<AActor *> Visited;
  TArray<AActor *> ToVisit;
  ToVisit.Add(Start);
  while (!ToVisit.IsEmpty()) {
    auto Current = ToVisit[0];
    ToVisit.RemoveAt(0);
    Visited.Add(Current);
    auto Neighbors = Adjacency.Find(Current);
    if (!Neighbors) {
      continue;
    }
    for (auto Neighbor : *Adjacency.Find(Current)) {
      if (Visited.Contains(Neighbor)) {
        continue;
      }
      if (ToVisit.Contains(Neighbor)) {
        continue;
      }
      ToVisit.Add(Neighbor);
      DrawDebugLine(GetWorld(), Current->GetActorLocation(),
                    Neighbor->GetActorLocation(), FColor::Green, false, 5.0f);
    }
  }
}