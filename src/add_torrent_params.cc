#include <libtorrent-rasterbar/add_torrent_params.h>
#include <libtorrent-rasterbar/torrent_info.h>
#include <libtorrent-rasterbar/macros.h>

#define THROW_TYPE_ERROR_RETURN(prop, type)                                   \
  Nan::ThrowTypeError("Property " #prop " must be a " #type);                 \
  return 1;

#define HAS_KEY(obj, key)                                                     \
  (Nan::Has(obj, Nan::New(key).ToLocalChecked()) == Nan::Just(true))

#define GET_WITH_CHECK(obj, prop, name, check, fullProp, type)                \
  v8::Local<v8::Value> name = Nan::Get(obj, prop).ToLocalChecked();           \
  if (!name->check()) {                                                       \
    THROW_TYPE_ERROR_RETURN(fullProp, type);                                  \
  }

#define GET_KEY_WITH_CHECK(obj, prop, name, check, fullProp, type)            \
  GET_WITH_CHECK(obj, Nan::New(prop).ToLocalChecked(), name, check, fullProp, type)

namespace libtorrent_rasterbar {

v8::Local<v8::Object> AddTorrentParamsFlags() {
  Nan::EscapableHandleScope scope;
  v8::Local<v8::Object> flags = Nan::New<v8::Object>();

  SET_INTEGER(flags, "SEED_MODE", libtorrent::add_torrent_params::flag_seed_mode);
  SET_INTEGER(flags, "OVERRIDE_RESUME_DATA", libtorrent::add_torrent_params::flag_override_resume_data);
  SET_INTEGER(flags, "UPLOAD_MODE", libtorrent::add_torrent_params::flag_upload_mode);
  SET_INTEGER(flags, "SHARE_MODE", libtorrent::add_torrent_params::flag_share_mode);
  SET_INTEGER(flags, "APPLY_IP_FILTER", libtorrent::add_torrent_params::flag_apply_ip_filter);
  SET_INTEGER(flags, "PAUSED", libtorrent::add_torrent_params::flag_paused);
  SET_INTEGER(flags, "AUTO_MANAGED", libtorrent::add_torrent_params::flag_auto_managed);
  SET_INTEGER(flags, "DUPLICATE_IS_ERROR", libtorrent::add_torrent_params::flag_duplicate_is_error);
  SET_INTEGER(flags, "MERGE_RESUME_TRACKERS", libtorrent::add_torrent_params::flag_merge_resume_trackers);
  SET_INTEGER(flags, "UPDATE_SUBSCRIBE", libtorrent::add_torrent_params::flag_update_subscribe);
  SET_INTEGER(flags, "SUPER_SEEDING", libtorrent::add_torrent_params::flag_super_seeding);
  SET_INTEGER(flags, "SEQUENTIAL_DOWNLOAD", libtorrent::add_torrent_params::flag_sequential_download);
  SET_INTEGER(flags, "USE_RESUME_SAVE_PATH", libtorrent::add_torrent_params::flag_use_resume_save_path);
  SET_INTEGER(flags, "PINNED", libtorrent::add_torrent_params::flag_pinned);
  SET_INTEGER(flags, "MERGE_RESUME_HTTP_SEEDS", libtorrent::add_torrent_params::flag_merge_resume_http_seeds);
  SET_INTEGER(flags, "STOP_WHEN_READY", libtorrent::add_torrent_params::flag_stop_when_ready);
  SET_INTEGER(flags, "DEFAULT", libtorrent::add_torrent_params::default_flags);

  return scope.Escape(flags);
}

int AddTorrentParamsFromObject(v8::Local<v8::Object> obj, libtorrent::add_torrent_params& p) {
  Nan::HandleScope scope;

  if (HAS_KEY(obj, "ti")) {
    v8::Local<v8::Value> ti = Nan::Get(obj, Nan::New("ti").ToLocalChecked()).ToLocalChecked();
    if (!Nan::New(TorrentInfo::prototype)->HasInstance(ti)) {
      THROW_TYPE_ERROR_RETURN("ti", "TorrentInfo");
    }
    p.ti = Nan::ObjectWrap::Unwrap<TorrentInfo>(ti->ToObject())->ti;
  }

  if (HAS_KEY(obj, "trackers")) {
    GET_KEY_WITH_CHECK(obj, "trackers", trackers, IsArray, "trackers", "Array");
    for (uint32_t i = 0, length = v8::Local<v8::Array>::Cast(trackers)->Length(); i < length; ++i) {
      GET_WITH_CHECK(trackers->ToObject(), i, tracker, IsString, ("trackers." + std::to_string(i)).c_str(), "String");
      p.trackers.push_back(std::string(*Nan::Utf8String(tracker)));
    }
  }

  if (HAS_KEY(obj, "urlSeeds")) {
    GET_KEY_WITH_CHECK(obj, "urlSeeds", urls, IsArray, "urlSeeds", "Array");
    for (uint32_t i = 0, length = v8::Local<v8::Array>::Cast(urls)->Length(); i < length; ++i) {
      GET_WITH_CHECK(urls->ToObject(), i, url, IsString, ("urlSeeds." + std::to_string(i)).c_str(), "String");
      p.url_seeds.push_back(std::string(*Nan::Utf8String(url)));
    }
  }

  if (HAS_KEY(obj, "dhtNodes")) {
    GET_KEY_WITH_CHECK(obj, "dhtNodes", nodes, IsArray, "dhtNodes", "Array");
    for (uint32_t i = 0, length = v8::Local<v8::Array>::Cast(nodes)->Length(); i < length; ++i) {
      GET_WITH_CHECK(nodes->ToObject(), i, node, IsObject, ("dhtNodes." + std::to_string(i)).c_str(), "Object");
      GET_KEY_WITH_CHECK(node->ToObject(), "host", host, IsString, ("dhtNodes." + std::to_string(i) + ".host").c_str(), "String");
      GET_KEY_WITH_CHECK(node->ToObject(), "port", port, IsNumber, ("dhtNodes." + std::to_string(i) + ".port").c_str(), "Number");
      p.dht_nodes.push_back(std::make_pair(std::string(*Nan::Utf8String(host)), (int) port->IntegerValue()));
    }
  }

  if (HAS_KEY(obj, "name")) {
    GET_KEY_WITH_CHECK(obj, "name", name, IsString, "name", "String");
    p.name = std::string(*Nan::Utf8String(name));
  }

  if (HAS_KEY(obj, "savePath")) {
    GET_KEY_WITH_CHECK(obj, "savePath", save_path, IsString, "savePath", "String");
    p.save_path = std::string(*Nan::Utf8String(save_path));
  }

  if (HAS_KEY(obj, "resumeData")) {
    v8::Local<v8::Value> data = Nan::Get(obj, Nan::New("resumeData").ToLocalChecked()).ToLocalChecked();
    if (!node::Buffer::HasInstance(data)) {
      THROW_TYPE_ERROR_RETURN("resumeData", "Buffer");
    }
    const char* buffer = node::Buffer::Data(data);
    p.resume_data = std::vector<char>(buffer, buffer + node::Buffer::Length(data));
  }

  if (HAS_KEY(obj, "storageMode")) {
    GET_KEY_WITH_CHECK(obj, "storageMode", storage_mode, IsNumber, "storageMode", "Number");
    p.storage_mode = (libtorrent::storage_mode_t) storage_mode->IntegerValue();
  }

  // if (HAS_KEY(obj, "storage"))
  // if (HAS_KEY(obj, "userData"))

  if (HAS_KEY(obj, "filePriorities")) {
    GET_KEY_WITH_CHECK(obj, "filePriorities", priorities, IsArray, "filePriorities", "Array");
    for (uint32_t i = 0, length = v8::Local<v8::Array>::Cast(priorities)->Length(); i < length; ++i) {
      GET_WITH_CHECK(priorities->ToObject(), i, priority, IsNumber, ("filePriorities." + std::to_string(i)).c_str(), "Number");
      p.file_priorities.push_back((boost::uint8_t) priority->IntegerValue());
    }
  }

  if (HAS_KEY(obj, "trackerId")) {
    GET_KEY_WITH_CHECK(obj, "trackerId", trackerid, IsString, "trackerId", "String");
    p.trackerid = std::string(*Nan::Utf8String(trackerid));
  }

  if (HAS_KEY(obj, "url")) {
    GET_KEY_WITH_CHECK(obj, "url", url, IsString, "url", "String");
    p.url = std::string(*Nan::Utf8String(url));
  }

  if (HAS_KEY(obj, "uuid")) {
    GET_KEY_WITH_CHECK(obj, "uuid", uuid, IsString, "uuid", "String");
    p.uuid = std::string(*Nan::Utf8String(uuid));
  }

  if (HAS_KEY(obj, "sourceFeedURL")) {
    GET_KEY_WITH_CHECK(obj, "sourceFeedURL", url, IsString, "sourceFeedURL", "String");
    p.source_feed_url = std::string(*Nan::Utf8String(url));
  }

  if (HAS_KEY(obj, "flags")) {
    GET_KEY_WITH_CHECK(obj, "flags", flags, IsNumber, "flags", "Number");
    p.flags = (boost::uint64_t) flags->IntegerValue();
  }

  if (HAS_KEY(obj, "infoHash")) {
    v8::Local<v8::Value> data = Nan::Get(obj, Nan::New("infoHash").ToLocalChecked()).ToLocalChecked();
    if (!node::Buffer::HasInstance(data)) {
      THROW_TYPE_ERROR_RETURN("infoHash", "Buffer");
    }
    if (node::Buffer::Length(data) != 20) {
      Nan::ThrowTypeError("Property infoHash should have exactly 20 bytes");
      return 1;
    }
    p.info_hash = libtorrent::sha1_hash(node::Buffer::Data(data));
  }

  if (HAS_KEY(obj, "maxUploads")) {
    GET_KEY_WITH_CHECK(obj, "maxUploads", value, IsNumber, "maxUploads", "Number");
    p.max_uploads = (boost::uint64_t) value->IntegerValue();
  }

  if (HAS_KEY(obj, "maxConnections")) {
    GET_KEY_WITH_CHECK(obj, "maxConnections", value, IsNumber, "maxConnections", "Number");
    p.max_connections = (boost::uint64_t) value->IntegerValue();
  }

  if (HAS_KEY(obj, "uploadLimit")) {
    GET_KEY_WITH_CHECK(obj, "uploadLimit", value, IsNumber, "uploadLimit", "Number");
    p.upload_limit = (boost::uint64_t) value->IntegerValue();
  }

  if (HAS_KEY(obj, "downloadLimit")) {
    GET_KEY_WITH_CHECK(obj, "downloadLimit", value, IsNumber, "downloadLimit", "Number");
    p.download_limit = (boost::uint64_t) value->IntegerValue();
  }

  return 0;
}

} // namespace libtorrent_rasterbar
