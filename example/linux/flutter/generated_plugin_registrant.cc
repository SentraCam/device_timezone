//
//  Generated file. Do not edit.
//

// clang-format off

#include "generated_plugin_registrant.h"

#include <device_timezone/device_timezone_plugin.h>

void fl_register_plugins(FlPluginRegistry* registry) {
  g_autoptr(FlPluginRegistrar) device_timezone_registrar =
      fl_plugin_registry_get_registrar_for_plugin(registry, "DeviceTimezonePlugin");
  device_timezone_plugin_register_with_registrar(device_timezone_registrar);
}
