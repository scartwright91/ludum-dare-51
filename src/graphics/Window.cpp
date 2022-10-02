#include "Window.h"

namespace graphics {

	bool Window::keys[MAX_KEYS];
	bool Window::buttons[MAX_BUTTONS];

	Window::Window(const char* name, bool resizeable)
	{
		this->name = name;
		this->resizeable = resizeable;
		if (!init())
			glfwTerminate();
		else
			std::cout << "Created game window" << std::endl;

		for (int i = 0; i < MAX_KEYS; i++)
		{
			keys[i] = false;
		}
		for (int i = 0; i < MAX_BUTTONS; i++)
		{
			buttons[i] = false;
		}
	}

	Window::~Window() 
	{
		glfwTerminate();
	}

	bool Window::init() {
		if (!glfwInit())
		{
			std::cout << "Failed to initialise GLFW" << std::endl;
			return false;
		}
		else
		{
			std::cout << "Initialised GLFW" << std::endl;
		}
		if (!resizeable)
			glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		window = glfwCreateWindow(width, height, name, NULL, NULL);
		if (!window)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			return false;
		}

		glfwMakeContextCurrent(window);
		glfwSetWindowSizeCallback(window, windowResize);
		glfwSetKeyCallback(window, key_callback);
		glfwSetMouseButtonCallback(window, mouse_button_callback);

		std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
		return true;
	}

	bool Window::closed() const
	{
		return glfwWindowShouldClose(window) == 1;
	}

	void Window::update()
	{
		if (!glfwWindowShouldClose(window))
		{
			glfwPollEvents();
			glfwGetFramebufferSize(window, &width, &height);
			glfwSwapBuffers(window);
		}
		else
		{
			glfwTerminate();
		}
	}

	bool Window::isKeyPressed(unsigned int keycode)
	{
		if (keycode >= MAX_KEYS)
			return false;
		return keys[keycode];
	}

	bool Window::isButtonPressed(unsigned int button)
	{
		if (button >= MAX_BUTTONS)
			return false;
		return buttons[button];
	}

	glm::vec2 Window::getMouseScreenPosition()
	{
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		return glm::vec2(x, getHeight() - y);
	}

	void windowResize(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->keys[key] = action != GLFW_RELEASE;
	}

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->buttons[button] = action != GLFW_RELEASE;
	}

}
