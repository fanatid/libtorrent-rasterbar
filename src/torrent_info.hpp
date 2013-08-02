#ifndef NODE_LIBTORRENT_TORRENT_INFO_HPP_INCLUDED
#define NODE_LIBTORRENT_TORRENT_INFO_HPP_INCLUDED

#include <v8.h>
#include <node.h>

#include <libtorrent/torrent_info.hpp>


namespace nodelt {
  class TorrentInfoWrap: public node::ObjectWrap {
    public:
      static void Initialize(v8::Handle<v8::Object> target);
      static v8::Local<v8::Object> New(const libtorrent::torrent_info& ti);
      static libtorrent::torrent_info* Unwrap(const v8::Local<v8::Object>& obj) {
        return node::ObjectWrap::Unwrap<TorrentInfoWrap>(obj)->obj_;
      };

    private:
      libtorrent::torrent_info* obj_;
      TorrentInfoWrap();
      TorrentInfoWrap(const std::string& filename);
      ~TorrentInfoWrap();
      static v8::Persistent<v8::Function> constructor;
      static v8::Handle<v8::Value> NewInstance(const v8::Arguments& args);

      static v8::Handle<v8::Value> remap_files(const v8::Arguments& args);
      static v8::Handle<v8::Value> add_tracker(const v8::Arguments& args);
      static v8::Handle<v8::Value> add_url_seed(const v8::Arguments& args);
      static v8::Handle<v8::Value> add_http_seed(const v8::Arguments& args);
      static v8::Handle<v8::Value> web_seeds(const v8::Arguments& args);

      static v8::Handle<v8::Value> name(const v8::Arguments& args);
      static v8::Handle<v8::Value> comment(const v8::Arguments& args);
      static v8::Handle<v8::Value> creator(const v8::Arguments& args);
      static v8::Handle<v8::Value> total_size(const v8::Arguments& args);
      static v8::Handle<v8::Value> piece_length(const v8::Arguments& args);
      static v8::Handle<v8::Value> num_pieces(const v8::Arguments& args);
      static v8::Handle<v8::Value> info_hash(const v8::Arguments& args);

      static v8::Handle<v8::Value> hash_for_piece(const v8::Arguments& args);
      static v8::Handle<v8::Value> merkle_tree(const v8::Arguments& args);
      static v8::Handle<v8::Value> set_merkle_tree(const v8::Arguments& args);
      static v8::Handle<v8::Value> piece_size(const v8::Arguments& args);

      static v8::Handle<v8::Value> num_files(const v8::Arguments& args);
      static v8::Handle<v8::Value> file_at(const v8::Arguments& args);
      static v8::Handle<v8::Value> files(const v8::Arguments& args);
      static v8::Handle<v8::Value> orig_files(const v8::Arguments& args);
      static v8::Handle<v8::Value> rename_file(const v8::Arguments& args);

      static v8::Handle<v8::Value> priv(const v8::Arguments& args);
      static v8::Handle<v8::Value> trackers(const v8::Arguments& args);

      static v8::Handle<v8::Value> creation_date(const v8::Arguments& args);

      static v8::Handle<v8::Value> add_node(const v8::Arguments& args);
      static v8::Handle<v8::Value> nodes(const v8::Arguments& args);
      static v8::Handle<v8::Value> metadata(const v8::Arguments& args);
      static v8::Handle<v8::Value> metadata_size(const v8::Arguments& args);
      static v8::Handle<v8::Value> map_block(const v8::Arguments& args);
      static v8::Handle<v8::Value> map_file(const v8::Arguments& args);
  };

  v8::Local<v8::Object> announce_entry_to_object(const libtorrent::announce_entry& ae);
  libtorrent::announce_entry announce_entry_from_object(v8::Local<v8::Object> obj);
};

#endif // NODE_LIBTORRENT_TORRENT_INFO_HPP_INCLUDED
