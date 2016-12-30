#include <libtorrent/storage_defs.hpp>
#include <libtorrent-rasterbar/storage_mode.h>
#include <libtorrent-rasterbar/macros.h>

namespace libtorrent_rasterbar {

v8::Local<v8::Object> GetStorageModes() {
  Nan::EscapableHandleScope scope;

  v8::Local<v8::Object> data = Nan::New<v8::Object>();
  SET_INTEGER(data, "ALLOCATE", libtorrent::storage_mode_allocate);
  SET_INTEGER(data, "SPARSE", libtorrent::storage_mode_sparse);

  return scope.Escape(data);
}

} // namespace libtorrent_rasterbar
