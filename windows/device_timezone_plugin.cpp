#include "device_timezone_plugin.h"

// This must be included before many other Windows headers.
#include <windows.h>
#include <chrono>
#include <string>
#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>
#include <flutter/standard_method_codec.h>

#include <memory>
#include <sstream>

namespace device_timezone {

	// static
	void DeviceTimezonePlugin::RegisterWithRegistrar(
		flutter::PluginRegistrarWindows* registrar) {
		auto channel =
			std::make_unique<flutter::MethodChannel<flutter::EncodableValue>>(
				registrar->messenger(), "device_timezone",
				&flutter::StandardMethodCodec::GetInstance());

		auto plugin = std::make_unique<DeviceTimezonePlugin>();

		channel->SetMethodCallHandler(
			[plugin_pointer = plugin.get()](const auto& call, auto result) {
				plugin_pointer->HandleMethodCall(call, std::move(result));
			});

		registrar->AddPlugin(std::move(plugin));
	}

	DeviceTimezonePlugin::DeviceTimezonePlugin() {}

	DeviceTimezonePlugin::~DeviceTimezonePlugin() {}

	void DeviceTimezonePlugin::HandleMethodCall(
		const flutter::MethodCall<flutter::EncodableValue>& method_call,
		std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
		if (method_call.method_name().compare("getLocalTimezone") == 0) {

			std::string identifier = GetLocalTimezone();
			if (identifier.compare("") == 0) {
				result->Error("UNAVAILABLE", "Timezone not available.");
        return;
			}
			result->Success(flutter::EncodableValue(identifier));
		}
    else if (method_call.method_name().compare("getAvailableTimezones") == 0) {
      std::string identifier = GetLocalTimezone();
			if (identifier.compare("") == 0) {
				result->Error("UNAVAILABLE", "Timezone not available.");
        return;
			}
    flutter::EncodableList timeZones;

      timeZones.push_back(flutter::EncodableValue(identifier));

      result->Success(flutter::EncodableValue(timeZones));

    }
		else {
			result->NotImplemented();
		}
	}

  std::string DeviceTimezonePlugin::GetLocalTimezone() {

    const std::chrono::time_zone* current_z = std::chrono::current_zone();
    return std::string{current_z->name()};
   
  }

}  // namespace device_timezone
