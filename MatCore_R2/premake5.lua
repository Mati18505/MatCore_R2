project "MatCore_R2"
    kind "StaticLib"
    language "C++"

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
        "./headers/**.h",
        "./Dependece/stb_image/stb_image.cpp"
    }

    libdirs {
        "./Dependece/assimp/dynamicDebug"
    }

    links { "glad", "glfw", "assimp-vc142-mtd", "Dwmapi", "yaml-cpp" } --opengl32.lib?