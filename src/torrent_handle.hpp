#ifndef NODE_LIBTORRENT_TORRENT_HANDLE_HPP_INCLUDED
#define NODE_LIBTORRENT_TORRENT_HANDLE_HPP_INCLUDED

#include <v8.h>
#include <node.h>

#include <libtorrent/torrent_handle.hpp>


namespace nodelt {
  class TorrentHandleWrap: public node::ObjectWrap {
    public:
      static void Initialize(v8::Handle<v8::Object> target);
      static v8::Local<v8::Object> New(const libtorrent::torrent_handle& th);
      static libtorrent::torrent_handle* Unwrap(const v8::Local<v8::Object>& obj) {
        return node::ObjectWrap::Unwrap<TorrentHandleWrap>(obj)->obj_;
      };

    private:
      libtorrent::torrent_handle* obj_;
      TorrentHandleWrap();
      ~TorrentHandleWrap();
      static v8::Persistent<v8::Function> constructor;
      static v8::Handle<v8::Value> NewInstance(const v8::Arguments& args);

      static v8::Handle<v8::Value> get_peer_info(const v8::Arguments& args);
      static v8::Handle<v8::Value> status(const v8::Arguments& args);
      static v8::Handle<v8::Value> get_download_queue(const v8::Arguments& args);
      static v8::Handle<v8::Value> file_progress(const v8::Arguments& args);
      static v8::Handle<v8::Value> trackers(const v8::Arguments& args);
      static v8::Handle<v8::Value> replace_trackers(const v8::Arguments& args);
      static v8::Handle<v8::Value> add_tracker(const v8::Arguments& args);
      static v8::Handle<v8::Value> add_url_seed(const v8::Arguments& args);
      static v8::Handle<v8::Value> remove_url_seed(const v8::Arguments& args);
      static v8::Handle<v8::Value> url_seeds(const v8::Arguments& args);
      static v8::Handle<v8::Value> add_http_seed(const v8::Arguments& args);
      static v8::Handle<v8::Value> remove_http_seed(const v8::Arguments& args);
      static v8::Handle<v8::Value> http_seeds(const v8::Arguments& args);
      static v8::Handle<v8::Value> get_torrent_info(const v8::Arguments& args);
      static v8::Handle<v8::Value> set_metadata(const v8::Arguments& args);
      static v8::Handle<v8::Value> is_valid(const v8::Arguments& args);
      static v8::Handle<v8::Value> pause(const v8::Arguments& args);
      static v8::Handle<v8::Value> resume(const v8::Arguments& args);
      static v8::Handle<v8::Value> clear_error(const v8::Arguments& args);
      static v8::Handle<v8::Value> set_priority(const v8::Arguments& args);
      static v8::Handle<v8::Value> super_seeding(const v8::Arguments& args);

      static v8::Handle<v8::Value> auto_managed(const v8::Arguments& args);
      static v8::Handle<v8::Value> queue_position(const v8::Arguments& args);
      static v8::Handle<v8::Value> queue_position_up(const v8::Arguments& args);
      static v8::Handle<v8::Value> queue_position_down(const v8::Arguments& args);
      static v8::Handle<v8::Value> queue_position_top(const v8::Arguments& args);
      static v8::Handle<v8::Value> queue_position_bottom(const v8::Arguments& args);

#ifndef TORRENT_DISABLE_RESOLVE_COUNTRIES
      static v8::Handle<v8::Value> resolve_countries(const v8::Arguments& args);
#endif

      static v8::Handle<v8::Value> add_piece(const v8::Arguments& args);
      static v8::Handle<v8::Value> read_piece(const v8::Arguments& args);
      static v8::Handle<v8::Value> have_piece(const v8::Arguments& args);
      static v8::Handle<v8::Value> set_piece_deadline(const v8::Arguments& args);
      static v8::Handle<v8::Value> reset_piece_deadline(const v8::Arguments& args);
      static v8::Handle<v8::Value> piece_availability(const v8::Arguments& args);
      static v8::Handle<v8::Value> piece_priority(const v8::Arguments& args);
      static v8::Handle<v8::Value> prioritize_pieces(const v8::Arguments& args);
      static v8::Handle<v8::Value> piece_priorities(const v8::Arguments& args);
      static v8::Handle<v8::Value> prioritize_files(const v8::Arguments& args);
      static v8::Handle<v8::Value> file_priorities(const v8::Arguments& args);
      static v8::Handle<v8::Value> file_priority(const v8::Arguments& args);
      static v8::Handle<v8::Value> use_interface(const v8::Arguments& args);
      static v8::Handle<v8::Value> save_resume_data(const v8::Arguments& args);
      static v8::Handle<v8::Value> need_save_resume_data(const v8::Arguments& args);
      static v8::Handle<v8::Value> force_reannounce(const v8::Arguments& args);
#ifndef TORRENT_DISABLE_DHT
      static v8::Handle<v8::Value> force_dht_announce(const v8::Arguments& args);
#endif
      static v8::Handle<v8::Value> scrape_tracker(const v8::Arguments& args);
      static v8::Handle<v8::Value> name(const v8::Arguments& args);
      static v8::Handle<v8::Value> set_upload_mode(const v8::Arguments& args);
      static v8::Handle<v8::Value> set_share_mode(const v8::Arguments& args);
      static v8::Handle<v8::Value> flush_cache(const v8::Arguments& args);
      static v8::Handle<v8::Value> apply_ip_filter(const v8::Arguments& args);
      static v8::Handle<v8::Value> set_upload_limit(const v8::Arguments& args);
      static v8::Handle<v8::Value> upload_limit(const v8::Arguments& args);
      static v8::Handle<v8::Value> set_download_limit(const v8::Arguments& args);
      static v8::Handle<v8::Value> download_limit(const v8::Arguments& args);
      static v8::Handle<v8::Value> set_sequential_download(const v8::Arguments& args);
      static v8::Handle<v8::Value> connect_peer(const v8::Arguments& args);
      static v8::Handle<v8::Value> save_path(const v8::Arguments& args);
      static v8::Handle<v8::Value> set_max_uploads(const v8::Arguments& args);
      static v8::Handle<v8::Value> max_uploads(const v8::Arguments& args);
      static v8::Handle<v8::Value> set_max_connections(const v8::Arguments& args);
      static v8::Handle<v8::Value> max_connections(const v8::Arguments& args);
      static v8::Handle<v8::Value> set_tracker_login(const v8::Arguments& args);
      static v8::Handle<v8::Value> move_storage(const v8::Arguments& args);
      static v8::Handle<v8::Value> info_hash(const v8::Arguments& args);
      static v8::Handle<v8::Value> force_recheck(const v8::Arguments& args);
      static v8::Handle<v8::Value> rename_file(const v8::Arguments& args);
      static v8::Handle<v8::Value> set_ssl_certificate(const v8::Arguments& args);
  };
};

#endif // NODE_LIBTORRENT_TORRENT_HANDLE_HPP_INCLUDED
