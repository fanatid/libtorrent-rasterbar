#include <nan.h>
#include <libtorrent/version.hpp>
#include <libtorrent-rasterbar/extensions.h>
#include <libtorrent-rasterbar/session.h>
#include <libtorrent-rasterbar/macros.h>

namespace libtorrent_rasterbar {

NAN_MODULE_INIT(Init) {
  v8::Local<v8::Object> extensions = Nan::New<v8::Object>();
  Nan::Set(extensions, Nan::New("PluginStorage").ToLocalChecked(), PluginStorage::Init());
  Nan::Set(target, Nan::New("extensions").ToLocalChecked(), extensions);

  Nan::Set(target, Nan::New("Session").ToLocalChecked(), Session::Init());

  Nan::Set(target, Nan::New("version").ToLocalChecked(), Nan::New(LIBTORRENT_VERSION).ToLocalChecked());
}

NODE_MODULE(libtorrent, Init)

} // namespace libtorrent_rasterbar
