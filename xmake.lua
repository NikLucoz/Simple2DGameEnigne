set_project("SFMLGameEngine")

-- Enable standard build modes (debug, release, releasedbg, etc.)
add_rules("mode.debug", "mode.release", "mode.releasedbg")

-- Set C++ standard
set_languages("cxx17")

-- Dependencies managed automatically by Xmake
add_requires("sfml >=3.0.0", "imgui-sfml")

target("game_engine")
set_kind("binary")

-- Output directory equivalent to CMAKE_BINARY_DIR/bin
set_targetdir("build/bin")
set_rundir("build/bin")

-- Source files
add_files("src/main.cpp")
add_files("src/**/*.cpp")

-- Include directories
add_includedirs("src", {public = true})

-- Link required packages
add_packages("sfml", "imgui-sfml")

-- Copy assets post-build
-- Copy assets post-build
after_build(function (target)
    local src_assets = path.join(target:scriptdir(), "src/assets/*")
    local dst_assets = path.join(target:targetdir(), "assets/")
    os.cp(src_assets, dst_assets)
end)