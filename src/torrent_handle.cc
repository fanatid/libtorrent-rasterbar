#include <libtorrent-rasterbar/torrent_handle.h>
#include <libtorrent-rasterbar/macros.h>

namespace libtorrent_rasterbar {

Nan::Persistent<v8::FunctionTemplate> TorrentHandle::prototype;
Nan::Persistent<v8::Function> TorrentHandle::constructor;

v8::Local<v8::Function> TorrentHandle::Init() {
  Nan::EscapableHandleScope scope;

  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("TorrentHandle").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  Nan::SetPrototypeMethod(tpl, "isValid", IsValid);

  v8::Local<v8::Function> cons = Nan::GetFunction(tpl).ToLocalChecked();
  TorrentHandle::prototype.Reset(tpl);
  TorrentHandle::constructor.Reset(cons);

  return scope.Escape(cons);
}

v8::Local<v8::Object> TorrentHandle::FromTorrentHandle(libtorrent::torrent_handle th) {
  Nan::EscapableHandleScope scope;

  v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
  v8::Local<v8::Object> result = Nan::NewInstance(cons).ToLocalChecked();

  TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(result);
  obj->th = th;

  return scope.Escape(result);
}

NAN_METHOD(TorrentHandle::New) {
  if (!info.IsConstructCall()) return;

  TorrentHandle* obj = new TorrentHandle();
  obj->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

NAN_METHOD(TorrentHandle::IsValid) {
  TorrentHandle* obj = Nan::ObjectWrap::Unwrap<TorrentHandle>(info.Holder());
  info.GetReturnValue().Set(Nan::New<v8::Boolean>(obj->th.is_valid()));
}

// NAN_METHOD_WITH_LIBTORRENT_EXCEPTION_HANDLE(TorrentHandle::MethodName)

} // namespace libtorrent_rasterbar
