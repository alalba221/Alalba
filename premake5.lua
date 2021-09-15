workspace "Alalba"
	architecture "x64"
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


--Include directories relatice to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Alalba/vendor/GLFW/include"
IncludeDir["Glad"] = "Alalba/vendor/Glad/include"
IncludeDir["spdlog"] = "Alalba/vendor/spdlog/include"
IncludeDir["imgui"] = "Alalba/vendor/imgui"

group"Dependencies"
	include "Alalba/vendor/GLFW"
	include "Alalba/vendor/Glad"
	include "Alalba/vendor/imgui"
group""


project "Alalba"
	location "Alalba"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/"..outputdir.."/%{prj.name}")
	objdir ("bin-int/"..outputdir.."/%{prj.name}")

	pchheader "alalbapch.h"
	pchsource "Alalba/src/alalbapch.cpp"
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.imgui}"
	}
	links
	{
		"Glad",
		"GLFW",
		"dl",
		"pthread",
		"ImGui"
	}
	filter "system:linux"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		buildoptions "-fpermissive"
		defines
		{
			"ALALBA_PLATFORM_LINUX",
			"ALALBA_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}
	postbuildcommands
		{
			(" {MKDIR} ../bin/"..outputdir.."/Sandbox/"),
			("{COPY} %{cfg.buildtarget.relpath} ../bin/"..outputdir.."/Sandbox/")
		}

	filter "configurations:Debug"
		defines "ALALBA_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "ALALBA_RELEASE"
		optimize "On"
	filter "configurations:Dist"
		defines "ALALBA_Dist"
		optimize "On"
	

project "Sandbox"
	
		kind "ConsoleApp"
		language "C++"
	
		targetdir ("bin/"..outputdir.."/%{prj.name}")
		objdir ("bin-int/"..outputdir.."/%{prj.name}")
		
		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp",
			
		}
		includedirs
		{
			"Alalba/src",
			"%{IncludeDir.spdlog}",
			"Alalba/vendor"
		}
		links
		{
			"Alalba",
			"ImGui"
		}
		filter "system:linux"
			cppdialect "C++17"
			staticruntime "On"
			systemversion "latest"
			buildoptions "-fpermissive"
			defines
			{
				"ALALBA_PLATFORM_LINUX"
			}
		filter "configurations:Debug"
			defines "ALALBA_DEBUG"
			symbols "On"
			
		filter "configurations:Release"
			defines "ALALBA_RELEASE"
			optimize "On"
		filter "configurations:Dist"
			defines "ALALBA_Dist"
			optimize "On"
	
	