#ifndef LIBTORRENT_RASTERBAR_SESSION_H_
#define LIBTORRENT_RASTERBAR_SESSION_H_

#include <nan.h>
#include <libtorrent/session.hpp>

namespace libtorrent_rasterbar {

class Session : public Nan::ObjectWrap {
 public:
  static v8::Local<v8::Function> Init();
  static Nan::Persistent<v8::FunctionTemplate> prototype;
  static Nan::Persistent<v8::Function> constructor;

 private:
  libtorrent::session* session;

  explicit Session(libtorrent::session* session) : session(session) {};
  ~Session() {
    delete session;
  };

  static NAN_METHOD(New);
  static NAN_METHOD(AddExtension);
};

} // namespace libtorrent_rasterbar

#endif // LIBTORRENT_RASTERBAR_SESSION_H_
