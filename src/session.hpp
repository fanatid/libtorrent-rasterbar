#ifndef NODE_LIBTORRENT_SESSION_HPP_INCLUDED
#define NODE_LIBTORRENT_SESSION_HPP_INCLUDED

#include <v8.h>
#include <node.h>

#include <libtorrent/session.hpp>


namespace nodelt {
  class SessionWrap: public node::ObjectWrap {
    public:
      static void Initialize(v8::Handle<v8::Object> target);
      static libtorrent::session* Unwrap(const v8::Local<v8::Object>& obj) {
        return node::ObjectWrap::Unwrap<SessionWrap>(obj)->obj_;
      };

    private:
      libtorrent::session* obj_;
      SessionWrap(v8::Local<v8::Array> args = v8::Array::New());
      ~SessionWrap();
      static v8::Handle<v8::Value> NewInstance(const v8::Arguments& args);

      static v8::Handle<v8::Value> save_state(const v8::Arguments& args);
      static v8::Handle<v8::Value> load_state(const v8::Arguments& args);

      static v8::Handle<v8::Value> post_torrent_updates(const v8::Arguments& args);

      static v8::Handle<v8::Value> get_torrents(const v8::Arguments& args);

      static v8::Handle<v8::Value> find_torrent(const v8::Arguments& args);

      static v8::Handle<v8::Value> add_torrent(const v8::Arguments& args);
      static v8::Handle<v8::Value> async_add_torrent(const v8::Arguments& args);

      static v8::Handle<v8::Value> pause(const v8::Arguments& args);
      static v8::Handle<v8::Value> resume(const v8::Arguments& args);
      static v8::Handle<v8::Value> is_paused(const v8::Arguments& args);

      static v8::Handle<v8::Value> status(const v8::Arguments& args);
      static v8::Handle<v8::Value> get_cache_status(const v8::Arguments& args);

      static v8::Handle<v8::Value> get_cache_info(const v8::Arguments& args);

      static v8::Handle<v8::Value> add_feed(const v8::Arguments& args);
      static v8::Handle<v8::Value> remove_feed(const v8::Arguments& args);
      static v8::Handle<v8::Value> get_feeds(const v8::Arguments& args);

#ifndef TORRENT_DISABLE_DHT
      static v8::Handle<v8::Value> start_dht(const v8::Arguments& args);
      static v8::Handle<v8::Value> stop_dht(const v8::Arguments& args);
      static v8::Handle<v8::Value> set_dht_settings(const v8::Arguments& args);
      static v8::Handle<v8::Value> add_dht_node(const v8::Arguments& args);
      static v8::Handle<v8::Value> add_dht_router(const v8::Arguments& args);
      static v8::Handle<v8::Value> is_dht_running(const v8::Arguments& args);
#endif

#ifndef TORRENT_DISABLE_EXTENSIONS
      static v8::Handle<v8::Value> add_extension(const v8::Arguments& args);
#endif

#ifndef TORRENT_DISABLE_GEO_IP
      static v8::Handle<v8::Value> load_asnum_db(const v8::Arguments& args);
      static v8::Handle<v8::Value> load_country_db(const v8::Arguments& args);
#endif

      static v8::Handle<v8::Value> set_ip_filter(const v8::Arguments& args);
      static v8::Handle<v8::Value> get_ip_filter(const v8::Arguments& args);

      static v8::Handle<v8::Value> set_peer_id(const v8::Arguments& args);
      static v8::Handle<v8::Value> id(const v8::Arguments& args);

      static v8::Handle<v8::Value> is_listening(const v8::Arguments& args);
      static v8::Handle<v8::Value> listen_port(const v8::Arguments& args);
      static v8::Handle<v8::Value> listen_on(const v8::Arguments& args);

      static v8::Handle<v8::Value> remove_torrent(const v8::Arguments& args);

      static v8::Handle<v8::Value> set_settings(const v8::Arguments& args);
      static v8::Handle<v8::Value> settings(const v8::Arguments& args);

      static v8::Handle<v8::Value> set_proxy(const v8::Arguments& args);
      static v8::Handle<v8::Value> proxy(const v8::Arguments& args);

#if TORRENT_USE_I2P
      static v8::Handle<v8::Value> set_i2p_proxy(const v8::Arguments& args);
      static v8::Handle<v8::Value> i2p_proxy(const v8::Arguments& args);
#endif

      static v8::Handle<v8::Value> pop_alert(const v8::Arguments& args);
      static v8::Handle<v8::Value> pop_alerts(const v8::Arguments& args);
      static v8::Handle<v8::Value> set_alert_mask(const v8::Arguments& args);
      static v8::Handle<v8::Value> wait_for_alert(const v8::Arguments& args);

      static v8::Handle<v8::Value> start_lsd(const v8::Arguments& args);
      static v8::Handle<v8::Value> start_natpmp(const v8::Arguments& args);
      static v8::Handle<v8::Value> start_upnp(const v8::Arguments& args);

      static v8::Handle<v8::Value> stop_lsd(const v8::Arguments& args);
      static v8::Handle<v8::Value> stop_natpmp(const v8::Arguments& args);
      static v8::Handle<v8::Value> stop_upnp(const v8::Arguments& args);
  };
};

#endif // NODE_LIBTORRENT_SESSION_HPP_INCLUDED
