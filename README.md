# device_timezone

A flutter plugin for getting the local timezone of the OS.

This is an updated version of the [flutter_timezone](https://pub.dev/packages/flutter_timezone) project.

## Getting Started

### Get the timezone

```dart
final String? currentTimeZone = await DeviceTimezone.getLocalTimezone();
```
