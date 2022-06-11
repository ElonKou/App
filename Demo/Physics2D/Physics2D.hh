#pragma once

#include "PhysicsScene2D.hh"
#include <set>
#include <unordered_map>

typedef struct CollItem {
    size_t a;
    size_t b;
} CollItem;

class Physics2D {
  public:
    std::shared_ptr<PhysicsScene2D> scene; // contains all scenc objects.

    std::unordered_map<int, std::set<int>> hashtables;      // position hash tables for collision detection.
    std::vector<CollItem>                  collision_pairs; // collision pairs.
    size_t                                 rows_cols;       // rows and cols for hash table.

    Physics2D();

    ~Physics2D();

    void UpdateObjects(float dt);

  private:
    void UpdateHashTables();

    void SetVelocity();

    void UpdatePosition(float dt = 0.016f);

    void ApplyBoundConstraint();

    void ApplyLinkConstraint();

    void SolveHashCollision();

    void SolveCollision();
};
