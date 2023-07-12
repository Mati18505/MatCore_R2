project "MatCore_R2"
    kind "StaticLib"
    language "C++"

    pchheader "pch.h"
    pchsource "./source/pch.cpp"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}") 
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    includedirs {
        "./headers",
        "./Dependece/glfw/include",
        "./Dependece/glm",
        "./Dependece/glad/include",
        "./Dependece/entt",
        "./Dependece/spdlog/include",
        "./Dependece/stb_image",
        "./Dependece/assimp/include",
        "./Dependece/yaml-cpp-master/include"
    }

    files {
        "./source/**.cpp",
        "./headers/**.h"
    }

    libdirs {
        "./Dependece/assimp/dynamicDebug"
    }

    links { "glad", "glfw", "assimp-vc142-mtd", "Dwmapi", "yaml-cpp", "stb_image" } --opengl32.lib?