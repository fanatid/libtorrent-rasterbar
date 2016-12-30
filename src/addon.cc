#include <nan.h>
#include <libtorrent/version.hpp>
#include <libtorrent-rasterbar/add_torrent_params.h>
#include <libtorrent-rasterbar/alert.h>
#include <libtorrent-rasterbar/bencoding.h>
#include <libtorrent-rasterbar/extensions.h>
#include <libtorrent-rasterbar/session.h>
#include <libtorrent-rasterbar/settings.h>
#include <libtorrent-rasterbar/settings_pack.h>
#include <libtorrent-rasterbar/storage_mode.h>
#include <libtorrent-rasterbar/torrent_handle.h>
#include <libtorrent-rasterbar/torrent_info.h>
#include <libtorrent-rasterbar/macros.h>

namespace libtorrent_rasterbar {

NAN_MODULE_INIT(InitAlerts) {
  v8::Local<v8::Object> alerts = Nan::New<v8::Object>();
  Alert::Init();
  SET_VALUE(alerts, "types", Alert::GetTypes());
  SET_VALUE(alerts, "categories", Alert::GetCategories());
  SET_VALUE(target, "alerts", alerts);
}

NAN_MODULE_INIT(InitBencoding) {
  v8::Local<v8::Object> bencoding = Nan::New<v8::Object>();
  SET_FUNCTION(bencoding, "encode", BEncode);
  SET_FUNCTION(bencoding, "decode", BDecode);
  SET_VALUE(target, "bencoding", bencoding);
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
  SET_VALUE(settings, "STRING", SettingsPack::GetStringSettingsInfo());
  SET_VALUE(settings, "NUMBER", SettingsPack::GetNumberSettingsInfo());
  SET_VALUE(settings, "BOOLEAN", SettingsPack::GetBooleanSettingsInfo());
  SET_VALUE(target, "settings", settings);
}

NAN_MODULE_INIT(InitStorage) {
  v8::Local<v8::Object> storage = Nan::New<v8::Object>();
  SET_VALUE(storage, "modes", GetStorageModes());
  SET_VALUE(target, "storage", storage);
}

NAN_MODULE_INIT(InitTorrent) {
  v8::Local<v8::Object> torrent = Nan::New<v8::Object>();
  v8::Local<v8::Object> atp = Nan::New<v8::Object>();
  SET_VALUE(atp, "flags", AddTorrentParamsGetFlags());
  SET_VALUE(torrent, "AddTorrentParams", atp);
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
  InitBencoding(target);
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
