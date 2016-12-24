#ifndef LIBTORRENT_RASTERBAR_SETTINGS_PACK_H_
#define LIBTORRENT_RASTERBAR_SETTINGS_PACK_H_

#include <nan.h>
#include <libtorrent/settings_pack.hpp>

namespace libtorrent_rasterbar {

class SettingsPack : public Nan::ObjectWrap {
 public:
  static Nan::Persistent<v8::FunctionTemplate> prototype;
  static Nan::Persistent<v8::Function> constructor;
  static v8::Local<v8::Function> Init();

  libtorrent::settings_pack pack;

 private:
  static NAN_METHOD(New);

  static NAN_METHOD(SettingByName);
  static NAN_METHOD(NameForSetting);

  static NAN_METHOD(Set);
  static NAN_METHOD(Has);
  static NAN_METHOD(Clear);
  static NAN_METHOD(Get);
};

} // namespace libtorrent_rasterbar

#endif // LIBTORRENT_RASTERBAR_SETTINGS_PACK_H_
