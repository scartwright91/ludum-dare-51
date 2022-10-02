// Created by Modar Nasser on 25/02/2022.

#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "thirdparty/json_fwd.h"

#include "defs/EntityDef.h"
#include "defs/LayerDef.h"
#include "DataTypes.h"
#include "Enum.h"
#include "Level.h"
#include "Tileset.h"
#include "World.h"

namespace ldtk {
    class Project {
    public:
        Project() = default;
        Project(const Project&) = delete;
        Project(Project&&) = default;
        auto operator=(const Project&) -> Project& = delete;

        void loadFromFile(const std::string& filepath);
        void loadFromFile(const std::string& filepath, const FileLoader& file_loader);

        void loadFromMemory(const std::vector<std::uint8_t>& bytes);
        void loadFromMemory(unsigned char* data, unsigned int size);

        auto getFilePath() const -> const FilePath&;

        auto getDefaultPivot() const -> const FloatPoint&;

        auto getDefaultCellSize() const -> int;

        auto getBgColor() const -> const Color&;

        auto getLayerDef(int id) const -> const LayerDef&;
        auto getLayerDef(const std::string& name) const -> const LayerDef&;

        auto getEntityDef(int id) const -> const EntityDef&;
        auto getEntityDef(const std::string& name) const -> const EntityDef&;

        auto allTilesets() const -> const std::vector<Tileset>&;
        auto getTileset(int id) const -> const Tileset&;
        auto getTileset(const std::string& name) const -> const Tileset&;

        auto getEnum(int id) const -> const Enum&;
        auto getEnum(const std::string& name) const -> const Enum&;

        auto allWorlds() const -> const std::vector<World>&;
        auto getWorld() const -> const World&;
        auto getWorld(const std::string& name) const -> const World&;
        auto getWorld(const IID& iid) const -> const World&;

    private:
        void load(const nlohmann::json& j, const FileLoader& file_loader, bool from_memory);

        FilePath m_file_path;
        FloatPoint m_default_pivot;
        int m_default_cell_size = 0;
        Color m_background_color;

        std::vector<LayerDef> m_layers_defs;
        std::vector<EntityDef> m_entities_defs;
        std::vector<Tileset> m_tilesets;
        std::vector<Enum> m_enums;

        std::vector<World> m_worlds;
    };
}
