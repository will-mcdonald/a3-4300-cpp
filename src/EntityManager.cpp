#include "EntityManager.h"
#include "Entity.h"
#include <memory>
#include <vector>

EntityManager::EntityManager() {}

void EntityManager::update()
{
    // add entities from m_entitiesToAdd the proper location(s)
    //   - add them to the vector of all entities
    //   - add them to the vector inside the map, with the tag as a k
    for (auto e : m_entitiesToAdd)
    {
        m_entities.push_back(e);
        m_entityMap[e->tag()].push_back(e);
    }
    m_entitiesToAdd.clear();

    // remove dead entities from the vector of all entities
    removeDeadEntities(m_entities);

    // remove dead entities from each vector in the entity map
    // C++20 way of iterating through [key, value] pairs in a map
    for (auto &[tag, entityVec] : m_entityMap)
    {
        removeDeadEntities(entityVec);
    }
}

void EntityManager::removeDeadEntities(EntityVec &vec)
{
    // Use std::remove_if to move dead entities to the end of the vector
    // and return the iterator to the new end of the vector.
    auto newEnd = std::remove_if(
        vec.begin(),
        vec.end(),
        [](std::shared_ptr<Entity> e)
        {
            return !e->isActive(); // predicate to remove dead entities
        });

    // Erase the elements from the new end to the original end of the vector
    vec.erase(newEnd, vec.end());
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string &tag)
{
    auto entity = std::shared_ptr<Entity>(new Entity(m_totalEntities++, tag));
    m_entitiesToAdd.push_back(entity);

    return entity;
}

const EntityVec &EntityManager::getEntities()
{
    return m_entities;
}

const EntityVec &EntityManager::getEntities(const std::string &tag)
{
    return m_entityMap[tag];
}

const std::map<std::string, EntityVec> &EntityManager::getEntityMap()
{
    return m_entityMap;
}
