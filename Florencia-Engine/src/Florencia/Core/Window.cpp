#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "Window.h"
#include "Florencia/Events/KeyEvent.h"
#include "Florencia/Events/MouseEvent.h"
#include "Florencia/Events/ApplicationEvent.h"

namespace Florencia {

	Window::Window(const WindowProps& props) : m_Properties(props) {
			if(!glfwInit()) {
				glfwTerminate();
			}
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			m_Window = glfwCreateWindow(m_Properties.Width, m_Properties.Height, m_Properties.Title.data(), NULL, NULL);
			if (!m_Window){
				// Window or OpenGL context creation failed
				glfwTerminate();
			}

			glfwSetWindowUserPointer(m_Window, &m_Properties);
			glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
				WindowProps& data = *(WindowProps*)glfwGetWindowUserPointer(window);
				WindowCloseEvent e;
				data.CallbackFunction(e);
			});
			glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height){
				WindowProps& data = *(WindowProps*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;

				WindowResizeEvent e(width, height);
				data.CallbackFunction(e);
			});
			glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods){
				WindowProps& data = *(WindowProps*)glfwGetWindowUserPointer(window);
				switch(action) {
					case GLFW_PRESS: {
						KeyPressedEvent e((Key)key, 0);
						data.CallbackFunction(e);
						break;
					}
					case GLFW_RELEASE: {
						KeyReleasedEvent e((Key)key);
						data.CallbackFunction(e);
						break;
					}
					case GLFW_REPEAT: {
						KeyPressedEvent e((Key)key, 1);
						data.CallbackFunction(e);
						break;
					}
				}
			});
			glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods){
				WindowProps& data = *(WindowProps*)glfwGetWindowUserPointer(window);
				switch(action) {
					case GLFW_PRESS: {
						MouseButtonPressedEvent e((MouseButton)button);
						data.CallbackFunction(e);
						break;
					}
					case GLFW_RELEASE: {
						MouseButtonReleasedEvent e((MouseButton)button);
						data.CallbackFunction(e);
						break;
					}
				}
			});
			glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset){
				WindowProps& data = *(WindowProps*)glfwGetWindowUserPointer(window);
				MouseScrolledEvent e(xOffset, yOffset);
				data.CallbackFunction(e);
			});
			glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos){
				WindowProps& data = *(WindowProps*)glfwGetWindowUserPointer(window);
				MouseMovedEvent e(xPos, yPos);
				data.CallbackFunction(e);
			});
			glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int character){
				WindowProps& data = *(WindowProps*)glfwGetWindowUserPointer(window);
				CharacterTypedEvent e((Character)character);
				data.CallbackFunction(e);
			});
		}

		Window::~Window() {
			if(m_Window) {
				glfwDestroyWindow(m_Window);
				glfwTerminate();
			}
		}

		void Window::Update() {
			glfwPollEvents();
		}

		void Window::Render() {

		}

}