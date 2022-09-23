#pragma once

#include <core/app/Window.h>
#include <GLFW/glfw3.h>

#include <core/app/EventDispatcher.h>

namespace Xen {

	struct UserPointer
	{
		WindowProps props;
		EventDispatcher dispatcher;

		uint8_t monitor_count;
		GLFWmonitor** monitors;
	};

	class XEN_API GLFW_window : public Window
	{
	private:
		GLFWwindow* m_Window;
		GLFWcursor* m_Cursor;

		UserPointer m_UserPointer;

	public:
		GLFW_window(const WindowProps& props);
		GLFW_window() {}
		virtual ~GLFW_window() { GLFW_window::Shutdown(); }

		void Create() override;
		void Update() override;
		void Shutdown() override;

		void SetWindowResolution(uint32_t width, uint32_t height) override;
		void SetWindowMaxResolution(uint32_t width, uint32_t height) override;
		void SetWindowMinResolution(uint32_t width, uint32_t height) override;
		void SetWindowTitle(const std::string& title) override;

		void SetWindowIcon(const std::string& icon_path) override;
		void SetCursorIcon(const std::string& icon_path) override;

		void MinimizeWindow() override;
		void MaximizeWindow() override;

		void ShowWindow(bool show) override;
		void FocusWindow() override;

		void SetVsync(bool enabled) override;

		virtual void* GetNativeWindow() const override { return m_Window; }

		inline uint32_t GetWidth() const override 
		{
			int width;
			glfwGetWindowSize(m_Window, &width, nullptr);
			return (uint32_t)width;
		}

		inline uint32_t GetHeight() const override
		{
			int height;
			glfwGetWindowSize(m_Window, nullptr, &height);
			return (uint32_t)height;
		}

		void SetFullScreenMonitor(const Ref<Monitor>& monitor) override;
		void SetWindowed() override;

		inline const std::string& GetTitle() const override { return m_UserPointer.props.title; }
		inline bool IsVsync() const override { return m_UserPointer.props.vsync; }

		void SetupEventListeners(const EventDispatcher& dispacher) override;
	};

}
