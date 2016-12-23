#include <nan.h>
#include <libtorrent/version.hpp>
#include <libtorrent-rasterbar/alert.h>
#include <libtorrent-rasterbar/extensions.h>
#include <libtorrent-rasterbar/session.h>
#include <libtorrent-rasterbar/settings.h>
#include <libtorrent-rasterbar/settings_pack.h>
#include <libtorrent-rasterbar/macros.h>

namespace libtorrent_rasterbar {

NAN_MODULE_INIT(InitAlerts) {
  v8::Local<v8::Object> alerts = Nan::New<v8::Object>();
  SET_VALUE(alerts, "Alert", Alert::Init());
  SET_VALUE(target, "alerts", alerts);
}

NAN_MODULE_INIT(InitExtensions) {
#ifndef TORRENT_DISABLE_EXTENSIONS
  v8::Local<v8::Object> extensions = Nan::New<v8::Object>();
  SET_STRING(extensions, "SmartBan", "smart_ban");
  SET_STRING(extensions, "UTMetadata", "ut_metadata");
  SET_STRING(extensions, "UTPex", "ut_pex");
  SET_VALUE(extensions, "Plugin", Plugin::Init());
  SET_VALUE(target, "extensions", extensions);
#endif // TORRENT_DISABLE_EXTENSIONS
}

NAN_MODULE_INIT(InitSettings) {
  v8::Local<v8::Object> settings = Nan::New<v8::Object>();
  SET_VALUE(settings, "SettingsPack", SettingsPack::Init());
  SET_FUNCTION(settings, "settingByName", SettingByName);
  SET_FUNCTION(settings, "nameForSetting", NameForSetting);
  SET_VALUE(target, "settings", settings);
}

NAN_MODULE_INIT(InitFeatures) {
  v8::Local<v8::Object> features = Nan::New<v8::Object>();

#ifdef TORRENT_DISABLE_EXTENSIONS
  SET_BOOLEAN(features, "TORRENT_DISABLE_EXTENSIONS", true);
#else
  SET_BOOLEAN(features, "TORRENT_DISABLE_EXTENSIONS", false);
#endif

#ifdef TORRENT_NO_DEPRECATE
  SET_BOOLEAN(features, "TORRENT_NO_DEPRECATE", true);
#else
  SET_BOOLEAN(features, "TORRENT_NO_DEPRECATE", false);
#endif

  SET_VALUE(target, "features", features);
}

NAN_MODULE_INIT(Init) {
  InitAlerts(target);
  InitExtensions(target);
  SET_VALUE(target, "Session", Session::Init());
  InitSettings(target);

  SET_STRING(target, "version", LIBTORRENT_VERSION);
  InitFeatures(target);
}

NODE_MODULE(libtorrent, Init)

} // namespace libtorrent_rasterbar
