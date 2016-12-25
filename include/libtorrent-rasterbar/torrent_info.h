#ifndef LIBTORRENT_RASTERBAR_TORRENT_INFO_H_
#define LIBTORRENT_RASTERBAR_TORRENT_INFO_H_

#include <nan.h>
#include <libtorrent/torrent_info.hpp>

namespace libtorrent_rasterbar {

class TorrentInfo : public Nan::ObjectWrap {
 public:
  static Nan::Persistent<v8::FunctionTemplate> prototype;
  static Nan::Persistent<v8::Function> constructor;
  static v8::Local<v8::Function> Init();

  boost::shared_ptr<libtorrent::torrent_info> ti;

 private:
  explicit TorrentInfo(boost::shared_ptr<libtorrent::torrent_info> ti) : ti(ti) {};

  static NAN_METHOD(New);
};

} // namespace libtorrent_rasterbar

#endif // LIBTORRENT_RASTERBAR_TORRENT_INFO_H_
