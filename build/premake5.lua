-- premake5.lua
workspace "Renderer"
   configurations { "Debug", "Release" }

project "Renderer"
   kind "WindowedApp"
   language "C++"
   targetdir "../bin/%{cfg.buildcfg}"
   objdir "../obj"

   files { "../src/*.hpp", "../src/*.cpp" }
   libdirs { "../lib" }
   includedirs { "../include" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      links { "sfml-graphics-d", "sfml-window-d", "sfml-system-d" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      links { "sfml-graphics", "sfml-window", "sfml-system" }
      optimize "On"
