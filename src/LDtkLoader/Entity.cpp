// Created by Modar Nasser on 22/11/2020.

#include "Entity.h"
#include "World.h"
#include "json.h"

using namespace ldtk;

Entity::Entity(const nlohmann::json& j, const World* w) :
FieldsContainer(j["fieldInstances"], w),
iid(j.contains("iid") ? j["iid"].get<std::string>() : ""),
m_definition(&w->getEntityDef(j["defUid"].get<int>())),
m_size(j["width"].get<int>(), j["height"].get<int>()),
m_position(j["px"][0].get<int>(), j["px"][1].get<int>()),
m_grid_pos(j["__grid"][0].get<int>(), j["__grid"][1].get<int>()),
m_color(j.contains("__smartColor") ? Color(j["__smartColor"].get<std::string>()) : m_definition->color),
m_tileset(j["__tile"].is_null() ? nullptr : &w->getTileset(j["__tile"]["tilesetUid"].get<int>())),
m_texture_rect(j["__tile"].is_null() ? IntRect{} :
        j["__tile"].contains("x") ?
            IntRect{j["__tile"]["x"], j["__tile"]["y"], j["__tile"]["w"], j["__tile"]["h"]} :
            IntRect{j["__tile"]["srcRect"][0], j["__tile"]["srcRect"][1], j["__tile"]["srcRect"][2], j["__tile"]["srcRect"][3]} // v0.9.3
)
{}

auto Entity::getName() const -> const std::string& {
    return m_definition->name;
}

auto Entity::getSize() const -> const IntPoint& {
    return m_size;
}

auto Entity::getPosition() const -> const IntPoint& {
    return m_position;
}

auto Entity::getGridPosition() const -> const IntPoint& {
    return m_grid_pos;
}

auto Entity::getColor() const -> const Color& {
    return m_color;
}

auto Entity::getPivot() const -> const FloatPoint& {
    return m_definition->pivot;
}

auto Entity::hasSprite() const -> bool {
    return m_tileset != nullptr;
}

auto Entity::getTexturePath() const -> const std::string& {
    return m_tileset->path;
}

auto Entity::getTextureRect() const -> const IntRect& {
    return m_texture_rect;
}

auto Entity::hasTag(const std::string& tag) const -> bool {
    return m_definition->hasTag(tag);
}

auto Entity::getTags() const -> const std::vector<std::string>& {
    return m_definition->getTags();
}

auto Entity::allFields() const -> const std::vector<FieldDef>& {
    return m_definition->fields;
}
