#include <libtorrent/extensions/smart_ban.hpp>
#include <libtorrent/extensions/ut_metadata.hpp>
#include <libtorrent/extensions/ut_pex.hpp>
#include <libtorrent-rasterbar/alert.h>
#include <libtorrent-rasterbar/extensions.h>
#include <libtorrent-rasterbar/session.h>
#include <libtorrent-rasterbar/settings_pack.h>
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

#ifndef TORRENT_DISABLE_EXTENSIONS
  Nan::SetPrototypeMethod(tpl, "addExtension", AddExtension);
#endif // TORRENT_DISABLE_EXTENSIONS
  Nan::SetPrototypeMethod(tpl, "popAlerts", PopAlerts);
  Nan::SetPrototypeMethod(tpl, "setAlertNotify", SetAlertNotify);

  v8::Local<v8::Function> cons = Nan::GetFunction(tpl).ToLocalChecked();
  v8::Local<v8::Object> flags = Nan::New<v8::Object>();
  SET_INTEGER(flags, "addDefaultPlugins", libtorrent::session::add_default_plugins);
  SET_INTEGER(flags, "startDefaultfeatures", libtorrent::session::start_default_features);
  SET_VALUE(cons, "flags", Nan::New<v8::Value>(flags));

  Session::prototype.Reset(tpl);
  Session::constructor.Reset(cons);

  return scope.Escape(cons);
}

NAN_METHOD(Session::New) {
  if (!info.IsConstructCall()) return;

  libtorrent::session* session;
  if (info.Length() > 0) {
    ARGUMENTS_REQUIRE_INSTANCE(0, SettingsPack, obj_pack);
    if (info.Length() > 1) {
      ARGUMENTS_REQUIRE_NUMBER(1, flags);
      session = new libtorrent::session(obj_pack->pack, flags);
    } else {
      session = new libtorrent::session(obj_pack->pack);
    }
  } else {
    session = new libtorrent::session();
  }

  Session* obj = new Session(session);
  obj->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
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
  obj->session->pop_alerts(&alerts);

  v8::Local<v8::Array> result = Nan::New<v8::Array>();
  for (auto it = alerts.begin(); it != alerts.end(); ++it) {
    Nan::Set(result, result->Length(), Alert::FromAlertPointer(*it));
  }

  info.GetReturnValue().Set(result);
}

void AlertNotify(Session* obj) {
  Nan::HandleScope scope;

  v8::Local<v8::Function> callback = Nan::New<v8::Function>(obj->fnAlertNotify);
  v8::Local<v8::Value> argv[0] = {};
  Nan::MakeCallback(Nan::Undefined()->ToObject(), callback, 0, argv);
}

NAN_METHOD(Session::SetAlertNotify) {
  ARGUMENTS_REQUIRE_FUNCTION(0, callback);

  Session* obj = Nan::ObjectWrap::Unwrap<Session>(info.Holder());
  if (obj->fnAlertNotify.IsEmpty()) obj->session->set_alert_notify(boost::bind(AlertNotify, obj));
  obj->fnAlertNotify.Reset(callback);
}

} // namespace libtorrent_rasterbar
