import 'package:flutter/services.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:device_timezone/device_timezone_method_channel.dart';

void main() {
  TestWidgetsFlutterBinding.ensureInitialized();

  MethodChannelDeviceTimezone platform = MethodChannelDeviceTimezone();
  const MethodChannel channel = MethodChannel('device_timezone');

  setUp(() {
    TestDefaultBinaryMessengerBinding.instance.defaultBinaryMessenger
        .setMockMethodCallHandler(
      channel,
      (MethodCall methodCall) async {
        return '42';
      },
    );
  });

  tearDown(() {
    TestDefaultBinaryMessengerBinding.instance.defaultBinaryMessenger
        .setMockMethodCallHandler(channel, null);
  });

  test('getLocalTimezone', () async {
    expect(await platform.getLocalTimezone(), '42');
  });
}
