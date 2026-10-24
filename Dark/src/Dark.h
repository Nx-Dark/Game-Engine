#pragma once

//To be Included by Applications using this Dark Engine/ Or by the client!

#include "dpch.h"

#include "Dark/Core/Application.h"
#include "Dark/Core/Input.h"
#include "Dark/Core/Core.h"
#include "Dark/Core/Log.h"
#include "Dark/Core/Assert.h"
#include "Dark/Core/Layer.h"

#include "Dark/Core/Timer.h"
#include "Dark/Core/DeltaTime.h"

//-------------------------------------------

//----Renderer---------------------------------
#include "Dark/Renderer/Renderer.h"
#include "Dark/Renderer/Renderer2D.h"

#include "Dark/Renderer/RenderCommand.h"

#include "Dark/Renderer/VertexArray.h"
#include "Dark/Renderer/Buffer.h"
#include "Dark/Renderer/Shader.h"
#include "Dark/Renderer/Framebuffer.h"
#include "Dark/Renderer/Texture.h"
#include "Dark/Renderer/SubTexture.h"

#include "Dark/Renderer/EditorCamera.h"

//--Entity Component System and Scene--
#include "Dark/Scene/Scene.h"
#include "Dark/Scene/SceneCamera.h"
#include "Dark/Scene/Components.h"
#include "Dark/Scene/Entity.h"
#include "Dark/Scene/ScriptableEntity.h"

//audio
#include "Dark/Audio/AudioMixer.h"

//Math and stuff--------------//
#include "Dark/Math/Math.h"
//----------------------------//

//Utils
#include "Dark/Utils/PlatformUtils.h"

//--ImGui---------------
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
//----------------------