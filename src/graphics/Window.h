#pragma once

#include <GLFW/glfw3.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace graphics {

#define MAX_KEYS 1024
#define MAX_BUTTONS 32
#define INITIAL_WIDTH 1280
#define INITIAL_HEIGHT 896

	// callbacks
	void windowResize(GLFWwindow* window, int width, int height);
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

	class Window
	{

	private:
		bool resizeable;
		int width = INITIAL_WIDTH;
		int height = INITIAL_HEIGHT;
		const char* name;
		GLFWwindow* window;

		static bool keys[MAX_KEYS];
		static bool buttons[MAX_BUTTONS];

	public:
		Window(const char* name, bool resizeable);
		~Window();

		bool closed() const;
		void update();

		inline int getWidth() const { return width; }
		inline int getHeight() const { return height; }
		inline glm::vec2 getScale() const { return glm::vec2((float) width / INITIAL_WIDTH, (float) height / INITIAL_HEIGHT); }
		inline GLFWwindow* getWindow() const { return window; }

		static bool isKeyPressed(unsigned int keycode);
		static bool isButtonPressed(unsigned int button);
		glm::vec2 getMouseScreenPosition();

	private:
		bool init();
		friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	
	};

}


