module;
#include <Florencia/Core/PlatformDetection.h>
export module Window;
import <functional>;
import <stdint.h>;
import Event;

export namespace Florencia {

	struct WindowProps {
		WindowProps(const std::string& title, uint32_t width = 0, uint32_t height = 0) :Title(title), Width(width), Height(height) {}
		std::string Title;
		uint32_t Width, Height;
	};

	class Window {
	public:
		enum class Platform {
			Windows,
			Android,
			IPhone,
			Linux,
			MacOS,
			None
		};
		using EventCallbackFn = std::function<void(Event&)>;

		Window() = default;
		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		void SetEventCallback(const EventCallbackFn& function) { m_CallbackFunction = function; }

		//Window Attributes
		virtual void SetWidth(uint32_t width) = 0;
		virtual void SetHeight(uint32_t height) = 0;

		virtual void* GetWindowHandle() = 0;

		static Window* Create(const WindowProps& props);
		static Platform GetPlatform() { return s_Platform; }
	private:
		#if defined(FLO_PLATFORM_WINDOWS) || defined(FLO_PLATFORM_WINDOWS_32)
		static constexpr Platform s_Platform = Platform::Windows;
		#elif defined(FLO_PLATFORM_LINUX)
		static constexpr Platform s_Platform = Platform::Linux;
		#elif defined(FLO_PLATFORM_MACOS)
		static constexpr Platform s_Platform = Platform::MacOS;
		#elif defined(FLO_PLATFORM_IPHONE) || defined(FLO_PLATFORM_IPHONE_SIMULATOR)
		static constexpr Platform s_Platform = Platform::IPhone;
		#elif defined(FLO_PLATFORM_ANDROID)
		static constexpr Platform s_Platform = Platform::Android;
		#endif
	protected:
		EventCallbackFn m_CallbackFunction;
	};
}