project "ImGUI"
    kind "StaticLib"
	language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	includedirs {
		"%{wks.location}/MatCore_R2/Dependece/glfw/include"
	}

    files {
        "*.cpp",
        "*.h"
    }
	
	systemversion "latest"
	cppdialect "C++17"
	
	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
		
	links { "glfw" }