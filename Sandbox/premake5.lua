project "Sandbox"
    kind "ConsoleApp"
    language "C++"

    objdir("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
    targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}") 

    includedirs { 
        "%{wks.location}/MatCore_R2/headers",
        "%{wks.location}/MatCore_R2/Dependece/glm",
        "%{wks.location}/MatCore_R2/Dependece/entt",
        "%{wks.location}/MatCore_R2/Dependece/spdlog/include"

    }

    files { 
        "./*.cpp",
        "./*.h"
    }

    links { "MatCore_R2" }