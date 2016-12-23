#include <nan.h>
#include <libtorrent-rasterbar/extensions.h>

NAN_METHOD(create) {
  v8::Local<v8::Function> cons = v8::Local<v8::Function>::Cast(info[0]);
  v8::Local<v8::Object> plugin = Nan::NewInstance(cons).ToLocalChecked();
  libtorrent_rasterbar::Plugin* obj = Nan::ObjectWrap::Unwrap<libtorrent_rasterbar::Plugin>(plugin);
  obj->Reset(boost::shared_ptr<libtorrent::plugin>(new libtorrent::plugin()));

  info.GetReturnValue().Set(plugin);
}

NAN_MODULE_INIT(Init) {
  Nan::Export(target, "create", create);
}

NODE_MODULE(addon, Init)
