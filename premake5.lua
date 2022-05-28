-- premake5.lua
workspace "GeoSimuli"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "GeoSimuli"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
include "Walnut/WalnutExternal.lua"

include "GeoSimuli"