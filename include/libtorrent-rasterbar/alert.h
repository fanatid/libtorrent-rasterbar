#ifndef LIBTORRENT_RASTERBAR_ALERT_H_
#define LIBTORRENT_RASTERBAR_ALERT_H_

#include <map>
#include <nan.h>
#include <libtorrent/alert.hpp>

namespace libtorrent_rasterbar {

class Alert : public Nan::ObjectWrap {
 public:
  static Nan::Persistent<v8::FunctionTemplate> prototype;
  static Nan::Persistent<v8::Function> constructor;
  static std::map<int, Nan::Persistent<v8::Function>> constructors;
  static v8::Local<v8::Function> Init();

  static v8::Local<v8::Object> GetAlerts();
  static v8::Local<v8::Object> GetTypes();
  static v8::Local<v8::Object> GetCategories();
  static v8::Local<v8::Object> FromAlertPointer(libtorrent::alert*, v8::Local<v8::Object>);

  static inline void NewAlert(v8::Local<v8::Object> self) {
    Alert* obj = new Alert();
    obj->Wrap(self);
  }

  libtorrent::alert* alert;

 private:
  static NAN_METHOD(New);
  static NAN_METHOD(NewTorrentAlert);
  static NAN_METHOD(NewTorrentAddedAlert);

  static NAN_METHOD(Timestamp);
  static NAN_METHOD(Type);
  static NAN_METHOD(What);
  static NAN_METHOD(Message);
  static NAN_METHOD(Category);

  static NAN_METHOD(TorrentName);
  static NAN_GETTER(GetHandle);
};

} // namespace libtorrent_rasterbar

#endif // LIBTORRENT_RASTERBAR_ALERT_H_
