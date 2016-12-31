#ifndef LIBTORRENT_RASTERBAR_ALERT_H_
#define LIBTORRENT_RASTERBAR_ALERT_H_

#include <nan.h>
#include <libtorrent/alert.hpp>

namespace libtorrent_rasterbar {

class Alert : public Nan::ObjectWrap {
 public:
  static Nan::Persistent<v8::FunctionTemplate> prototype;
  static Nan::Persistent<v8::Function> constructor;
  static v8::Local<v8::Function> Init();

  static v8::Local<v8::Object> GetTypes();
  static v8::Local<v8::Object> GetCategories();
  static v8::Local<v8::Object> FromAlertPointer(libtorrent::alert*);

  libtorrent::alert* alert;

 private:
  static NAN_METHOD(New);

  static NAN_METHOD(Timestamp);
  static NAN_METHOD(Type);
  static NAN_METHOD(What);
  static NAN_METHOD(Message);
  static NAN_METHOD(Category);
};

} // namespace libtorrent_rasterbar

#endif // LIBTORRENT_RASTERBAR_ALERT_H_
