#include <libtorrent-rasterbar/extensions.h>

namespace libtorrent_rasterbar {

Nan::Persistent<v8::FunctionTemplate> PluginStorage::prototype;
Nan::Persistent<v8::Function> PluginStorage::constructor;

v8::Local<v8::Function> PluginStorage::Init() {
  Nan::EscapableHandleScope scope;

  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("PluginStorage").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  PluginStorage::prototype.Reset(tpl);
  PluginStorage::constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());

  return scope.Escape(Nan::GetFunction(tpl).ToLocalChecked());
}

NAN_METHOD(PluginStorage::New) {
  if (!info.IsConstructCall()) return;

  PluginStorage* obj = new PluginStorage();
  obj->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

} // namespace libtorrent_rasterbar
