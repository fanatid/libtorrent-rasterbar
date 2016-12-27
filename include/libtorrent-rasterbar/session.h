#ifndef LIBTORRENT_RASTERBAR_SESSION_H_
#define LIBTORRENT_RASTERBAR_SESSION_H_

#include <nan.h>
#include <libtorrent/session.hpp>

namespace libtorrent_rasterbar {

class Session : public Nan::ObjectWrap {
 public:
  static Nan::Persistent<v8::FunctionTemplate> prototype;
  static Nan::Persistent<v8::Function> constructor;
  static v8::Local<v8::Function> Init();

  boost::shared_ptr<libtorrent::session> session;
  Nan::Callback fnAlertNotify;

 private:
  explicit Session(boost::shared_ptr<libtorrent::session> session) : session(session) {};

  static NAN_METHOD(New);

  static NAN_METHOD(Abort);
  static NAN_METHOD(AddTorrent);
  static NAN_METHOD(AsyncAddTorrent);
  static NAN_METHOD(Resume);
  static NAN_METHOD(Pause);
  static NAN_METHOD(IsPaused);
#ifndef TORRENT_DISABLE_EXTENSIONS
  static NAN_METHOD(AddExtension);
#endif // TORRENT_DISABLE_EXTENSIONS
  static NAN_METHOD(PopAlerts);
  static NAN_METHOD(SetAlertNotify);
};

} // namespace libtorrent_rasterbar

#endif // LIBTORRENT_RASTERBAR_SESSION_H_
