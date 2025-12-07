#include "Entity.hpp"
namespace engine
{
const Entity::Id Entity::INVALID_ID = 0xffffffffffffffff;
BaseComponent::Family BaseComponent::mfamily_counter = 0;

bool Entity::IsValid() const { return mEntityManager->IsValidId(mId); }
} // namespace engine
