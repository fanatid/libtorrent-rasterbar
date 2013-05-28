#ifndef NODE_LIBTORRENT_ADD_TORRENT_PARAMS_HPP_INCLUDED
#define NODE_LIBTORRENT_ADD_TORRENT_PARAMS_HPP_INCLUDED

#include <v8.h>

#include <libtorrent/add_torrent_params.hpp>


namespace nodelt {
  libtorrent::add_torrent_params add_torrent_params_from_object(v8::Local<v8::Object> obj);
};

#endif // NODE_LIBTORRENT_ADD_TORRENT_PARAMS_HPP_INCLUDED
