#ifndef FLUTTER_PLUGIN_DEVICE_TIMEZONE_PLUGIN_H_
#define FLUTTER_PLUGIN_DEVICE_TIMEZONE_PLUGIN_H_

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>
#include <string>

#include <memory>

namespace device_timezone {

class DeviceTimezonePlugin : public flutter::Plugin {
 public:
  static void RegisterWithRegistrar(flutter::PluginRegistrarWindows *registrar);

  DeviceTimezonePlugin();

  virtual ~DeviceTimezonePlugin();

  // Disallow copy and assign.
  DeviceTimezonePlugin(const DeviceTimezonePlugin&) = delete;
  DeviceTimezonePlugin& operator=(const DeviceTimezonePlugin&) = delete;

  // Called when a method is called on this plugin's channel from Dart.
  void HandleMethodCall(
      const flutter::MethodCall<flutter::EncodableValue> &method_call,
      std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);

  std::string GetLocalTimezone();

    std::string WcharToString(wchar_t* wc);

};

}  // namespace device_timezone

#endif  // FLUTTER_PLUGIN_DEVICE_TIMEZONE_PLUGIN_H_
