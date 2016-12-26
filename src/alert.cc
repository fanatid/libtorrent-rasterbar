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

  v8::Local<v8::ObjectTemplate> inst = tpl->InstanceTemplate();
  Nan::SetAccessor(inst, Nan::New("timestamp").ToLocalChecked(), Alert::GetTimestamp);
  Nan::SetAccessor(inst, Nan::New("type").ToLocalChecked(), Alert::GetType);
  Nan::SetAccessor(inst, Nan::New("what").ToLocalChecked(), Alert::GetWhat);
  Nan::SetAccessor(inst, Nan::New("message").ToLocalChecked(), Alert::GetMessage);
  Nan::SetAccessor(inst, Nan::New("category").ToLocalChecked(), Alert::GetCategory);

  v8::Local<v8::Function> cons = Nan::GetFunction(tpl).ToLocalChecked();
  Alert::prototype.Reset(tpl);
  Alert::constructor.Reset(cons);

  return scope.Escape(cons);
}

v8::Local<v8::Object> Alert::GetCategories() {
  Nan::EscapableHandleScope scope;
  v8::Local<v8::Object> categories = Nan::New<v8::Object>();

  SET_INTEGER(categories, "ERROR_NOTIFICATION", libtorrent::alert::error_notification);
  SET_INTEGER(categories, "PEER_NOTIFICATION", libtorrent::alert::peer_notification);
  SET_INTEGER(categories, "PORT_MAPPING_NOTIFICATION", libtorrent::alert::port_mapping_notification);
  SET_INTEGER(categories, "STORAGE_NOTIFICATION", libtorrent::alert::storage_notification);
  SET_INTEGER(categories, "TRACKER_NOTIFICATION", libtorrent::alert::tracker_notification);
  SET_INTEGER(categories, "DEBUG_NOTIFICATION", libtorrent::alert::debug_notification);
  SET_INTEGER(categories, "STATUS_NOTIFICATION", libtorrent::alert::status_notification);
  SET_INTEGER(categories, "PROGRESS_NOTIFICATION", libtorrent::alert::progress_notification);
  SET_INTEGER(categories, "IP_BLOCK_NOTIFICATION", libtorrent::alert::ip_block_notification);
  SET_INTEGER(categories, "PERFORMANCE_WARNING", libtorrent::alert::performance_warning);
  SET_INTEGER(categories, "DHT_NOTIFICATION", libtorrent::alert::dht_notification);
  SET_INTEGER(categories, "STATS_NOTIFICATION", libtorrent::alert::stats_notification);
  SET_INTEGER(categories, "SESSION_LOG_NOTIFICATION", libtorrent::alert::session_log_notification);
  SET_INTEGER(categories, "TORRENT_LOG_NOTIFICATION", libtorrent::alert::torrent_log_notification);
  SET_INTEGER(categories, "PEER_LOG_NOTIFICATION", libtorrent::alert::peer_log_notification);
  SET_INTEGER(categories, "INCOMING_REQUEST_NOTIFICATION", libtorrent::alert::incoming_request_notification);
  SET_INTEGER(categories, "DHT_LOG_NOTIFICATION", libtorrent::alert::dht_log_notification);
  SET_INTEGER(categories, "DHT_OPERATION_NOTIFICATION", libtorrent::alert::dht_operation_notification);
  SET_INTEGER(categories, "PORT_MAPPING_LOG_NOTIFICATION", libtorrent::alert::port_mapping_log_notification);
  SET_INTEGER(categories, "PICKER_LOG_NOTIFICATION", libtorrent::alert::picker_log_notification);
  SET_INTEGER(categories, "ALL", libtorrent::alert::all_categories);

  return scope.Escape(categories);
}

v8::Local<v8::Object> Alert::FromAlertPointer(libtorrent::alert* alert) {
  Nan::EscapableHandleScope scope;

  v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
  v8::Local<v8::Object> result = Nan::NewInstance(cons).ToLocalChecked();

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

NAN_GETTER(Alert::GetTimestamp) {
  Alert* obj = Nan::ObjectWrap::Unwrap<Alert>(info.Holder());
  auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(obj->alert->timestamp().time_since_epoch()).count();
  info.GetReturnValue().Set(Nan::New<v8::Date>(ns / 1000000).ToLocalChecked());
}

NAN_GETTER(Alert::GetType) {
  Alert* obj = Nan::ObjectWrap::Unwrap<Alert>(info.Holder());
  info.GetReturnValue().Set(Nan::New(obj->alert->type()));
}

NAN_GETTER(Alert::GetWhat) {
  Alert* obj = Nan::ObjectWrap::Unwrap<Alert>(info.Holder());
  info.GetReturnValue().Set(Nan::New(obj->alert->what()).ToLocalChecked());
}

NAN_GETTER(Alert::GetMessage) {
  Alert* obj = Nan::ObjectWrap::Unwrap<Alert>(info.Holder());
  info.GetReturnValue().Set(Nan::New(obj->alert->message().c_str()).ToLocalChecked());
}

NAN_GETTER(Alert::GetCategory) {
  Alert* obj = Nan::ObjectWrap::Unwrap<Alert>(info.Holder());
  info.GetReturnValue().Set(Nan::New(obj->alert->category()));
}

} // namespace libtorrent_rasterbar
