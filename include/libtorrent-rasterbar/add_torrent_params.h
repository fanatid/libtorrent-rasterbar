#ifndef LIBTORRENT_RASTERBAR_ADD_TORRENT_PARAMS_H_
#define LIBTORRENT_RASTERBAR_ADD_TORRENT_PARAMS_H_

#include <nan.h>
#include <libtorrent/add_torrent_params.hpp>

namespace libtorrent_rasterbar {

v8::Local<v8::Object> GetAddTorrentParamsFlags();
int AddTorrentParamsFromObject(v8::Local<v8::Object>, libtorrent::add_torrent_params&);

} // namespace libtorrent_rasterbar

#endif // LIBTORRENT_RASTERBAR_ADD_TORRENT_PARAMS_H_
