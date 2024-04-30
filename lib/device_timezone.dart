import 'device_timezone_platform_interface.dart';

///
/// Class for getting the native timezone.
///
class DeviceTimezone {
  ///
  /// Returns local timezone from the native layer.
  ///
  static Future<String?> getLocalTimezone() {
    return DeviceTimezonePlatform.instance.getLocalTimezone();
  }

  ///
  /// Gets the list of available timezones from the native layer.
  ///
  static Future<List<String>> getAvailableTimezones() {
    return DeviceTimezonePlatform.instance.getAvailableTimezones();
  }
}
