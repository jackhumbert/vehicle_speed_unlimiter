#include "Utils/Utils.hpp"
#include "Utils/ModModule.hpp"
#include "Engine/RTTIRegistrar.hpp"
#include "stdafx.hpp"
#include <RED4ext/Api/Sdk.hpp>
#include <RED4ext/InstanceType.hpp>
#include <RED4ext/Common.hpp>
#include <RED4ext/RTTITypes.hpp>
#include <RED4ext/Version.hpp>
#include <RedLib.hpp>
#include <iostream>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <libloaderapi.h>
#include <string>
#include <winbase.h>

RED4EXT_C_EXPORT void RED4EXT_CALL RegisterTypes() {
  spdlog::info("Registering classes & types");
  ModModuleFactory::GetInstance().RegisterTypes();
}

RED4EXT_C_EXPORT void RED4EXT_CALL PostRegisterTypes() {
  spdlog::info("Registering functions");
  ModModuleFactory::GetInstance().PostRegisterTypes();
}

bool loaded = false;
RED4ext::PluginHandle pluginHandle;

RED4EXT_C_EXPORT bool RED4EXT_CALL Main(RED4ext::PluginHandle aHandle, RED4ext::EMainReason aReason,
                                        const RED4ext::Sdk *aSdk) {
  switch (aReason) {
  case RED4ext::EMainReason::Load: {
    pluginHandle = aHandle;

    Utils::CreateLogger();
    spdlog::info("Starting up Vehicle Speed Unlimiter {}", MOD_VERSION_STR);
    auto ptr = GetModuleHandle(nullptr);
    spdlog::info("Base address: {}", fmt::ptr(ptr));
    auto modPtr = aHandle;
    spdlog::info("Mod address: {}", fmt::ptr(modPtr));

    RED4ext::RTTIRegistrator::Add(RegisterTypes, PostRegisterTypes);
    Engine::RTTIRegistrar::RegisterPending();
    Red::TypeInfoRegistrar::RegisterDiscovered();

    ModModuleFactory::GetInstance().Load(aSdk, aHandle);

    loaded = true;

    break;
  }
  case RED4ext::EMainReason::Unload: {
    // Free memory, detach hooks.
    // The game's memory is already freed, to not try to do anything with it.
    spdlog::info("Shutting down");
    if (loaded) {
      ModModuleFactory::GetInstance().Unload(aSdk, aHandle);
    }
    spdlog::shutdown();
    break;
  }
  }

  return true;
}

RED4EXT_C_EXPORT void RED4EXT_CALL Query(RED4ext::PluginInfo *aInfo) {
  aInfo->name = L"Vehicle Speed Unlimiter";
  aInfo->author = L"Jack Humbert";
  aInfo->version = RED4EXT_SEMVER(MOD_VERSION_MAJOR, MOD_VERSION_MINOR, MOD_VERSION_PATCH);
  aInfo->runtime = RED4EXT_RUNTIME_INDEPENDENT;
  aInfo->sdk = RED4EXT_SDK_LATEST;
}

RED4EXT_C_EXPORT uint32_t RED4EXT_CALL Supports() { return RED4EXT_API_VERSION_LATEST; }
