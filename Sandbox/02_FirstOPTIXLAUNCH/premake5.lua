project "02_FirstOPTIXLAUNCH"
	kind "ConsoleApp"
	staticruntime "on"
	language "C++"
	cppdialect "C++17"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
	
local SOURCE_DIR = "source/*"
    files
    { 
      SOURCE_DIR .. "**.h", 
      SOURCE_DIR .. "**.hpp", 
      SOURCE_DIR .. "**.c",
      SOURCE_DIR .. "**.cpp",
	--  SOURCE_DIR .. "**.cu"
    }
	
	defines
	{
		"ALALBA_PLATFORM_WINDOWS"
	}
	

	
	includedirs
	{
		"%{wks.location}/Alalba/vendor/spdlog/include",
		"%{wks.location}/Alalba/src",
		"%{wks.location}/Alalba/vendor",
		"%{IncludeDir.glm}",

		--"%{wks.location}/Alalba/vendor",

	}
	-- Directories relatice to project folder
	postbuildcommands
    {
			--("{COPY} %{cfg.buildtarget.relpath} ../bin/"..outputdir.."/Sandbox")
			--("{COPY} assets  %{wks.location}/bin/" ..outputdir .. "/%{prj.name}")
    }

--os.execute 'nvcc assets\deviceCode.cu -ptx -ccbin "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.30.30705\bin\Hostx64\x64" --gpu-architecture=compute_52 --use_fast_math --relocatable-device-code=true -I"C:\ProgramData\NVIDIA Corporation\OptiX SDK 7.4.0\include" -I"C:\ProgramData\NVIDIA Corporation\OptiX SDK 7.4.0\SDK" -I"C:\ProgramData\NVIDIA Corporation\OptiX SDK 7.4.0\SDK\cuda" -I"D:\Study\Alalba\Alalba\src\Alalba\Optix" -I"D:\Study\Alalba\Alalba\vendor\gdt\source\math" -I"D:\Study\Alalba\Alalba\vendor\gdt\source" -I"D:\Study\Alalba\Alalba\src" -o assets\deviceCode.ptx'
-- add settings common to all project
--os.execute('nvcc assets\deviceCode.cu -ptx -ccbin "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.30.30705\bin\Hostx64\x64" --gpu-architecture=compute_52 --use_fast_math --relocatable-device-code=true -I"C:\ProgramData\NVIDIA Corporation\OptiX SDK 7.4.0\include" -I"C:\ProgramData\NVIDIA Corporation\OptiX SDK 7.4.0\SDK" -I"C:\ProgramData\NVIDIA Corporation\OptiX SDK 7.4.0\SDK\cuda" -I"D:\Study\Alalba\Alalba\src\Alalba\Optix" -I"D:\Study\Alalba\Alalba\vendor\gdt\source\math" -I"D:\Study\Alalba\Alalba\vendor\gdt\source" -I"D:\Study\Alalba\Alalba\src" -o assets\deviceCode.ptx')
os.execute('nvcc assets\\deviceCode.cu -ptx -ccbin "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.30.30705\\bin\\Hostx64\\x64" --gpu-architecture=compute_52 --use_fast_math --relocatable-device-code=true -I"C:\\ProgramData\\NVIDIA Corporation\\OptiX SDK 7.4.0\\include" -I"C:\\ProgramData\\NVIDIA Corporation\\OptiX SDK 7.4.0\\SDK" -I"C:\\ProgramData\\NVIDIA Corporation\\OptiX SDK 7.4.0\\SDK\\cuda" -I"D:\\Study\\Alalba\\Alalba\\src\\Alalba\\Optix" -I"D:\\Study\\Alalba\\Alalba\\vendor\\gdt\\source\\math" -I"D:\\Study\\Alalba\\Alalba\\vendor\\gdt\\source" -I"D:\\Study\\Alalba\\Alalba\\src" -o assets\\deviceCode.ptx')
--os.execute('nvcc --version')
dofile("../optix.lua")