// Created by Modar Nasser on 16/11/2020.

#pragma once

#include <string>

#include "../thirdparty/json_fwd.h"
#include "../containers/TagsContainer.h"
#include "../defs/FieldDef.h"
#include "../DataTypes.h"
#include "../Tileset.h"

namespace ldtk {

    class Project;

    class EntityDef : public TagsContainer {
    public:
        const std::string name;
        const int uid;
        const IntPoint size;
        const Color color;
        const FloatPoint pivot;
        const Tileset* tileset;
        const IntRect texture_rect;
        std::vector<FieldDef> fields;

        EntityDef(const nlohmann::json& j, Project* p);
    };

}
