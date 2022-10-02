#include "SpriteRenderer.h"


namespace s2d
{

	SpriteRenderer::SpriteRenderer(graphics::Shader* shader)
	{
        init();
        this->shader = shader;
        this->shader->use();
        this->shader->setInt("u_Texture", 0);
	}

	SpriteRenderer::~SpriteRenderer()
	{
        glDeleteVertexArrays(1, &this->VAO);
	}

	void SpriteRenderer::render(
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
        )
	{
        // prepare shader
        shader->use();
        shader->setMat4("u_Model", model);
        shader->setMat4("u_View", view);
        shader->setMat4("u_Projection", projection);
        shader->setBool("u_UseTexture", useTexture);
        if (useTexture)
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, textureID);
            shader->setFloat("u_NumberOfRows", numberOfRows);
            shader->setFloat("u_NumberOfCols", numberOfCols);
            shader->setVec2("u_TextureOffset", textureOffset);
        }
        shader->setVec3("u_SpriteColor", spriteColor);
        shader->setFloat("u_Alpha", alpha);
        // bind and draw
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
	}

	void SpriteRenderer::init()
	{
        // configure VAO/VBO
        unsigned int VBO;
        float vertices[] = {
            // pos      // tex
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,

            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f
        };

        glGenVertexArrays(1, &this->VAO);
        glGenBuffers(1, &VBO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindVertexArray(this->VAO);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
	}

}