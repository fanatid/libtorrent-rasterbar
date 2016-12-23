#include <nan.h>
#include <libtorrent/version.hpp>
#include <libtorrent-rasterbar/extensions.h>
#include <libtorrent-rasterbar/session.h>

namespace libtorrent_rasterbar {

NAN_MODULE_INIT(Init) {
#ifndef TORRENT_DISABLE_EXTENSIONS
  v8::Local<v8::Object> extensions = Nan::New<v8::Object>();
  Nan::Set(extensions, Nan::New("SmartBan").ToLocalChecked(), Nan::New("smart_ban").ToLocalChecked());
  Nan::Set(extensions, Nan::New("UTMetadata").ToLocalChecked(), Nan::New("ut_metadata").ToLocalChecked());
  Nan::Set(extensions, Nan::New("UTPex").ToLocalChecked(), Nan::New("ut_pex").ToLocalChecked());
  Nan::Set(extensions, Nan::New("PluginStorage").ToLocalChecked(), PluginStorage::Init());
  Nan::Set(target, Nan::New("extensions").ToLocalChecked(), extensions);
#endif // TORRENT_DISABLE_EXTENSIONS

  Nan::Set(target, Nan::New("Session").ToLocalChecked(), Session::Init());

  Nan::Set(target, Nan::New("version").ToLocalChecked(), Nan::New(LIBTORRENT_VERSION).ToLocalChecked());
}

NODE_MODULE(libtorrent, Init)

} // namespace libtorrent_rasterbar
