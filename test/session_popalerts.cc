#include <nan.h>
#include <libtorrent/alert_types.hpp>
#include <libtorrent-rasterbar/alert.h>

class TorrentErrorAlert : public Nan::ObjectWrap {
 public:
  static Nan::Persistent<v8::Function> constructor_base;
  static NAN_METHOD(Init) {
    constructor_base.Reset(v8::Local<v8::Function>::Cast(info[0]));

    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("TorrentErrorAlert").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    return info.GetReturnValue().Set(Nan::GetFunction(tpl).ToLocalChecked());
  };

  libtorrent::alert* alert;

 private:
  static NAN_METHOD(New) {
    Nan::SetAccessor(info.This(), Nan::New("error").ToLocalChecked(), GetError);
    Nan::Call(Nan::New<v8::Function>(constructor_base), info.This(), 0, NULL);
    if (info.IsConstructCall()) libtorrent_rasterbar::Alert::NewAlert(info.This());
    info.GetReturnValue().Set(info.This());
  };

  static NAN_GETTER(GetError) {
    libtorrent_rasterbar::Alert* obj = Nan::ObjectWrap::Unwrap<libtorrent_rasterbar::Alert>(info.Holder());
    auto msg = dynamic_cast<libtorrent::torrent_error_alert*>(obj->alert)->error.message();
    info.GetReturnValue().Set(Nan::New(msg).ToLocalChecked());
  }
};

Nan::Persistent<v8::Function> TorrentErrorAlert::constructor_base;

NAN_MODULE_INIT(Init) {
  Nan::Export(target, "createTorrentErrorAlert", TorrentErrorAlert::Init);
}

NODE_MODULE(addon, Init)
