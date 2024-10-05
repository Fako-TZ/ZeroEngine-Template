-- premake5.lua
workspace "ZeroEngineApp"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "ZeroEngineApp"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "ZeroEngineExternal.lua"
include "ZeroEngineApp"