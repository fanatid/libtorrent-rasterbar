#include <libtorrent/extensions/smart_ban.hpp>
#include <libtorrent/extensions/ut_metadata.hpp>
#include <libtorrent/extensions/ut_pex.hpp>
#include <libtorrent-rasterbar/extensions.h>
#include <libtorrent-rasterbar/session.h>

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

  Session::prototype.Reset(tpl);
  Session::constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());

  return scope.Escape(Nan::GetFunction(tpl).ToLocalChecked());
}

NAN_METHOD(Session::New) {
  if (!info.IsConstructCall()) return;

  libtorrent::session* session;
  session = new libtorrent::session();

  Session* obj = new Session(session);
  obj->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

#ifndef TORRENT_DISABLE_EXTENSIONS
NAN_METHOD(Session::AddExtension) {
  Session* obj = Nan::ObjectWrap::Unwrap<Session>(info.Holder());

  if (info[0]->IsString()) {
    std::string name(*Nan::Utf8String(info[0]));
    if (name == "smart_ban") obj->session->add_extension(libtorrent::create_smart_ban_plugin);
    if (name == "ut_metadata") obj->session->add_extension(libtorrent::create_ut_metadata_plugin);
    if (name == "ut_pex") obj->session->add_extension(libtorrent::create_ut_pex_plugin);
    return Nan::ThrowError(("Unknow plugin name: " + name).c_str());
  }

  if (info[0]->IsObject()) {
    v8::Local<v8::Object> arg1 = info[0]->ToObject();
    if (Nan::New(PluginStorage::prototype)->HasInstance(arg1)) {
      PluginStorage* ps = Nan::ObjectWrap::Unwrap<PluginStorage>(arg1);
      obj->session->add_extension(ps->Value());
      return;
    }
  }

  Nan::ThrowTypeError("expected String or PluginStorage");
}
#endif // TORRENT_DISABLE_EXTENSIONS

} // namespace libtorrent_rasterbar
