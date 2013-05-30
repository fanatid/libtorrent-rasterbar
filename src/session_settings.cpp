#include <v8.h>

#include <libtorrent/session_settings.hpp>

#include "session_settings.hpp"

using namespace v8;


namespace nodelt {
#ifndef TORRENT_DISABLE_DHT
  libtorrent::dht_settings const dht_settings_from_object(Handle<Object> obj) {
    libtorrent::dht_settings dht;

    if (obj->Has(String::NewSymbol("max_peers_reply")))
      dht.max_peers_reply = obj->Get(String::NewSymbol("max_peers_reply"))->IntegerValue();
    if (obj->Has(String::NewSymbol("search_branching")))
      dht.search_branching = obj->Get(String::NewSymbol("search_branching"))->IntegerValue();
    if (obj->Has(String::NewSymbol("max_fail_count")))
      dht.max_fail_count = obj->Get(String::NewSymbol("max_fail_count"))->IntegerValue();
    if (obj->Has(String::NewSymbol("max_torrents")))
      dht.max_torrents = obj->Get(String::NewSymbol("max_torrents"))->IntegerValue();
    if (obj->Has(String::NewSymbol("max_dht_items")))
      dht.max_dht_items = obj->Get(String::NewSymbol("max_dht_items"))->IntegerValue();
    if (obj->Has(String::NewSymbol("max_torrent_search_reply")))
      dht.max_torrent_search_reply = obj->Get(String::NewSymbol("max_torrent_search_reply"))->IntegerValue();
    if (obj->Has(String::NewSymbol("restrict_routing_ips")))
      dht.restrict_routing_ips = obj->Get(String::NewSymbol("restrict_routing_ips"))->BooleanValue();
    if (obj->Has(String::NewSymbol("restrict_search_ips")))
      dht.restrict_search_ips = obj->Get(String::NewSymbol("restrict_search_ips"))->BooleanValue();

    return dht;
  };
#endif
};
