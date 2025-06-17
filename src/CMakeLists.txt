include(Red4ext)

target_link_libraries(vehicle_speed_unlimiter.dll
  PUBLIC
    Detours
    RED4ext.SDK
    RedLib
    spdlog
)