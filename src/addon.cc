#include <nan.h>
#include <libtorrent/version.hpp>
#include <libtorrent-rasterbar/add_torrent_params.h>
#include <libtorrent-rasterbar/alert.h>
#include <libtorrent-rasterbar/extensions.h>
#include <libtorrent-rasterbar/session.h>
#include <libtorrent-rasterbar/settings.h>
#include <libtorrent-rasterbar/settings_pack.h>
#include <libtorrent-rasterbar/torrent_handle.h>
#include <libtorrent-rasterbar/torrent_info.h>
#include <libtorrent-rasterbar/macros.h>

namespace libtorrent_rasterbar {

NAN_MODULE_INIT(InitAlerts) {
  v8::Local<v8::Object> alerts = Nan::New<v8::Object>();
  SET_VALUE(alerts, "Alert", Alert::Init());
  SET_VALUE(alerts, "categories", Alert::GetCategories());
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

NAN_MODULE_INIT(InitSession) {
  SET_VALUE(target, "Session", Session::Init());
}

NAN_MODULE_INIT(InitSettings) {
  v8::Local<v8::Object> settings = Nan::New<v8::Object>();
  SET_VALUE(settings, "SettingsPack", SettingsPack::Init());
  SET_FUNCTION(settings, "settingByName", SettingByName);
  SET_FUNCTION(settings, "nameForSetting", NameForSetting);
  v8::Local<v8::Object> strings = Nan::New<v8::Object>();
  SET_INTEGER(strings, "offset", 0x0000);
  SET_INTEGER(strings, "count", libtorrent::settings_pack::num_string_settings);
  SET_VALUE(settings, "STRING", strings);
  v8::Local<v8::Object> number = Nan::New<v8::Object>();
  SET_INTEGER(number, "offset", 0x4000);
  SET_INTEGER(number, "count", libtorrent::settings_pack::num_int_settings);
  SET_VALUE(settings, "NUMBER", number);
  v8::Local<v8::Object> boolean = Nan::New<v8::Object>();
  SET_INTEGER(boolean, "offset", 0x8000);
  SET_INTEGER(boolean, "count", libtorrent::settings_pack::num_bool_settings);
  SET_VALUE(settings, "BOOLEAN", boolean);
  SET_VALUE(target, "settings", settings);
}

NAN_MODULE_INIT(InitStorage) {
  v8::Local<v8::Object> storage = Nan::New<v8::Object>();
  v8::Local<v8::Object> modes = Nan::New<v8::Object>();
  SET_INTEGER(modes, "ALLOCATE", libtorrent::storage_mode_allocate);
  SET_INTEGER(modes, "SPARSE", libtorrent::storage_mode_sparse);
  SET_VALUE(storage, "modes", modes);
  SET_VALUE(target, "storage", storage);
}

NAN_MODULE_INIT(InitTorrent) {
  v8::Local<v8::Object> torrent = Nan::New<v8::Object>();
  SET_VALUE(torrent, "ADD_TORRENT_PARAMS", GetAddTorrentParamsFlags());
  SET_VALUE(torrent, "TorrentInfo", TorrentInfo::Init());
  TorrentHandle::Init();
  SET_VALUE(target, "torrent", torrent);
}

NAN_MODULE_INIT(InitFeatures) {
  v8::Local<v8::Object> features = Nan::New<v8::Object>();
#ifdef TORRENT_DISABLE_EXTENSIONS
  SET_BOOLEAN(features, "TORRENT_DISABLE_EXTENSIONS", true);
#else
  SET_BOOLEAN(features, "TORRENT_DISABLE_EXTENSIONS", false);
#endif
  SET_VALUE(target, "features", features);
}

NAN_MODULE_INIT(Init) {
  Nan::HandleScope scope; // HandleScope for initialization

  InitAlerts(target);
  InitExtensions(target);
  InitSession(target);
  InitSettings(target);
  InitStorage(target);
  InitTorrent(target);

  SET_STRING(target, "version", LIBTORRENT_VERSION);
  InitFeatures(target);
}

NODE_MODULE(libtorrent, Init)

} // namespace libtorrent_rasterbar
