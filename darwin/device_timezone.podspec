#
# To learn more about a Podspec see http://guides.cocoapods.org/syntax/podspec.html.
# Run `pod lib lint device_timezone.podspec` to validate before publishing.
#
Pod::Spec.new do |s|
  s.name             = 'device_timezone'
  s.version          = '0.0.1'
  s.summary          = 'A native timezone project.'
  s.description      = <<-DESC
  A native timezone project.
                       DESC
  s.homepage         = 'https://sentracam.com'
  s.license          = { :file => '../LICENSE' }
  s.author           = { 'SentraCam' => 'rob.leckie@sentracam.com' }
  s.source           = { :path => '.' }
  s.source_files = 'Classes/**/*'
  s.ios.dependency 'Flutter'
  s.osx.dependency 'FlutterMacOS'
  s.ios.deployment_target = '11.0'
  s.osx.deployment_target = '10.14'

  # Flutter.framework does not contain a i386 slice.
  s.pod_target_xcconfig = { 'DEFINES_MODULE' => 'YES', 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'i386' }
  s.swift_version = '5.0'
end
