#ifndef LIBTORRENT_RASTERBAR_ALERT_H_
#define LIBTORRENT_RASTERBAR_ALERT_H_

#include <nan.h>
#include <libtorrent/alert.hpp>

namespace libtorrent_rasterbar {

class Alert : public Nan::ObjectWrap {
 public:
  static v8::Local<v8::Function> Init();
  static Nan::Persistent<v8::FunctionTemplate> prototype;
  static Nan::Persistent<v8::Function> constructor;

  static v8::Local<v8::Object> FromAlertPointer(libtorrent::alert*);

 private:
  libtorrent::alert* alert;

  static NAN_METHOD(New);
};

} // namespace libtorrent_rasterbar

#endif // LIBTORRENT_RASTERBAR_ALERT_H_
