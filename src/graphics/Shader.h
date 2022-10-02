#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GLEW/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace graphics
{
	class Shader
	{

	public:

		unsigned int ID;
		Shader();
		Shader(const char* vertexPath, const char* fragmentPath);
		~Shader();

		void use();
		void setBool(const std::string& name, bool value) const;
		void setInt(const std::string& name, int value) const;
		void setFloat(const std::string& name, float value) const;
		void setMat4(const std::string& name, glm::mat4 value);
		void setVec2(const std::string& name, glm::vec2 value);
		void setVec3(const std::string& name, glm::vec3 value);
		void setVec4(const std::string& name, glm::vec4 value);

	private:
		void checkCompileErrors(unsigned int shader, std::string type);
	};
}

