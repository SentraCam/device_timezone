# device_timezone

A flutter plugin for getting the local timezone of the OS.

This is an updated version of the [flutter_timezone](https://pub.dev/packages/flutter_timezone) project to include Windows support.

## Getting Started

### Get the timezone

```dart
final String? currentTimeZone = await DeviceTimezone.getLocalTimezone();
```

### Get all available timezones

```dart
final List<String> availableTimezones = await DeviceTimezone.getAvailableTimezones();
```
### Windows

Update [Visual Studio](https://visualstudio.microsoft.com) to the latest version for using `C++ 20`.

> **💡 If you can't compile**
> 
> Try downloading a latest Windows SDK:
> 1. Open Visual Studio Installer
> 2. Select Modify
> 3. Select Windows SDK
