#ifndef NODE_LIBTORRENT_CREATE_TORRENT_HPP_INCLUDED
#define NODE_LIBTORRENT_CREATE_TORRENT_HPP_INCLUDED

#include <v8.h>
#include <node.h>

#include <libtorrent/create_torrent.hpp>


namespace nodelt {
  class CreateTorrentWrap: public node::ObjectWrap {
    public:
      static void Initialize(v8::Handle<v8::Object> target);
      libtorrent::create_torrent* GetWrapped() const { return obj_; };

    private:
      CreateTorrentWrap(libtorrent::file_storage& fs);
      ~CreateTorrentWrap();
      static v8::Handle<v8::Value> NewInstance(const v8::Arguments& args);
      static v8::Handle<v8::Value> generate(const v8::Arguments& args);

      // Wrapped methods

      // Wrapped object
      libtorrent::create_torrent* obj_;
  };
};

#endif // NODE_LIBTORRENT_CREATE_TORRENT_HPP_INCLUDED
