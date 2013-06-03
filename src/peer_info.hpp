#ifndef NODE_LIBTORRENT_PEER_INFO_PARAMS_HPP_INCLUDED
#define NODE_LIBTORRENT_PEER_INFO_PARAMS_HPP_INCLUDED

#include <v8.h>

#include <libtorrent/peer_info.hpp>


namespace nodelt {
  v8::Local<v8::Object> peer_info_to_object(const libtorrent::peer_info& pi);
};

#endif // NODE_LIBTORRENT_PEER_INFO_PARAMS_HPP_INCLUDED
