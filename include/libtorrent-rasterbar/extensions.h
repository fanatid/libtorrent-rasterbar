#ifndef LIBTORRENT_RASTERBAR_EXTENSIONS_H_
#define LIBTORRENT_RASTERBAR_EXTENSIONS_H_

#ifndef TORRENT_DISABLE_EXTENSIONS

#include <nan.h>
#include <libtorrent/extensions.hpp>

namespace libtorrent_rasterbar {

class Plugin : public Nan::ObjectWrap {
 public:
  static Nan::Persistent<v8::FunctionTemplate> prototype;
  static Nan::Persistent<v8::Function> constructor;
  static v8::Local<v8::Function> Init();

  boost::shared_ptr<libtorrent::plugin> ext;

  void Reset (boost::shared_ptr<libtorrent::plugin> _ext) { ext = _ext; }
  boost::shared_ptr<libtorrent::plugin> Value () { return ext; }

 private:
  static NAN_METHOD(New);
};

} // namespace libtorrent_rasterbar

#endif // TORRENT_DISABLE_EXTENSIONS

#endif // LIBTORRENT_RASTERBAR_EXTENSIONS_H_
