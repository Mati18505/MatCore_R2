//Plik dołączeniowy dla aplikacji korzystających z MatCore
#pragma once

//Main
#include "Application.h"
#include "Scene.h"

//Narzędzia IO
#include "Log.h"
#include "Input.h"
#include "KeyCodes.h"
#include "MouseButtonCodes.h"
#include "SceneSerializer.h"

//Narzędzia
#include "Entity.h"
#include "Model.h"
#include "Mesh.h"
#include "PlatformUtils.h"
#include "Resource.h"
#include "OpenGL/TextureBuffer.h"
#include "ShaderLibrary.h"

//Komponenty
#include "TagComponent.h"
#include "Transform.h"
#include "MeshComponent.h"
#include "Material.h"
#include "InheritanceComponent.h"
#include "CameraComponent.h"
#include "NativeScriptComponent.h"

//Eventy
#include "Events/ApplicationEvents.h"
#include "Events/KeyboardEvents.h"
#include "Events/MouseEvents.h"

extern MatCore::Application* applicationP;