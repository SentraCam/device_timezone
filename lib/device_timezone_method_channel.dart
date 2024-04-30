import 'package:flutter/foundation.dart';
import 'package:flutter/services.dart';

import 'device_timezone_platform_interface.dart';

/// An implementation of [DeviceTimezonePlatform] that uses method channels.
class MethodChannelDeviceTimezone extends DeviceTimezonePlatform {
  /// The method channel used to interact with the native platform.
  @visibleForTesting
  final methodChannel = const MethodChannel('device_timezone');

  @override
  Future<String?> getLocalTimezone() async {
    final String? localTimezone =
        await methodChannel.invokeMethod("getLocalTimezone");
    if (localTimezone == null) {
      throw ArgumentError("Invalid return from platform getLocalTimezone()");
    }
    return localTimezone;
  }

  @override
  Future<List<String>> getAvailableTimezones() async {
    final List<String>? availableTimezones =
        await methodChannel.invokeListMethod<String>("getAvailableTimezones");
    if (availableTimezones == null) {
      throw ArgumentError(
          "Invalid return from platform getAvailableTimezones()");
    }
    return availableTimezones;
  }
}
