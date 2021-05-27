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
IncludeDir["glm"] = "Filbert/vendor/glm"


group "Dependencies"
    include "Filbert/vendor/GLFW"
    include "Filbert/vendor/Glad"
    include "Filbert/vendor/imgui"
    
group ""

project "Filbert"
    location "Filbert"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .."/%{prj.name}")
    objdir ("bin-int/" .. outputdir .."/%{prj.name}")

    pchheader "fbpch.h"
    pchsource "Filbert/src/fbpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl",
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}"
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"
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
        symbols "on"

    filter "configurations:Release"
        defines "FB_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "FB_DIST"
        runtime "Release"
        optimize "on"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"
    
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
        "Filbert/src",
        "Filbert/vendor",
        "%{IncludeDir.glm}"
    }

    links
    {
        "Filbert"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "FB_PLATFORM_WINDOWS"
        }
        

    filter "configurations:Debug"
        defines "FB_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "FB_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "FB_DIST"
        runtime "Release"
        optimize "on"