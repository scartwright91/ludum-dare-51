#pragma once

#include <GLEW/glew.h>
#include <glm/glm.hpp>

#include "../graphics/Shader.h"


namespace s2d
{
	class SpriteRenderer
	{

	public:

		SpriteRenderer(graphics::Shader* shader);
		~SpriteRenderer();

		void render(
			glm::mat4 model,
			glm::mat4 view,
			glm::mat4 projection,
			unsigned int textureID,
			bool useTexture,
			float numberOfRows,
			float numberOfCols,
			glm::vec2 textureOffset,
			glm::vec3 spriteColor,
			float alpha
		);

	private:

		graphics::Shader* shader;
		unsigned int VAO = 0;

		void init();

	};
}

