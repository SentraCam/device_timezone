import 'package:flutter_test/flutter_test.dart';
import 'package:device_timezone/device_timezone.dart';
import 'package:device_timezone/device_timezone_platform_interface.dart';
import 'package:device_timezone/device_timezone_method_channel.dart';

void main() {
  final DeviceTimezonePlatform initialPlatform =
      DeviceTimezonePlatform.instance;

  test('$MethodChannelDeviceTimezone is the default instance', () {
    expect(initialPlatform, isInstanceOf<MethodChannelDeviceTimezone>());
  });

  test('getLocalTimezone', () async {
    expect(await DeviceTimezone.getLocalTimezone(), '42');
  });
}
