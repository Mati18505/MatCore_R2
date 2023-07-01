project "Editor"
    kind "ConsoleApp"
    language "C++"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}") 
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    includedirs {
        "%{prj.loaction}/Dependece",
        "%{wks.location}/MatCore_R2/headers",
        "%{wks.location}/MatCore_R2/Dependece/glm",
        "%{wks.location}/MatCore_R2/Dependece/entt",
        "%{wks.location}/MatCore_R2/Dependece/spdlog/include"
    }

    files {
        "./*.cpp",
        "./*.h"
    }

    links { "MatCore_R2", "ImGUI" }

    characterset "MBCS"