#pragma once

#include <Core/Application.h>
#include <Florencia/Core/LayerStack.h>

#define FLO_APP_CONSTRUCTOR(classname, appname) classname():Application(appname)
#define FLO_CREATE_APP(appname) Application* CreateApplication() { return new appname(); }