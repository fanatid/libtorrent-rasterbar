#ifndef LIBTORRENT_RASTERBAR_TORRENT_HANDLE_H_
#define LIBTORRENT_RASTERBAR_TORRENT_HANDLE_H_

#include <nan.h>
#include <libtorrent/torrent_handle.hpp>

namespace libtorrent_rasterbar {

class TorrentHandle : public Nan::ObjectWrap {
 public:
  static Nan::Persistent<v8::FunctionTemplate> prototype;
  static Nan::Persistent<v8::Function> constructor;
  static v8::Local<v8::Function> Init();
  static v8::Local<v8::Object> FromTorrentHandle(libtorrent::torrent_handle);

  libtorrent::torrent_handle th;

 private:
  static NAN_METHOD(New);

  static NAN_METHOD(IsValid);
};

} // namespace libtorrent_rasterbar

#endif // LIBTORRENT_RASTERBAR_TORRENT_HANDLE_H_
