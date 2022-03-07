#include "EntityFactory.h"

AbstractEntity* EntityFactory::Create(const std::string& className) {
    if (className == "BlockEntity") {
        int shapeNumber = rand()%((shapes.size() - 1) - 0 + 1);
        BlockEntity *block =  new BlockEntity(shapeNumber + 1);
        block->SetParts(shapes.at(shapeNumber));
        return block;
    }
    return nullptr;
}
