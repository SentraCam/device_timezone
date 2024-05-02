#include "include/device_timezone/device_timezone_plugin.h"

#include <flutter_linux/flutter_linux.h>
#include <gtk/gtk.h>
#include <sys/utsname.h>

#include <cstring>
#include <chrono>

#include "device_timezone_plugin_private.h"

#define DEVICE_TIMEZONE_PLUGIN(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), device_timezone_plugin_get_type(), \
                              DeviceTimezonePlugin))

struct _DeviceTimezonePlugin {
  GObject parent_instance;
};

G_DEFINE_TYPE(DeviceTimezonePlugin, device_timezone_plugin, g_object_get_type())

// Called when a method call is received from Flutter.
static void device_timezone_plugin_handle_method_call(
    DeviceTimezonePlugin* self,
    FlMethodCall* method_call) {
  g_autoptr(FlMethodResponse) response = nullptr;

  const gchar* method = fl_method_call_get_name(method_call);

  if (strcmp(method, "getLocalTimezone") == 0) {
    response = get_local_timezone();
  } 
  else if (strcmp(method, "getAvailableTimezones") == 0) {
    response = get_available_timezones();
  } 
  else {
    response = FL_METHOD_RESPONSE(fl_method_not_implemented_response_new());
  }

  fl_method_call_respond(method_call, response, nullptr);
}

FlMethodResponse* get_local_timezone() {
  const std::chrono::time_zone* current_z = std::chrono::current_zone();
  if (current_z == nullptr) {
    return FL_METHOD_RESPONSE(fl_method_error_response_new("UNAVAILABLE",
                                                           "Timezone not available."));
  }
  g_autoptr(FlValue) result = fl_value_new_string(current_z->name());
  return FL_METHOD_RESPONSE(fl_method_success_response_new(result));
}

FlMethodResponse* get_available_timezones() {
  g_autoptr(FlValue) result = fl_value_new_list();

  for (auto& tz : std::chrono::get_tzdb().zones){
      fl_value_append_take(result, fl_value_new_string(tz.name().c_str()));
  }
  return FL_METHOD_RESPONSE(fl_method_success_response_new(result));
}

static void device_timezone_plugin_dispose(GObject* object) {
  G_OBJECT_CLASS(device_timezone_plugin_parent_class)->dispose(object);
}

static void device_timezone_plugin_class_init(DeviceTimezonePluginClass* klass) {
  G_OBJECT_CLASS(klass)->dispose = device_timezone_plugin_dispose;
}

static void device_timezone_plugin_init(DeviceTimezonePlugin* self) {}

static void method_call_cb(FlMethodChannel* channel, FlMethodCall* method_call,
                           gpointer user_data) {
  DeviceTimezonePlugin* plugin = DEVICE_TIMEZONE_PLUGIN(user_data);
  device_timezone_plugin_handle_method_call(plugin, method_call);
}

void device_timezone_plugin_register_with_registrar(FlPluginRegistrar* registrar) {
  DeviceTimezonePlugin* plugin = DEVICE_TIMEZONE_PLUGIN(
      g_object_new(device_timezone_plugin_get_type(), nullptr));

  g_autoptr(FlStandardMethodCodec) codec = fl_standard_method_codec_new();
  g_autoptr(FlMethodChannel) channel =
      fl_method_channel_new(fl_plugin_registrar_get_messenger(registrar),
                            "device_timezone",
                            FL_METHOD_CODEC(codec));
  fl_method_channel_set_method_call_handler(channel, method_call_cb,
                                            g_object_ref(plugin),
                                            g_object_unref);

  g_object_unref(plugin);
}
