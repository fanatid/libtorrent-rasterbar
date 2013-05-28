#ifndef NODE_LIBTORRENT_TORRENT_INFO_HPP_INCLUDED
#define NODE_LIBTORRENT_TORRENT_INFO_HPP_INCLUDED

#include <v8.h>
#include <node.h>

#include <libtorrent/torrent_info.hpp>


namespace nodelt {
  class TorrentInfoWrap: public node::ObjectWrap {
    public:
      static void Initialize(v8::Handle<v8::Object> target);
      static libtorrent::torrent_info* Unwrap(v8::Local<v8::Object> const& obj) {
        return node::ObjectWrap::Unwrap<TorrentInfoWrap>(obj)->obj_;
      };

    private:
      TorrentInfoWrap(std::string const& filename);
      ~TorrentInfoWrap();
      static v8::Handle<v8::Value> NewInstance(const v8::Arguments& args);

      // Wrapped methods

      // Wrapped object
      libtorrent::torrent_info* obj_;
  };
};

#endif // NODE_LIBTORRENT_TORRENT_INFO_HPP_INCLUDED
