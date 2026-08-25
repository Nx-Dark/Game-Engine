#pragma once

//To be Included by Applications using this Dark Engine/ Or by the client!

#include "dpch.h"

#include "Dark/Application.h"
#include "Dark/Input.h"
#include "Dark/Log.h"
#include "Dark/Core.h"
#include "Dark/Layer.h"
#include "Dark/OrthoGraphicCameraController.h"

#include "Dark/Core/Timer.h"
#include "Dark/Core/DeltaTime.h"

//----Renderer---------------------------------
#include "Dark/Renderer/Renderer.h"
#include "Dark/Renderer/RenderCommand.h"

#include "Dark/Renderer/VertexArray.h"
#include "Dark/Renderer/Buffer.h"
#include "Dark/Renderer/Shader.h"
#include "Dark/Renderer/Texture.h"

#include "Dark/Renderer/OrthoGraphicCamera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//---------------------------------------------

//--ImGui---------------
#include <imgui/imgui.h>
//----------------------

/*--Entry Point--*/
#include "Dark/EntryPoint.h"
/*---------------*/