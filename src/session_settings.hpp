#ifndef NODE_LIBTORRENT_SESSION_SETTINGS_HPP_INCLUDED
#define NODE_LIBTORRENT_SESSION_SETTINGS_HPP_INCLUDED

#include <v8.h>

#include <libtorrent/session_settings.hpp>


namespace nodelt {
#ifndef TORRENT_DISABLE_DHT
  libtorrent::dht_settings const dht_settings_from_object(v8::Handle<v8::Object> obj);
#endif
};

#endif // NODE_LIBTORRENT_SESSION_SETTINGS_HPP_INCLUDED
