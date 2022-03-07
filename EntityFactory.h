#ifndef ENTITY_FACTORY_H_
#define ENTITY_FACTORY_H_

#include <iostream>

#include "AbstractEntity.h"
#include "BlockEntity.h"

class EntityFactory
{
    public:
        AbstractEntity* Create(const std::string& className);

    private:
        std::vector<std::vector<std::vector<bool>>> shapes {
            {
                { true, true, false },
                { false, true, true }
            },
            {
                { false, true, true },
                { true, true, false }
            },
            {
                { true, true },
                { false, true },
                { false, true },
            },
            {
                { true, true },
                { true, true }
            },
            {
                { false, true, false },
                { true, true, true }
            },
            {
                { true, true },
                { true, false },
                { true, false }
            },
            {
                { true },
                { true },
                { true },
                { true }
            }
        };
};

#endif // ENTITY_FACTORY_H_