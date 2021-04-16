workspace "Filbert"
    architecture "x64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Filbert/vendor/GLFW/include"
IncludeDir["Glad"] = "Filbert/vendor/Glad/include"
IncludeDir["ImGui"] = "Filbert/vendor/imgui"

include "Filbert/vendor/GLFW"
include "Filbert/vendor/Glad"
include "Filbert/vendor/imgui"


project "Filbert"
    location "Filbert"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .."/%{prj.name}")
    objdir ("bin-int/" .. outputdir .."/%{prj.name}")

    pchheader "fbpch.h"
    pchsource "Filbert/src/fbpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "off"
        systemversion "latest"

        defines
        {
            "FB_PLATFORM_WINDOWS",
            "FILBERT_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug"
        defines "FB_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "FB_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "FB_DIST"
        runtime "Release"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    
    targetdir ("bin/" .. outputdir .."/%{prj.name}")
    objdir ("bin-int/" .. outputdir .."/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs
    {
        "Filbert/vendor/spdlog/include",
        "Filbert/src"
    }

    links
    {
        "Filbert"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "off"
        systemversion "latest"

        defines
        {
            "FB_PLATFORM_WINDOWS"
        }
        
        postbuildcommands
        {
	        ("{COPY} ../bin/" .. outputdir .. "/Filbert/Filbert.dll %{cfg.buildtarget.directory}")
        }

    filter "configurations:Debug"
        defines "FB_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "FB_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "FB_DIST"
        runtime "Release"
        optimize "On"