#pragma once

//To be Included by Applications using this Dark Engine/ Or by the client!

#include "dpch.h"

#include "Dark/Core/Application.h"
#include "Dark/Core/Input.h"
#include "Dark/Core/Log.h"
#include "Dark/Core/Core.h"
#include "Dark/Core/Layer.h"

#include "Dark/Core/Timer.h"
#include "Dark/Core/DeltaTime.h"

//----Renderer---------------------------------
#include "Dark/Renderer/Renderer.h"
#include "Dark/Renderer/Renderer2D.h"

#include "Dark/Renderer/RenderCommand.h"

#include "Dark/Renderer/VertexArray.h"
#include "Dark/Renderer/Buffer.h"
#include "Dark/Renderer/Shader.h"
#include "Dark/Renderer/Texture.h"

#include "Dark/Renderer/OrthoGraphicCamera.h"
#include "Dark/Renderer/OrthoGraphicCameraController.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//---------------------------------------------

//--ImGui---------------
#include <imgui/imgui.h>
//----------------------