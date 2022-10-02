#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


namespace graphics
{
	class UI
	{

	public:
		UI();
		~UI();

		void init(GLFWwindow* window);
		void render();
		void destroy();

		inline float getSize() const { return size; }

	private:
		float size;


	};

}
