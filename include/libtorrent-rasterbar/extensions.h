#ifndef LIBTORRENT_RASTERBAR_EXTENSIONS_H_
#define LIBTORRENT_RASTERBAR_EXTENSIONS_H_

#include <nan.h>
#include <libtorrent/extensions.hpp>

namespace libtorrent_rasterbar {

class PluginStorage : public Nan::ObjectWrap {
 public:
  static v8::Local<v8::Function> Init();
  static Nan::Persistent<v8::FunctionTemplate> prototype;
  static Nan::Persistent<v8::Function> constructor;

  void Reset (boost::shared_ptr<libtorrent::plugin> _ext) { ext = _ext; }
  boost::shared_ptr<libtorrent::plugin> Value () { return ext; }

 private:
  boost::shared_ptr<libtorrent::plugin> ext;

  static NAN_METHOD(New);
};

} // namespace libtorrent_rasterbar

#endif
