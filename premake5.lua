-- premake5.lua
workspace "DiscordActivityGui"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "DiscordActivityGui"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
include "Walnut/WalnutExternal.lua"

include "DiscordActivityGui"