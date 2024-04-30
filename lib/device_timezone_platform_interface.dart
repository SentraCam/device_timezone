import 'package:plugin_platform_interface/plugin_platform_interface.dart';

import 'device_timezone_method_channel.dart';

abstract class DeviceTimezonePlatform extends PlatformInterface {
  /// Constructs a DeviceTimezonePlatform.
  DeviceTimezonePlatform() : super(token: _token);

  static final Object _token = Object();

  static DeviceTimezonePlatform _instance = MethodChannelDeviceTimezone();

  /// The default instance of [DeviceTimezonePlatform] to use.
  ///
  /// Defaults to [MethodChannelDeviceTimezone].
  static DeviceTimezonePlatform get instance => _instance;

  /// Platform-specific implementations should set this with their own
  /// platform-specific class that extends [DeviceTimezonePlatform] when
  /// they register themselves.
  static set instance(DeviceTimezonePlatform instance) {
    PlatformInterface.verifyToken(instance, _token);
    _instance = instance;
  }

  ///
  /// Returns local timezone from the native layer.
  ///
  Future<String?> getLocalTimezone() {
    throw UnimplementedError('getLocalTimezone() has not been implemented.');
  }

  ///
  /// Gets the list of available timezones from the native layer.
  ///
  Future<List<String>> getAvailableTimezones() async {
    throw UnimplementedError(
        'getAvailableTimezones() has not been implemented.');
  }
}
