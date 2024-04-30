#include "device_timezone_plugin.h"

// This must be included before many other Windows headers.
#include <windows.h>

#include <timezoneapi.h>
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

			TIME_ZONE_INFORMATION timeZoneInfo;
			DWORD zoneInfoResult = GetTimeZoneInformation(&timeZoneInfo);

			if (zoneInfoResult == TIME_ZONE_ID_INVALID) {
				result->NotImplemented();
        return;
			}

			// Identify Time Zone based on return value
			std::string identifier;
			switch (zoneInfoResult) {
			case TIME_ZONE_ID_UNKNOWN:
				identifier = "Unknown";
				break;
			case TIME_ZONE_ID_STANDARD:
				identifier = WcharToString(timeZoneInfo.StandardName);
				break;
			case TIME_ZONE_ID_DAYLIGHT:
				identifier = WcharToString(timeZoneInfo.DaylightName);
				break;
			}
			result->Success(flutter::EncodableValue(identifier));
		}
		else {
			result->NotImplemented();
		}
	}

	std::string DeviceTimezonePlugin::WcharToString(wchar_t* wc) {
    std::wstring wstr(wc);
    if ( wstr.length() > INT_MAX )
      {
        throw std::overflow_error("data is larger than INT_MAX");
      }
    int count = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), static_cast<int>(wstr.length()), NULL, 0, NULL, NULL);
    std::string str(count, 0);
    WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, &str[0], count, NULL, NULL);
    return str;
	}

}  // namespace device_timezone
