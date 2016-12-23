#include <nan.h>
#include <libtorrent/version.hpp>
#include <libtorrent-rasterbar/alert.h>
#include <libtorrent-rasterbar/extensions.h>
#include <libtorrent-rasterbar/session.h>

namespace libtorrent_rasterbar {

NAN_MODULE_INIT(InitFeatures) {
  v8::Local<v8::Object> features = Nan::New<v8::Object>();

#ifdef TORRENT_DISABLE_EXTENSIONS
  Nan::Set(features, Nan::New("TORRENT_DISABLE_EXTENSIONS").ToLocalChecked(), Nan::New(true));
#else
  Nan::Set(features, Nan::New("TORRENT_DISABLE_EXTENSIONS").ToLocalChecked(), Nan::New(false));
#endif

#ifdef TORRENT_NO_DEPRECATE
  Nan::Set(features, Nan::New("TORRENT_NO_DEPRECATE").ToLocalChecked(), Nan::New(true));
#else
  Nan::Set(features, Nan::New("TORRENT_NO_DEPRECATE").ToLocalChecked(), Nan::New(false));
#endif

  Nan::Set(target, Nan::New("features").ToLocalChecked(), features);
}

NAN_MODULE_INIT(Init) {
  v8::Local<v8::Object> alerts = Nan::New<v8::Object>();
  Nan::Set(alerts, Nan::New("Alert").ToLocalChecked(), Alert::Init());
  Nan::Set(target, Nan::New("alerts").ToLocalChecked(), alerts);

#ifndef TORRENT_DISABLE_EXTENSIONS
  v8::Local<v8::Object> extensions = Nan::New<v8::Object>();
  Nan::Set(extensions, Nan::New("SmartBan").ToLocalChecked(), Nan::New("smart_ban").ToLocalChecked());
  Nan::Set(extensions, Nan::New("UTMetadata").ToLocalChecked(), Nan::New("ut_metadata").ToLocalChecked());
  Nan::Set(extensions, Nan::New("UTPex").ToLocalChecked(), Nan::New("ut_pex").ToLocalChecked());
  Nan::Set(extensions, Nan::New("Plugin").ToLocalChecked(), Plugin::Init());
  Nan::Set(target, Nan::New("extensions").ToLocalChecked(), extensions);
#endif // TORRENT_DISABLE_EXTENSIONS

  Nan::Set(target, Nan::New("Session").ToLocalChecked(), Session::Init());

  Nan::Set(target, Nan::New("version").ToLocalChecked(), Nan::New(LIBTORRENT_VERSION).ToLocalChecked());
  InitFeatures(target);
}

NODE_MODULE(libtorrent, Init)

} // namespace libtorrent_rasterbar
