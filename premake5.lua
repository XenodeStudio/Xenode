workspace "Xenode"
	configurations { "Debug", "Release_Debug", "Production" }
	architecture "x64"

	bin_folder = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	startproject "SandboxApp"
-- dependencies:

--VULKAN_SDK_ROOT = "C:/VulkanSDK/1.3.216.0"

include "Xenode/deps/glfw"
include "Xenode/deps/imgui"

IncludeDir = {}
IncludeDir["spdlog"] = "%{wks.location}/Xenode/deps/spdlog/include"
IncludeDir["GLFW"] = "%{wks.location}/Xenode/deps/glfw/include"
IncludeDir["glad"] = "%{wks.location}/Xenode/deps/glad/include"
IncludeDir["glm"] = "%{wks.location}/Xenode/deps/glm/include"
IncludeDir["stb"] = "%{wks.location}/Xenode/deps/stb"
IncludeDir["ImGui"] = "%{wks.location}/Xenode/deps/imgui"
--IncludeDir["VulkanSDK"] = "%{VULKAN_SDK_ROOT}/Include"

-- Main projects:

include "Xenode/"
include "SandboxApp/"
