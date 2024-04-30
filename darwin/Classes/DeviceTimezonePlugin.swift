#if os(OSX)
  import FlutterMacOS
  import Cocoa
#else
  import Flutter
  import UIKit
#endif

public class DeviceTimezonePlugin: NSObject, FlutterPlugin {
  public static func register(with registrar: FlutterPluginRegistrar) {
    var channel: FlutterMethodChannel
    #if os(OSX)
      channel = FlutterMethodChannel(
        name: "device_timezone", binaryMessenger: registrar.messenger)
    #else
      channel = FlutterMethodChannel(
        name: "device_timezone", binaryMessenger: registrar.messenger())

    #endif

    let instance = DeviceTimezonePlugin()
    registrar.addMethodCallDelegate(instance, channel: channel)
  }

  public func handle(_ call: FlutterMethodCall, result: @escaping FlutterResult) {
    switch call.method {
    case "getLocalTimezone":
      result(NSTimeZone.local.identifier)
    case "getAvailableTimezones":
      result(NSTimeZone.knownTimeZoneNames)
    default:
      result(FlutterMethodNotImplemented)
    }
  }
}
