#pragma once

#include "Object.h"

namespace s2d
{
    class Text : public Object
    {

    public:

        std::string text;
        glm::vec2 textScale = glm::vec2(1.0f);

        Text()
        {
            this->renderType = TEXT;
            setRenderLayer(HUD_LAYER);
        }
        Text(std::string text)
        {
            this->text = text;
            this->renderType = TEXT;
            setRenderLayer(HUD_LAYER);
        }
        ~Text()
        {

        }

    };
}

