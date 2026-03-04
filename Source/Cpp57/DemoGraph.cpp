
#include "DemoGraph.h"

void ADemoGraph::DebugEdges() {
  for (auto Edge : Edges) {
    if (!Edge.From || !Edge.To) {
      UE_LOG(LogTemp, Error, TEXT("Edges should not have empty members"));
      continue;
    } else {
      DrawDebugLine(GetWorld(), Edge.From->GetActorLocation(),
                    Edge.To->GetActorLocation(), FColor::Green, false, 5.0f);
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

  // visit the whole graph
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
                    Neighbor->GetActorLocation(), FColor::Green, false, 5.0f, 0,
                    3.0f);
    }
  }
}

void ADemoGraph::PathFind() {
  TArray<AActor *> Path;

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
  if (!Start) {
    UE_LOG(LogTemp, Error, TEXT("End should be defined"));
    return;
  }

  // collect neighbors
  TMap<AActor *, TSet<AActor *>> Adjacency;
  for (auto Edge : Edges) {
    Adjacency.FindOrAdd(Edge.From).Add(Edge.To);
  }

  // visit the whole graph
  TSet<AActor *> Visited;
  TArray<AActor *> ToVisit;
  TMap<AActor *, AActor *> Parents;
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
      Parents.Add(Neighbor, Current);
      DrawDebugLine(GetWorld(), Current->GetActorLocation(),
                    Neighbor->GetActorLocation(), FColor::Cyan, false, 5.0f, 0,
                    3.0f);
    }
  }

  // build the path from walking up the parents chain
  AActor **ParentPtr = &End;
  while (ParentPtr) {
    Path.Add(*ParentPtr);
    ParentPtr = Parents.Find(*ParentPtr);
  }
  Algo::Reverse(Path);

  for (int i = 0; i < Path.Num() - 1; i++) {
    DrawDebugLine(GetWorld(), Path[i]->GetActorLocation(),
                  Path[i + 1]->GetActorLocation(), FColor::Yellow, false, 5.0f,
                  0, 6.0f);
  }

  return;
}