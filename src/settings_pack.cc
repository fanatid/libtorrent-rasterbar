#include <libtorrent-rasterbar/settings_pack.h>
#include <libtorrent-rasterbar/macros.h>

namespace libtorrent_rasterbar {

Nan::Persistent<v8::FunctionTemplate> SettingsPack::prototype;
Nan::Persistent<v8::Function> SettingsPack::constructor;

v8::Local<v8::Function> SettingsPack::Init() {
  Nan::EscapableHandleScope scope;

  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("SettingsPack").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  Nan::SetPrototypeMethod(tpl, "set", Set);
  Nan::SetPrototypeMethod(tpl, "has", Has);
  Nan::SetPrototypeMethod(tpl, "clear", Clear);
  Nan::SetPrototypeMethod(tpl, "get", Get);

  v8::Local<v8::Function> cons = Nan::GetFunction(tpl).ToLocalChecked();
  SettingsPack::prototype.Reset(tpl);
  SettingsPack::constructor.Reset(cons);

  return scope.Escape(cons);
}

v8::Local<v8::Object> SettingsPack::GetStringSettingsInfo() {
  Nan::EscapableHandleScope scope;

  v8::Local<v8::Object> data = Nan::New<v8::Object>();
  SET_INTEGER(data, "offset", 0x0000);
  SET_INTEGER(data, "count", libtorrent::settings_pack::num_string_settings);

  return scope.Escape(data);
}

v8::Local<v8::Object> SettingsPack::GetNumberSettingsInfo() {
  Nan::EscapableHandleScope scope;

  v8::Local<v8::Object> data = Nan::New<v8::Object>();
  SET_INTEGER(data, "offset", 0x4000);
  SET_INTEGER(data, "count", libtorrent::settings_pack::num_int_settings);

  return scope.Escape(data);
}

v8::Local<v8::Object> SettingsPack::GetBooleanSettingsInfo() {
  Nan::EscapableHandleScope scope;

  v8::Local<v8::Object> data = Nan::New<v8::Object>();
  SET_INTEGER(data, "offset", 0x8000);
  SET_INTEGER(data, "count", libtorrent::settings_pack::num_bool_settings);

  return scope.Escape(data);
}

NAN_METHOD(SettingsPack::New) {
  if (!info.IsConstructCall()) return;

  SettingsPack* obj = new SettingsPack();
  obj->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

NAN_METHOD(SettingsPack::Set) {
  ARGUMENTS_REQUIRE_NUMBER(0, name);
  SettingsPack* obj = Nan::ObjectWrap::Unwrap<SettingsPack>(info.Holder());

  switch (name & libtorrent::settings_pack::type_mask) {
    case libtorrent::settings_pack::string_type_base: {
      ARGUMENTS_REQUIRE_STRING(1, val);
      return obj->pack.set_str(name, std::string(*val));
    }

    case libtorrent::settings_pack::int_type_base: {
      ARGUMENTS_REQUIRE_NUMBER(1, val);
      return obj->pack.set_int(name, val);
    }

    case libtorrent::settings_pack::bool_type_base: {
      ARGUMENTS_REQUIRE_BOOLEAN(1, val);
      return obj->pack.set_bool(name, val);
    }

    default: {
      return Nan::ThrowRangeError(("Unknow name" + std::to_string(name)).c_str());
    }
  }
}

NAN_METHOD(SettingsPack::Has) {
  ARGUMENTS_REQUIRE_NUMBER(0, name);
  SettingsPack* obj = Nan::ObjectWrap::Unwrap<SettingsPack>(info.Holder());
  info.GetReturnValue().Set(Nan::New(obj->pack.has_val(name)));
}

NAN_METHOD(SettingsPack::Clear) {
  SettingsPack* obj = Nan::ObjectWrap::Unwrap<SettingsPack>(info.Holder());
  obj->pack.clear();
}

NAN_METHOD(SettingsPack::Get) {
  ARGUMENTS_REQUIRE_NUMBER(0, name);
  SettingsPack* obj = Nan::ObjectWrap::Unwrap<SettingsPack>(info.Holder());

  switch (name & libtorrent::settings_pack::type_mask) {
    case libtorrent::settings_pack::string_type_base: {
      return info.GetReturnValue().Set(Nan::New(obj->pack.get_str(name).c_str()).ToLocalChecked());
    }

    case libtorrent::settings_pack::int_type_base: {
      return info.GetReturnValue().Set(Nan::New(obj->pack.get_int(name)));
    }

    case libtorrent::settings_pack::bool_type_base: {
      return info.GetReturnValue().Set(Nan::New(obj->pack.get_bool(name)));
    }

    default: {
      return Nan::ThrowRangeError(("Unknow name" + std::to_string(name)).c_str());
    }
  }
}

} // namespace libtorrent_rasterbar
