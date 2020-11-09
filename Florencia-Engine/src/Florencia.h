#pragma once

#define FLO_APP_CONSTRUCTOR(appname) appname():Application("Flo Editor")
#define FLO_CREATE_APP(appname) Application* CreateApplication() { return new appname(); }

#include <Core/EntryPoint.h>
namespace Florencia {
	class OrthographicCamera;
	class PerspectiveCamera;
	class WindowResizeEvent;
	class WindowCloseEvent;
	class AppUpdateEvent;
	class AppRenderEvent;
	class AppTickEvent;
	class Application;
	class Renderer;
	class Camera;
	class Event;

	struct RenderData;
}