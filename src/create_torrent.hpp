#ifndef NODE_LIBTORRENT_CREATE_TORRENT_HPP_INCLUDED
#define NODE_LIBTORRENT_CREATE_TORRENT_HPP_INCLUDED

#include <v8.h>
#include <node.h>

#include <libtorrent/create_torrent.hpp>


namespace nodelt {
  class CreateTorrentWrap: public node::ObjectWrap {
    public:
      static void Initialize(v8::Handle<v8::Object> target);
      static libtorrent::create_torrent* Unwrap(const v8::Local<v8::Object>& obj) {
        return node::ObjectWrap::Unwrap<CreateTorrentWrap>(obj)->obj_;
      };

    private:
      libtorrent::create_torrent* obj_;
      CreateTorrentWrap(libtorrent::file_storage& fs);
      ~CreateTorrentWrap();
      static v8::Handle<v8::Value> NewInstance(const v8::Arguments& args);

      static v8::Handle<v8::Value> generate(const v8::Arguments& args);
  };
};

#endif // NODE_LIBTORRENT_CREATE_TORRENT_HPP_INCLUDED
