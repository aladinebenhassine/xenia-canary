include("tools/build")
require("third_party/premake-export-compile-commands/export-compile-commands")
require("third_party/premake-androidndk/androidndk")
require("third_party/premake-cmake/cmake")

location(build_root)
targetdir(build_bin)
objdir(build_obj)

if os.istarget("linux") then
  ARCH = os.outputof("uname -p")
elseif os.istarget("macosx") then
  ARCH = os.outputof("uname -m")
else
  ARCH = "unknown"
end

includedirs({
  ".",
  "src",
  "third_party",
  "third_party/FFmpeg", -- Include FFmpeg directory
})

defines({
  "_UNICODE",
  "UNICODE",
})

cppdialect("C++17")
exceptionhandling("On")
rtti("On")
symbols("On")

characterset("Unicode")
flags({
  "FatalWarnings",
})

-- Apply -mavx only to x86_64 architecture and only to C++ files
if ARCH == "x86_64" then
  filter("architecture:x86_64")
    filter("files:**.cpp or **.cc or **.cxx")
      buildoptions({
        "-mavx",
      })
    filter({})
end

filter("kind:StaticLib")
  defines({
    "_LIB",
  })

filter("configurations:Checked")
  runtime("Debug")
  optimize("Off")
  defines({
    "DEBUG",
  })
filter({"configurations:Checked", "platforms:Windows"})
  buildoptions({
    "/RTCsu",
  })
filter({"configurations:Checked", "platforms:Linux"})
  defines({
    "_GLIBCXX_DEBUG",
  })
filter({"configurations:Release", "platforms:Windows"})
  buildoptions({
    "/Gw",
    "/GS-",
    "/Oy"
  })

filter("configurations:Debug")
  runtime("Release")
  optimize("Off")
  defines({
    "DEBUG",
    "_NO_DEBUG_HEAP=1",
  })
filter({"configurations:Debug", "platforms:Linux"})
  defines({
    "_GLIBCXX_DEBUG",
  })

filter("configurations:Release")
  runtime("Release")
  defines({
    "NDEBUG",
    "_NO_DEBUG_HEAP=1",
  })
  optimize("Speed")
  inlining("Auto")
  flags({
    "LinkTimeOptimization",
  })

filter("platforms:Linux")
  system("linux")
  toolset("clang")
  buildoptions({
  })
  pkg_config.all("gtk+-x11-3.0")
  links({
    "stdc++fs",
    "dl",
    "lz4",
    "pthread",
    "rt",
  })

filter({"platforms:Linux", "kind:*App"})
  linkgroups("On")

filter({"platforms:Linux", "language:C++", "toolset:gcc"})
  disablewarnings({
    "unused-result"
  })

filter({"platforms:Linux", "toolset:gcc"})
  if ARCH == "ppc64" then
    buildoptions({
      "-m32",
      "-mpowerpc64"
    })
    linkoptions({
      "-m32",
      "-mpowerpc64"
    })
  end

filter({"platforms:Linux", "language:C++", "toolset:clang"})
  disablewarnings({
    "deprecated-register"
  })
filter({"platforms:Linux", "language:C++", "toolset:clang", "files:*.cc or *.cpp"})
  buildoptions({
    "-stdlib=libstdc++",
  })

filter("platforms:Android-*")
  system("android")
  systemversion("24")
  cppstl("c++")
  staticruntime("On")
  visibility("Hidden")
  links({
    "android",
    "dl",
    "log",
  })

filter("platforms:Windows")
  system("windows")
  toolset("msc")
  buildoptions({
    "/utf-8",
    "/w14839",
    "/w14840",
    "/wd4100",
    "/wd4201",
    "/wd4512",
    "/wd4127",
    "/wd4324",
    "/wd4189",
  })
  flags({
    "MultiProcessorCompile",
    "NoMinimalRebuild",
  })

  defines({
    "_CRT_NONSTDC_NO_DEPRECATE",
    "_CRT_SECURE_NO_WARNINGS",
    "WIN32",
    "_WIN64=1",
    "_AMD64=1",
  })
  linkoptions({
    "/ignore:4006",
    "/ignore:4221",
  })
  links({
    "ntdll",
    "wsock32",
    "ws2_32",
    "xinput",
    "comctl32",
    "shcore",
    "shlwapi",
    "dxguid",
    "bcrypt",
  })

filter({"platforms:Windows", "kind:ConsoleApp or WindowedApp"})
  files({
    "src/xenia/base/app_win32.manifest"
  })

filter("platforms:Mac")
  system("macosx")
  toolset("clang")
  filter("files:**.cpp or **.cc or **.cxx")
    buildoptions({
      "-std=c++17",
      "-stdlib=libc++",
      "-mmacosx-version-min=10.15"
    })
    linkoptions({
      "-stdlib=libc++",
    })
  filter({})
  links({
    "MoltenVK",
    "Cocoa",
    "IOKit",
    "CoreVideo",
    "Metal",
    "Foundation"
  })
  xcodebuildsettings({
    ["MACOSX_DEPLOYMENT_TARGET"] = "10.15",
    ["ARCHS"] = "arm64"
  })

if not os.isdir("scratch") then
  os.mkdir("scratch")
end

workspace("xenia")
  uuid("931ef4b0-6170-4f7a-aaf2-0fece7632747")
  startproject("xenia-app")
  if os.istarget("android") then
    platforms({"Android-ARM64", "Android-x86_64"})
    filter("platforms:Android-ARM64")
      architecture("ARM64")
    filter("platforms:Android-x86_64")
      architecture("x86_64")
    filter({})
  else
    architecture("x86_64")
    if os.istarget("linux") then
      platforms({"Linux"})
    elseif os.istarget("macosx") then
      platforms({"Mac"})
    elseif os.istarget("windows") then
      platforms({"Windows"})
      filter("action:vs2017")
        systemversion("10.0.22000.0")
      filter("action:vs2019")
        systemversion("10.0")
      filter({})
    end
  end
  configurations({"Checked", "Debug", "Release"})

  include("third_party/aes_128.lua")
  include("third_party/capstone.lua")
  include("third_party/dxbc.lua")
  include("third_party/discord-rpc.lua")
  include("third_party/cxxopts.lua")
  include("third_party/cpptoml.lua")
  include("third_party/FFmpeg/premake5.lua")
  include("third_party/fmt.lua")
  include("third_party/glslang-spirv.lua")
  include("third_party/imgui.lua")
  include("third_party/mspack.lua")
  include("third_party/snappy.lua")
  include("third_party/xxhash.lua")
  include("third_party/zarchive.lua")
  include("third_party/zstd.lua")

  if not os.istarget("android") then
    include("third_party/SDL2.lua")
  end

  for _, prj in ipairs(premake.api.scope.current.solution.projects) do
    project(prj.name)
    removefiles({
      "src/xenia/base/app_win32.manifest"
    })
    removeflags({
      "FatalWarnings",
    })
  end

  include("src/xenia")
  include("src/xenia/app")
  include("src/xenia/app/discord")
  include("src/xenia/apu")
  include("src/xenia/apu/nop")
  include("src/xenia/apu/coreaudio")
  include("src/xenia/base")
  include("src/xenia/cpu")
  include("src/xenia/cpu/backend/x64")
  include("src/xenia/debug/ui")
  include("src/xenia/gpu")
  include("src/xenia/gpu/null")
  include("src/xenia/gpu/vulkan")
  include("src/xenia/hid")
  include("src/xenia/hid/nop")
  include("src/xenia/kernel")
  include("src/xenia/patcher")
  include("src/xenia/ui")
  include("src/xenia/ui/vulkan")
  include("src/xenia/ui/metal")
  include("src/xenia/vfs")

  if not os.istarget("android") then
    include("src/xenia/apu/sdl")
    include("src/xenia/helper/sdl")
    include("src/xenia/hid/sdl")
  end

  if os.istarget("windows") then
    include("src/xenia/apu/xaudio2")
    include("src/xenia/gpu/d3d12")
    include("src/xenia/hid/winkey")
    include("src/xenia/hid/xinput")
    include("src/xenia/ui/d3d12")
  end
