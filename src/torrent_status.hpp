#ifndef NODE_LIBTORRENT_TORRENT_STATUS_HPP_INCLUDED
#define NODE_LIBTORRENT_TORRENT_STATUS_HPP_INCLUDED

#include <v8.h>

#include <libtorrent/torrent_handle.hpp>


namespace nodelt {
  v8::Handle<v8::Value> torrent_status_to_object(const libtorrent::torrent_status& st);
};

#endif // NODE_LIBTORRENT_TORRENT_STATUS_HPP_INCLUDED
