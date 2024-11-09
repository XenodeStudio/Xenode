project "Xen"

	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. bin_folder .. "/bin/%{prj.name}")
	objdir ("%{wks.location}/bin/" .. bin_folder .. "/obj/%{prj.name}")

	files {
		"src/**.cpp",
		"src/**.h",

		--ImGuizmo source files
		"../../deps/ImGuizmo/*.cpp",
		"../../deps/ImGuizmo/*.h"
	}

	includedirs {
		"%{wks.location}/core/Xenode/src/",
		"%{wks.location}/core/Xen/src",

		"%{IncludeDir.spdlog}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.yaml_cpp}",
		"%{IncludeDir.ImGuizmo}",
		"%{IncludeDir.ImGradientHDR}",

	}

	links { "Xenode", "yaml-cpp", "GLFW", "ImGui", "Box2D", "Lua" }

	pic "on"

	postbuildcommands {
		"{COPYFILE} %{wks.location}/bin/" .. bin_folder .. "/bin/yaml-cpp/yaml-cpp.dll %{wks.location}/bin/" .. bin_folder .. "/bin/%{prj.name}"
	}

	defines {
		"EDITOR_RESOURCES=\"%{EDITOR_RESOURCES_PATH}\"",
		"PROJECTS=\"%{PROJECTS_PATH}\""
	}

	filter "files:deps/ImGuizmo/*.cpp"
		flags { "NoPCH" }

	filter "system:windows"

		systemversion "latest"

		includedirs {
			"%{wks.location}/Xenode/src/platform/windows",
			"%{wks.location}/Xenode/src"
		}

		defines { "XEN_PLATFORM_WINDOWS", "XEN_BUILD_EXE", "XEN_DEVICE_DESKTOP" }

	filter "system:linux"

		systemversion "latest"

		includedirs {
			"%{wks.location}/Xenode/src/platform/linux",
			"%{wks.location}/Xenode/src"
		}

		defines { "XEN_PLATFORM_LINUX", "XEN_BUILD_EXE", "XEN_DEVICE_DESKTOP" }

	filter "configurations:Debug"
        defines {"XEN_DEBUG", "XEN_LOG_ON"}
        symbols "On"
		-- buildoptions "/MTd"

    filter "configurations:Release_Debug"
        defines {"XEN_RELEASE", "XEN_LOG_ON"}
        optimize "On"
		-- buildoptions "/MT"

    filter "configurations:Production"
		kind "WindowedApp"
        defines {"XEN_PRODUCTION", "XEN_LOG_OFF"}
        optimize "On"

	filter "action:vs*"
		buildoptions "/std:c++latest"
		flags { "MultiProcessorCompile" }

		-- Disable warnings that I don't care:
		disablewarnings {
			"4244", -- conversion from 'type1' to 'type2'
			"4267", -- conversion from 'size_t' to other numeric data type
			"4018", -- Signed/Unsigned mismatch
			"4146", -- Unary minus operator applied to unsigned type: the number will still remain unsigned and show weird results 
			"4858", -- Some C++20 Deprication warning (remove and remove_if) 
			"4312", -- type cast to greater size
		}

		defines {" _SILENCE_ALL_CXX23_DEPRECATION_WARNINGS" }

	filter "action:gmake*"
		links { "pthread" }
		buildoptions{ "-std=c++2b", "-Wa,-mbig-obj" }

	filter { "action:gmake*", "system:windows" }
		links { "gdi32", "comdlg32" }

	filter { "system:windows", "configurations:Debug" }
		links {
			"%{Library.ShaderC_Debug}",
			"%{Library.SpirVCrossCore_Debug}",
			"%{Library.SpirVCrossGLSL_Debug}"
		}
	filter { "system:windows", "configurations:Release_Debug" }
		links {
			"%{Library.ShaderC_Release}",
			"%{Library.SpirVCrossCore_Release}",
			"%{Library.SpirVCrossGLSL_Release}"
		}
	filter { "system:windows", "configurations:Production" }
		links {
			"%{Library.ShaderC_Release}",
			"%{Library.SpirVCrossCore_Release}",
			"%{Library.SpirVCrossGLSL_Release}",
		}

