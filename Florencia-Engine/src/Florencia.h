#pragma once

#define FLO_CREATE_APP(appname) Application* CreateApplication() { return new appname(); }

#include "FloMath.h"

#include <Core/EntryPoint.h>
#include <Core/Application.h>