#include "include/device_timezone/device_timezone_plugin_c_api.h"

#include <flutter/plugin_registrar_windows.h>

#include "device_timezone_plugin.h"

void DeviceTimezonePluginCApiRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  device_timezone::DeviceTimezonePlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarManager::GetInstance()
          ->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}
