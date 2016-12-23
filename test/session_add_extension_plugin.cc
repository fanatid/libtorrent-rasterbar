#include <nan.h>
#include <libtorrent-rasterbar/extensions.h>

NAN_METHOD(create) {
  v8::Local<v8::Function> cons = v8::Local<v8::Function>::Cast(info[0]);
  v8::Local<v8::Object> obj = Nan::NewInstance(cons).ToLocalChecked();
  libtorrent_rasterbar::PluginStorage* ps = Nan::ObjectWrap::Unwrap<libtorrent_rasterbar::PluginStorage>(obj);
  ps->Reset(boost::shared_ptr<libtorrent::plugin>(new libtorrent::plugin()));

  info.GetReturnValue().Set(obj);
}

NAN_MODULE_INIT(Init) {
  Nan::Export(target, "create", create);
}

NODE_MODULE(addon, Init)
