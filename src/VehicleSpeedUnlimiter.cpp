#include <RED4ext/Common.hpp>
#include <RED4ext/Scripting/Natives/Generated/vehicle/BaseObject.hpp>
#include <RED4ext/Scripting/Natives/vehiclePhysicsData.hpp>
#include "Utils/ModModule.hpp"

// void vehicle::RigidBody::Recalculate(void)
REGISTER_FLIGHT_HOOK_HASH(short, 593628708, Recalculate, RED4ext::vehicle::PhysicsData *ps) {
  // apply force to linear velocity
  RED4ext::Vector3 unlimitedVelocity;
  unlimitedVelocity.X = ps->velocity.X + ps->force.X * ps->inverseMass;
  unlimitedVelocity.Y = ps->velocity.Y + ps->force.Y * ps->inverseMass;
  unlimitedVelocity.Z = ps->velocity.Z + ps->force.Z * ps->inverseMass;

  auto result = Recalculate_Original(ps);

  // ignore speed limit in og function
  if (result != FP_INFINITE) {
    ps->velocity = unlimitedVelocity;
  }

  return result;
}

// Vector4 vehicle::RigidBody::ForceSetLinearVelocity(Vector4 const &)
REGISTER_FLIGHT_HOOK_HASH(short, 4067628720, ForceSetLinearVelocity, RED4ext::vehicle::PhysicsData *vps, RED4ext::Vector3 *velocity) {
  auto result = ForceSetLinearVelocity_Original(vps, velocity);

  if (result != FP_INFINITE) {
    vps->velocity = *velocity;
  }

  return result;
}