#pragma once

#include <Math/FloMath.h>
#include <Core/Application.h>
#include <Renderer/Renderer.h>
#include <Florencia/Core/LayerStack.h>

#define FLO_APP_CONSTRUCTOR(classname, appname) classname():Application(appname)
#define FLO_CREATE_APP(appname) Application* CreateApplication() { return new appname(); }
#define FLO_APPLICATION(classname) class classname : public Application