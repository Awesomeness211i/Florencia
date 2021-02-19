#pragma once

#define FLO_APPLICATION(classname) class classname : public Application
#define FLO_APP_CONSTRUCTOR(classname) classname(WindowProps& props) : Application(props)

#include <Florencia/Core/Application.h>
#include <Florencia/Core/EntryPoint.h>