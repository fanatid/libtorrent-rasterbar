#include <libtorrent-rasterbar/alert.h>
#include <libtorrent-rasterbar/torrent_handle.h>
#include <libtorrent-rasterbar/macros.h>
#include <libtorrent/alert_types.hpp>

#define CREATE_ALERT(name, lt_name) \
  v8::Local<v8::FunctionTemplate> name = Nan::New<v8::FunctionTemplate>(New ## name); \
  name->SetClassName(Nan::New("" #name).ToLocalChecked()); \
  name->InstanceTemplate()->SetInternalFieldCount(1); \
  Nan::Set(alerts, libtorrent::lt_name::alert_type, Nan::GetFunction(name).ToLocalChecked());

#define CREATE_ALERT_BODY(constructor) \
  Nan::Call(Nan::New<v8::Function>(constructor), info.This(), 0, NULL); \
  if (info.IsConstructCall()) NewAlert(info.This()); \
  info.GetReturnValue().Set(info.This());

namespace libtorrent_rasterbar {

Nan::Persistent<v8::FunctionTemplate> Alert::prototype;
Nan::Persistent<v8::Function> Alert::constructor;
std::map<int, Nan::Persistent<v8::Function>> Alert::constructors;

v8::Local<v8::Function> Alert::Init() {
  Nan::EscapableHandleScope scope;

  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("Alert").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  v8::Local<v8::Function> cons = Nan::GetFunction(tpl).ToLocalChecked();
  prototype.Reset(tpl);
  constructor.Reset(cons);

  return scope.Escape(cons);
}

v8::Local<v8::Object> Alert::GetAlerts() {
  Nan::EscapableHandleScope scope;
  v8::Local<v8::Object> alerts = Nan::New<v8::Object>();

  CREATE_ALERT(TorrentAlert, torrent_alert);
  constructors[libtorrent::torrent_alert::alert_type].Reset(Nan::GetFunction(TorrentAlert).ToLocalChecked());

  CREATE_ALERT(TorrentAddedAlert, torrent_added_alert);

  return scope.Escape(alerts);
}

v8::Local<v8::Object> Alert::GetTypes() {
  Nan::EscapableHandleScope scope;
  v8::Local<v8::Object> types = Nan::New<v8::Object>();

  SET_INTEGER(types, "TORRENT_ALERT", libtorrent::torrent_alert::alert_type);
  SET_INTEGER(types, "PEER_ALERT", libtorrent::peer_alert::alert_type);
  SET_INTEGER(types, "TRACKER_ALERT", libtorrent::tracker_alert::alert_type);
  SET_INTEGER(types, "TORRENT_ADDED_ALERT", libtorrent::torrent_added_alert::alert_type);
  SET_INTEGER(types, "TORRENT_REMOVED_ALERT", libtorrent::torrent_removed_alert::alert_type);
  SET_INTEGER(types, "READ_PIECE_ALERT", libtorrent::read_piece_alert::alert_type);
  SET_INTEGER(types, "FILE_COMPLETED_ALERT", libtorrent::file_completed_alert::alert_type);
  SET_INTEGER(types, "FILE_RENAMED_ALERT", libtorrent::file_renamed_alert::alert_type);
  SET_INTEGER(types, "FILE_RENAME_FAILED_ALERT", libtorrent::file_rename_failed_alert::alert_type);
  SET_INTEGER(types, "PERFORMANCE_ALERT", libtorrent::performance_alert::alert_type);
  SET_INTEGER(types, "STATE_CHANGED_ALERT", libtorrent::state_changed_alert::alert_type);
  SET_INTEGER(types, "TRAKCER_ERROR_ALERT", libtorrent::tracker_error_alert::alert_type);
  SET_INTEGER(types, "TRACKER_WARNING_ALERT", libtorrent::tracker_warning_alert::alert_type);
  SET_INTEGER(types, "SCARPE_REPLY_ALERT", libtorrent::scrape_reply_alert::alert_type);
  SET_INTEGER(types, "SCARPE_FAILED_ALERT", libtorrent::scrape_failed_alert::alert_type);
  SET_INTEGER(types, "TRACKER_REPLY_ALERT", libtorrent::tracker_reply_alert::alert_type);
  SET_INTEGER(types, "DHT_REPLY_ALERT", libtorrent::dht_reply_alert::alert_type);
  SET_INTEGER(types, "TRACKER_ANNOUNCE_ALERT", libtorrent::tracker_announce_alert::alert_type);
  SET_INTEGER(types, "HASH_FAILED_ALERT", libtorrent::hash_failed_alert::alert_type);
  SET_INTEGER(types, "PEER_BAN_ALERT", libtorrent::peer_ban_alert::alert_type);
  SET_INTEGER(types, "PEER_UNSNUBBED_ALERT", libtorrent::peer_unsnubbed_alert::alert_type);
  SET_INTEGER(types, "PEER_SNUBBED_ALERT", libtorrent::peer_snubbed_alert::alert_type);
  SET_INTEGER(types, "PEER_ERROR_ALERT", libtorrent::peer_error_alert::alert_type);
  SET_INTEGER(types, "PEER_CONNECT_ALERT", libtorrent::peer_connect_alert::alert_type);
  SET_INTEGER(types, "PEER_DISCONNECTED_ALERT", libtorrent::peer_disconnected_alert::alert_type);
  SET_INTEGER(types, "INVALID_REQUEST_ALERT", libtorrent::invalid_request_alert::alert_type);
  SET_INTEGER(types, "TORRENT_FINISHED_ALERT", libtorrent::torrent_finished_alert::alert_type);
  SET_INTEGER(types, "PIECE_FINISHED_ALERT", libtorrent::piece_finished_alert::alert_type);
  SET_INTEGER(types, "REQUEST_DROPPED_ALERT", libtorrent::request_dropped_alert::alert_type);
  SET_INTEGER(types, "BLOCK_TIMEOUT_ALERT", libtorrent::block_timeout_alert::alert_type);
  SET_INTEGER(types, "BLOCK_FINISHED_ALERT", libtorrent::block_finished_alert::alert_type);
  SET_INTEGER(types, "BLOCK_DOWNLOADING_ALERT", libtorrent::block_downloading_alert::alert_type);
  SET_INTEGER(types, "UNWANTED_BLOCK_ALERT", libtorrent::unwanted_block_alert::alert_type);
  SET_INTEGER(types, "STORAGE_MOVED_ALERT", libtorrent::storage_moved_alert::alert_type);
  SET_INTEGER(types, "STORAGE_MOVED_FAILED_ALERT", libtorrent::storage_moved_failed_alert::alert_type);
  SET_INTEGER(types, "TORRENT_DELETED_ALERT", libtorrent::torrent_deleted_alert::alert_type);
  SET_INTEGER(types, "TORRENT_DELETE_FAILED_ALERT", libtorrent::torrent_delete_failed_alert::alert_type);
  SET_INTEGER(types, "SAVE_RESUME_DATA_ALERT", libtorrent::save_resume_data_alert::alert_type);
  SET_INTEGER(types, "SAVE_RESUME_DATA_FAILED_ALERT", libtorrent::save_resume_data_failed_alert::alert_type);
  SET_INTEGER(types, "TORRENT_PAUSED_ALERT", libtorrent::torrent_paused_alert::alert_type);
  SET_INTEGER(types, "TORRENT_RESUMED_ALERT", libtorrent::torrent_resumed_alert::alert_type);
  SET_INTEGER(types, "TORRENT_CHECKED_ALERT", libtorrent::torrent_checked_alert::alert_type);
  SET_INTEGER(types, "URL_SEED_ALERT", libtorrent::url_seed_alert::alert_type);
  SET_INTEGER(types, "FILE_ERROR_ALERT", libtorrent::file_error_alert::alert_type);
  SET_INTEGER(types, "METADATA_FAILED_ALERT", libtorrent::metadata_failed_alert::alert_type);
  SET_INTEGER(types, "METADATA_RECEIVED_ALERT", libtorrent::metadata_received_alert::alert_type);
  SET_INTEGER(types, "UDP_ERROR_ALERT", libtorrent::udp_error_alert::alert_type);
  SET_INTEGER(types, "EXTERNAL_IP_ALERT", libtorrent::external_ip_alert::alert_type);
  SET_INTEGER(types, "LISTEN_FAILED_ALERT", libtorrent::listen_failed_alert::alert_type);
  SET_INTEGER(types, "LISTEN_SUCCEEDED_ALERT", libtorrent::listen_succeeded_alert::alert_type);
  SET_INTEGER(types, "PORTMAP_ERROR_ALERT", libtorrent::portmap_error_alert::alert_type);
  SET_INTEGER(types, "PROTMAP_ALERT", libtorrent::portmap_alert::alert_type);
  // SET_INTEGER(types, "PORTMAP_LOG_ALERT", libtorrent::portmap_log_alert::alert_type);
  SET_INTEGER(types, "FASTRESUME_REJECTED_ALERT", libtorrent::fastresume_rejected_alert::alert_type);
  SET_INTEGER(types, "PEER_BLOCKED_ALERT", libtorrent::peer_blocked_alert::alert_type);
  SET_INTEGER(types, "DHT_ANNOUNCE_ALERT", libtorrent::dht_announce_alert::alert_type);
  SET_INTEGER(types, "DHT_GET_PEERS_ALERT", libtorrent::dht_get_peers_alert::alert_type);
  SET_INTEGER(types, "STATS_ALERT", libtorrent::stats_alert::alert_type);
  SET_INTEGER(types, "CACHE_FLUSHED_ALERT", libtorrent::cache_flushed_alert::alert_type);
  SET_INTEGER(types, "ANONYMOUS_MODE_ALERT", libtorrent::anonymous_mode_alert::alert_type);
  SET_INTEGER(types, "LSD_PEER_ALERT", libtorrent::lsd_peer_alert::alert_type);
  SET_INTEGER(types, "TRACKERID_ALERT", libtorrent::trackerid_alert::alert_type);
  SET_INTEGER(types, "DHT_BOOTSTRAP_ALERT", libtorrent::dht_bootstrap_alert::alert_type);
  // SET_INTEGER(types, "RSS_ALERT", libtorrent::rss_alert::alert_type);
  SET_INTEGER(types, "TORRENT_ERROR_ALERT", libtorrent::torrent_error_alert::alert_type);
  SET_INTEGER(types, "TORRENT_NEED_CERT_ALERT", libtorrent::torrent_need_cert_alert::alert_type);
  SET_INTEGER(types, "INCOMING_CONNECTION_ALERT", libtorrent::incoming_connection_alert::alert_type);
  SET_INTEGER(types, "ADD_TORRENT_ALERT", libtorrent::add_torrent_alert::alert_type);
  SET_INTEGER(types, "STATE_UPDATE_ALERT", libtorrent::state_update_alert::alert_type);
  SET_INTEGER(types, "MMAP_CACHE_ALERT", libtorrent::mmap_cache_alert::alert_type);
  SET_INTEGER(types, "SESSION_STATS_ALERT", libtorrent::session_stats_alert::alert_type);
  SET_INTEGER(types, "TORRENT_UPDATE_ALERT", libtorrent::torrent_update_alert::alert_type);
  // SET_INTEGER(types, "RSS_ITEM_ALERT", libtorrent::rss_item_alert::alert_type);
  SET_INTEGER(types, "DHT_ERROR_ALERT", libtorrent::dht_error_alert::alert_type);
  SET_INTEGER(types, "DHT_IMMUTABLE_ITEM_ALERT", libtorrent::dht_immutable_item_alert::alert_type);
  SET_INTEGER(types, "DHT_MUTABLE_ITEM_ALERT", libtorrent::dht_mutable_item_alert::alert_type);
  SET_INTEGER(types, "DHT_PUT_ALERT", libtorrent::dht_put_alert::alert_type);
  SET_INTEGER(types, "I2P_ALERT", libtorrent::i2p_alert::alert_type);
  SET_INTEGER(types, "DHT_OUTGOING_GET_PEERS_ALERT", libtorrent::dht_outgoing_get_peers_alert::alert_type);
  // SET_INTEGER(types, "LOG_ALERT", libtorrent::log_alert::alert_type);
  // SET_INTEGER(types, "TORRENT_LOG_ALERT", libtorrent::torrent_log_alert::alert_type);
  // SET_INTEGER(types, "PEER_LOG_ALERT", libtorrent::peer_log_alert::alert_type);
  SET_INTEGER(types, "LSD_ERROR_ALERT", libtorrent::lsd_error_alert::alert_type);
  SET_INTEGER(types, "DHT_STATS_ALERT", libtorrent::dht_stats_alert::alert_type);
  SET_INTEGER(types, "INCOMING_REQUEST_ALERT", libtorrent::incoming_request_alert::alert_type);
  SET_INTEGER(types, "DHT_LOG_ALERT", libtorrent::dht_log_alert::alert_type);
  SET_INTEGER(types, "DHT_PKT_ALERT", libtorrent::dht_pkt_alert::alert_type);
  SET_INTEGER(types, "DHT_GET_PEERS_REPLY_ALERT", libtorrent::dht_get_peers_reply_alert::alert_type);
  SET_INTEGER(types, "DHT_DIRECT_RESPONSE_ALERT", libtorrent::dht_direct_response_alert::alert_type);
  SET_INTEGER(types, "PICKER_LOG_ALERT", libtorrent::picker_log_alert::alert_type);

  return scope.Escape(types);
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

v8::Local<v8::Object> Alert::FromAlertPointer(libtorrent::alert* alert, v8::Local<v8::Object> alerts) {
  Nan::EscapableHandleScope scope;

  v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
  if (alert->type() != 0 && Nan::Has(alerts, alert->type()) == Nan::Just(true)) {
    v8::Local<v8::Value> alert_t = Nan::Get(alerts, alert->type()).ToLocalChecked();
    if (alert_t->IsFunction()) cons = v8::Local<v8::Function>::Cast(alert_t);
  }

  v8::Local<v8::Object> result = Nan::NewInstance(cons).ToLocalChecked();
  Nan::ObjectWrap::Unwrap<Alert>(result)->alert = alert;

  return scope.Escape(result);
}

NAN_METHOD(Alert::New) {
  Nan::SetMethod(info.This(), "timestamp", Timestamp);
  Nan::SetMethod(info.This(), "type", Type);
  Nan::SetMethod(info.This(), "what", What);
  Nan::SetMethod(info.This(), "message", Message);
  Nan::SetMethod(info.This(), "category", Category);
  if (info.IsConstructCall()) NewAlert(info.This());
  info.GetReturnValue().Set(info.This());
}

NAN_METHOD(Alert::NewTorrentAlert) {
  Nan::SetMethod(info.This(), "torrentName", TorrentName);
  Nan::SetAccessor(info.This(), Nan::New("handle").ToLocalChecked(), GetHandle);
  CREATE_ALERT_BODY(constructor);
}

NAN_METHOD(Alert::NewTorrentAddedAlert) {
  CREATE_ALERT_BODY(constructors[libtorrent::torrent_alert::alert_type]);
}

NAN_METHOD(Alert::Timestamp) {
  Alert* obj = Nan::ObjectWrap::Unwrap<Alert>(info.Holder());
  auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(obj->alert->timestamp().time_since_epoch()).count();
  info.GetReturnValue().Set(Nan::New<v8::Date>(ns / 1000000).ToLocalChecked());
}

NAN_METHOD(Alert::Type) {
  Alert* obj = Nan::ObjectWrap::Unwrap<Alert>(info.Holder());
  info.GetReturnValue().Set(Nan::New(obj->alert->type()));
}

NAN_METHOD(Alert::What) {
  Alert* obj = Nan::ObjectWrap::Unwrap<Alert>(info.Holder());
  info.GetReturnValue().Set(Nan::New(obj->alert->what()).ToLocalChecked());
}

NAN_METHOD(Alert::Message) {
  Alert* obj = Nan::ObjectWrap::Unwrap<Alert>(info.Holder());
  info.GetReturnValue().Set(Nan::New(obj->alert->message().c_str()).ToLocalChecked());
}

NAN_METHOD(Alert::Category) {
  Alert* obj = Nan::ObjectWrap::Unwrap<Alert>(info.Holder());
  info.GetReturnValue().Set(Nan::New(obj->alert->category()));
}

NAN_METHOD(Alert::TorrentName) {
  Alert* obj = Nan::ObjectWrap::Unwrap<Alert>(info.Holder());
  char const* name = dynamic_cast<libtorrent::torrent_alert*>(obj->alert)->torrent_name();
  info.GetReturnValue().Set(Nan::New(name).ToLocalChecked());
}

NAN_GETTER(Alert::GetHandle) {
  Alert* obj = Nan::ObjectWrap::Unwrap<Alert>(info.Holder());
  libtorrent::torrent_handle th = dynamic_cast<libtorrent::torrent_alert*>(obj->alert)->handle;
  info.GetReturnValue().Set(TorrentHandle::FromTorrentHandle(th));
}

} // namespace libtorrent_rasterbar
