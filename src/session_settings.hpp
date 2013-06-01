#ifndef NODE_LIBTORRENT_SESSION_SETTINGS_HPP_INCLUDED
#define NODE_LIBTORRENT_SESSION_SETTINGS_HPP_INCLUDED

#include <v8.h>

#include <libtorrent/session_settings.hpp>


namespace nodelt {
#ifndef TORRENT_DISABLE_DHT
  libtorrent::dht_settings const dht_settings_from_object(v8::Handle<v8::Object> obj);
#endif

  v8::Local<v8::Object> proxy_settings_to_object(const libtorrent::proxy_settings& s);
  libtorrent::proxy_settings proxy_settings_from_object(v8::Local<v8::Object> obj);

  v8::Local<v8::Object> session_settings_to_object(const libtorrent::session_settings& s);
  libtorrent::session_settings session_settings_from_object(v8::Local<v8::Object> obj);
};

#endif // NODE_LIBTORRENT_SESSION_SETTINGS_HPP_INCLUDED
