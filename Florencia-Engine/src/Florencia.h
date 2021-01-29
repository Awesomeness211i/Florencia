#pragma once
#include <Math/FloMath.h>
#include <Core/Application.h>
#include <Renderer/Renderer.h>

#include <Florencia/Core/EntryPoint.h>

#define FLO_APP_CONSTRUCTOR(classname) classname(WindowProps& props) : Application(props)
#define FLO_APPLICATION(classname) class classname : public Application