#include <libtorrent-rasterbar/alert.h>
#include <libtorrent-rasterbar/macros.h>

namespace libtorrent_rasterbar {

Nan::Persistent<v8::FunctionTemplate> Alert::prototype;
Nan::Persistent<v8::Function> Alert::constructor;

v8::Local<v8::Function> Alert::Init() {
  Nan::EscapableHandleScope scope;

  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("Alert").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  Alert::prototype.Reset(tpl);
  Alert::constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());

  return scope.Escape(Nan::GetFunction(tpl).ToLocalChecked());
}

v8::Local<v8::Object> Alert::FromAlertPointer(libtorrent::alert* alert) {
  Nan::EscapableHandleScope scope;

  v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
  v8::Local<v8::Object> result = Nan::NewInstance(cons).ToLocalChecked();
  SET_INTEGER(result, "type", alert->type());
  SET_STRING(result, "what", alert->what());
  SET_STRING(result, "message", alert->message().c_str());
  SET_INTEGER(result, "category", alert->category());

  Alert* obj = Nan::ObjectWrap::Unwrap<Alert>(result);
  obj->alert = alert;

  return scope.Escape(result);
}

NAN_METHOD(Alert::New) {
  if (!info.IsConstructCall()) return;

  Alert* obj = new Alert();
  obj->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

} // namespace libtorrent_rasterbar
