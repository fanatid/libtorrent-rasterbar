#include <libtorrent/extensions/smart_ban.hpp>
#include <libtorrent/extensions/ut_metadata.hpp>
#include <libtorrent/extensions/ut_pex.hpp>
#include <libtorrent-rasterbar/add_torrent_params.h>
#include <libtorrent-rasterbar/alert.h>
#include <libtorrent-rasterbar/extensions.h>
#include <libtorrent-rasterbar/session.h>
#include <libtorrent-rasterbar/settings_pack.h>
#include <libtorrent-rasterbar/torrent_handle.h>
#include <libtorrent-rasterbar/macros.h>

#include <boost/bind.hpp>
#include <boost/function.hpp>

namespace libtorrent_rasterbar {

Nan::Persistent<v8::FunctionTemplate> Session::prototype;
Nan::Persistent<v8::Function> Session::constructor;

v8::Local<v8::Function> Session::Init() {
  Nan::EscapableHandleScope scope;

  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("Session").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  Nan::SetPrototypeMethod(tpl, "abort", Abort);
  Nan::SetPrototypeMethod(tpl, "addTorrent", AddTorrent);
  Nan::SetPrototypeMethod(tpl, "asyncAddTorrent", AsyncAddTorrent);
#ifndef TORRENT_DISABLE_EXTENSIONS
  Nan::SetPrototypeMethod(tpl, "addExtension", AddExtension);
#endif // TORRENT_DISABLE_EXTENSIONS
  Nan::SetPrototypeMethod(tpl, "popAlerts", PopAlerts);
  Nan::SetPrototypeMethod(tpl, "setAlertNotify", SetAlertNotify);

  v8::Local<v8::Function> cons = Nan::GetFunction(tpl).ToLocalChecked();
  v8::Local<v8::Object> flags = Nan::New<v8::Object>();
  SET_INTEGER(flags, "ADD_DEFAULT_PLUGINS", libtorrent::session::add_default_plugins);
  SET_INTEGER(flags, "START_DEFAULT_FEATURES", libtorrent::session::start_default_features);
  SET_VALUE(cons, "flags", flags);

  Session::prototype.Reset(tpl);
  Session::constructor.Reset(cons);

  return scope.Escape(cons);
}

NAN_METHOD(Session::New) {
  if (!info.IsConstructCall()) return;

  boost::shared_ptr<libtorrent::session> session;
  if (info.Length() > 0) {
    ARGUMENTS_REQUIRE_INSTANCE(0, SettingsPack, obj_pack);
    if (info.Length() > 1) {
      ARGUMENTS_REQUIRE_NUMBER(1, flags);
      session = boost::shared_ptr<libtorrent::session>(new libtorrent::session(obj_pack->pack, flags));
    } else {
      session = boost::shared_ptr<libtorrent::session>(new libtorrent::session(obj_pack->pack));
    }
  } else {
    session = boost::shared_ptr<libtorrent::session>(new libtorrent::session());
  }

  Session* obj = new Session(session);
  obj->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

class AsyncAbort : public Nan::AsyncWorker {
 public:
  boost::shared_ptr<libtorrent::session> session;

  explicit AsyncAbort(boost::shared_ptr<libtorrent::session> session, v8::Local<v8::Function> fn)
      : Nan::AsyncWorker(new Nan::Callback(fn)), session(session) {}

  void Execute() {
    // create `session_proxy` and wait `session` thread termination in destructor
    session->abort();
  }

  void HandleOKCallback() {
    v8::Local<v8::Value> argv[] = { Nan::Null() };
    callback->Call(1, argv);
  }
};

NAN_METHOD(Session::Abort) {
  ARGUMENTS_REQUIRE_FUNCTION(0, callback);

  Session* obj = Nan::ObjectWrap::Unwrap<Session>(info.Holder());
  AsyncQueueWorker(new AsyncAbort(obj->session, callback));
}

NAN_METHOD(Session::AddTorrent) {
  Session* obj = Nan::ObjectWrap::Unwrap<Session>(info.Holder());

  ARGUMENTS_OPTIONAL_OBJECT(0, arg0, Nan::New<v8::Object>());
  libtorrent::add_torrent_params p;
  if (AddTorrentParamsFromObject(arg0, p) != 0) return;

  boost::system::error_code ec;
  libtorrent::torrent_handle th = obj->session->add_torrent(p, ec);
  if (ec != boost::system::errc::success) {
    return Nan::ThrowError(ec.message().c_str());
  }

  info.GetReturnValue().Set(TorrentHandle::FromTorrentHandle(th));
}

NAN_METHOD(Session::AsyncAddTorrent) {
  Session* obj = Nan::ObjectWrap::Unwrap<Session>(info.Holder());

  ARGUMENTS_OPTIONAL_OBJECT(0, arg0, Nan::New<v8::Object>());
  libtorrent::add_torrent_params p;
  if (AddTorrentParamsFromObject(arg0, p) != 0) return;

  obj->session->async_add_torrent(p);
}

#ifndef TORRENT_DISABLE_EXTENSIONS
NAN_METHOD(Session::AddExtension) {
  Session* obj = Nan::ObjectWrap::Unwrap<Session>(info.Holder());

  if (info[0]->IsString()) {
    std::string name(*Nan::Utf8String(info[0]));
    if (name == "smart_ban") {
      obj->session->add_extension(libtorrent::create_smart_ban_plugin);
    } else if (name == "ut_metadata") {
      obj->session->add_extension(libtorrent::create_ut_metadata_plugin);
    } else if (name == "ut_pex") {
      obj->session->add_extension(libtorrent::create_ut_pex_plugin);
    } else {
      Nan::ThrowError(("Unknow plugin name: " + name).c_str());
    }
    return;
  }

  if (ARGUMENTS_IS_INSTANCE(0, Plugin)) {
    Plugin* ps = Nan::ObjectWrap::Unwrap<Plugin>(info[0]->ToObject());
    obj->session->add_extension(ps->Value());
    return;
  }

  Nan::ThrowTypeError("Argument 0 must be String or Plugin");
}
#endif // TORRENT_DISABLE_EXTENSIONS

NAN_METHOD(Session::PopAlerts) {
  ARGUMENTS_REQUIRE_NUMBER(0, count);
  if (count == 0) return Nan::ThrowRangeError("Argument 0 must be more than zero");

  Session* obj = Nan::ObjectWrap::Unwrap<Session>(info.Holder());
  std::vector<libtorrent::alert*> alerts(count);
  // TODO: mark previous created Alert as not valid
  // At least we should remove pointers!
  obj->session->pop_alerts(&alerts);

  v8::Local<v8::Array> result = Nan::New<v8::Array>();
  for (auto it = alerts.begin(); it != alerts.end(); ++it) {
    Nan::Set(result, result->Length(), Alert::FromAlertPointer(*it));
  }

  info.GetReturnValue().Set(result);
}

void AlertNotify(Session* obj) {
  Nan::HandleScope scope;

  v8::Local<v8::Value> argv[] = { Nan::Null() };
  obj->fnAlertNotify(1, argv);
}

NAN_METHOD(Session::SetAlertNotify) {
  ARGUMENTS_REQUIRE_FUNCTION(0, callback);

  Session* obj = Nan::ObjectWrap::Unwrap<Session>(info.Holder());
  if (obj->fnAlertNotify.IsEmpty()) obj->session->set_alert_notify(boost::bind(AlertNotify, obj));
  obj->fnAlertNotify.Reset(callback);
}

} // namespace libtorrent_rasterbar
