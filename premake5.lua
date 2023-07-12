workspace "MatCore"
    configurations { "Debug", "Release", "Dist" }
    platforms { "Win64" }
    startproject "Editor"

    flags { "MultiProcessorCompile" }

    outputdir = "%{cfg.platform}-%{cfg.buildcfg}"

    systemversion "latest"

    filter "configurations:Debug" 
        defines { "DEBUG" }
        symbols "on"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "on"

    filter "platforms:Win64"
        cppdialect "C++17"
        architecture "x86_64"
        buildoptions { "/ZI" }

    group "Dependencies"
        include "MatCore_R2/Dependece/glfw"
        include "MatCore_R2/Dependece/glad"
        include "Editor/Dependece/ImGUI"
        include "MatCore_R2/Dependece/yaml-cpp-master"
        include "MatCore_R2/Dependece/stb_image"

    group "Core"
        include "MatCore_R2"

    group "Tools"
        include "Editor"

    group "Applications"
        include "Sandbox"


workspace "*"
    newaction {
        trigger     = "clean",
        description = "Remove binaries, intermediate files and vs project files",
        execute     = function ()
        print("Removing binaries")
        os.rmdir("./bin")
        print("Removing intermediate files")
        os.rmdir("./bin-int")
        print("Removing project files")
        os.rmdir("./.vs")
        os.remove("**.sln")
        os.remove("**.vcxproj")
        os.remove("**.vcxproj.filters")
        os.remove("**.vcxproj.user")
        print("Done")
        end
    }