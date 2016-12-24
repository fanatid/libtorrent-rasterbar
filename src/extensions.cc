#include <libtorrent-rasterbar/extensions.h>

#ifndef TORRENT_DISABLE_EXTENSIONS

namespace libtorrent_rasterbar {

Nan::Persistent<v8::FunctionTemplate> Plugin::prototype;
Nan::Persistent<v8::Function> Plugin::constructor;

v8::Local<v8::Function> Plugin::Init() {
  Nan::EscapableHandleScope scope;

  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("Plugin").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  v8::Local<v8::Function> cons = Nan::GetFunction(tpl).ToLocalChecked();
  Plugin::prototype.Reset(tpl);
  Plugin::constructor.Reset(cons);

  return scope.Escape(cons);
}

NAN_METHOD(Plugin::New) {
  if (!info.IsConstructCall()) return;

  Plugin* obj = new Plugin();
  obj->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

} // namespace libtorrent_rasterbar

#endif // TORRENT_DISABLE_EXTENSIONS
