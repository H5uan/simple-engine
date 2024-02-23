#pragma once
#include <typeindex>
#include <unordered_set>
#include <typeinfo>
#include <algorithm> // For std::all_of

namespace RXECS
{
    struct ComponentHash
    {
        std::unordered_set<size_t> componentHashes;

    private:
        // Utility function to compute hash for a component type.
        template <typename ComponentType>
        static size_t ComputeHash()
        {
            return std::hash<std::type_index>{}(std::type_index(typeid(ComponentType)));
        }

    public:
        // Adds a component type to the component hash set.
        template <typename ComponentType>
        void AddComponent()
        {
            componentHashes.insert(ComputeHash<ComponentType>());
        }

        // Removes a component type from the component hash set.
        template <typename ComponentType>
        void RemoveComponent()
        {
            componentHashes.erase(ComputeHash<ComponentType>());
        }

        // Checks if this ComponentHash matches another ComponentHash (systemHash).
        bool matches(const ComponentHash& systemHash) const
        {
            // Early exit if systemHash has more components than this ComponentHash
            if (systemHash.componentHashes.size() > componentHashes.size()) return false;

            return std::all_of(systemHash.componentHashes.begin(), systemHash.componentHashes.end(),
                               [this](const size_t& hash)
                               {
                                   return componentHashes.find(hash) != componentHashes.end();
                               });
        }

        // Determines if this ComponentHash is a new match compared to an oldHash for a given systemHash.
        bool IsNewMatch(const ComponentHash& i_OldHash, const ComponentHash& i_SystemHash) const
        {
            return matches(i_SystemHash) && !i_OldHash.matches(i_SystemHash);
        }

        // Determines if this ComponentHash is no longer a match compared to an oldHash for a given systemHash.
        bool IsNoLongerMatched(const ComponentHash& i_OldHash, const ComponentHash& i_SystemHash) const
        {
            return i_OldHash.matches(i_SystemHash) && !matches(i_SystemHash);
        }
    };
}
