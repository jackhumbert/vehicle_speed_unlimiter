cmake_minimum_required(VERSION 3.24)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/deps/cyberpunk_cmake")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/deps/red4ext.sdk/cmake")

include(ConfigureVersionFromGit)
configure_version_from_git()

project(vehicle_speed_unlimiter VERSION ${GIT_VERSION_MAJOR}.${GIT_VERSION_MINOR}.${GIT_VERSION_PATCH} LANGUAGES NONE)

include(CyberpunkMod)

configure_mod(
  NAME "Vehicle Speed Unlimitetr"
  SLUG ${PROJECT_NAME}
  PREFIX VSU
  AUTHOR "Jack Humbert"
  URL "https://github.com/jackhumbert/vehicle_speed_unlimiter"
  LICENSE "Licensed under the MIT license. See the license.md in the root project for details."
)

find_program(ZOLTAN_CLANG_EXE NAMES zoltan-clang.exe PATHS "${MOD_TOOLS_DIR}" CACHE)
find_program(REDSCRIPT_CLI_EXE NAMES redscript-cli.exe PATHS "${MOD_TOOLS_DIR}" CACHE)
find_program(CYBERPUNK_2077_EXE NAMES Cyberpunk2077.exe PATHS "${CYBERPUNK_2077_GAME_DIR}/bin/x64" CACHE DOC "Cyberpunk2077.exe Executable File")

set(ZOLTAN_CLANG_EXE "C:/Users/Jack/Documents/cyberpunk/zoltan/target/release/zoltan-clang.exe")

configure_red4ext(src)

find_package(Detours)
find_package(Spdlog)
find_package(RedLib)
# find_package(ModSettings)

target_link_libraries(vehicle_speed_unlimiter.dll
  PUBLIC
    Detours
    spdlog
    RedLib
)

configure_folder_file(readme.md)
configure_folder_file(license.md)

# list(APPEND MOD_REQUIREMENTS "Mod Settings v0.2.8+ (optional)")

# configure_uninstall()
configure_release(${MOD_SLUG}_${MOD_VERSION_STR}.zip)
configure_install()