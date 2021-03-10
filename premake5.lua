workspace "Filbert"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Filbert"
    location "Filbert"
    kind "SharedLib"
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
        "%{prj.name}/vendor/spdlog/include"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "FB_PLATFORM_WINDOWS",
            "FILBERT_BUILD_DLL"
        }

    filter "configurations:Debug"
        defines "FB_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "FB_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "FB_DIST"
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
        staticruntime "On"
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
        symbols "On"

    filter "configurations:Release"
        defines "FB_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "FB_DIST"
        optimize "On"