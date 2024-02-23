#pragma once
#include <type_traits>
#include "ComponentManager.h"
#include "Entity.h"
/*
  This is the base implementation of a component. To create your own component:

  struct Position : Component {
    int x;
    int y;
  }
*/
namespace RXECS
{
    struct ComponentCounter
    {
        static int familyCounter;
    };

    template <typename ComponentType>
    struct Component
    {
        static inline int family()
        {
            static int family = ComponentCounter::familyCounter++;
            return family;
        }
    };

    // Util method for getting family given type
    template <typename C>
    static int GetComponentFamily()
    {
        return Component<typename std::remove_const<C>::type>::family();
    }
}
