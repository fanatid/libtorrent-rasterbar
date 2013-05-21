#ifndef NODE_LIBTORRENT_CREATE_TORRENT_HPP_INCLUDED
#define NODE_LIBTORRENT_CREATE_TORRENT_HPP_INCLUDED

#include <v8.h>
#include <node.h>
#include <libtorrent/create_torrent.hpp>

namespace nodelt {
    class CreateTorrentWrap: public node::ObjectWrap {
      public:
        static void Initialize(v8::Handle<v8::Object> target);
        libtorrent::create_torrent* GetWrapped() const { return ct_; };
        static bool IsInstance(v8::Local<v8::Value> obj);

      private:
        CreateTorrentWrap(libtorrent::file_storage& fs);
        ~CreateTorrentWrap();
        static v8::Handle<v8::Value> New(const v8::Arguments& args);
        static v8::Handle<v8::Value> generate(const v8::Arguments& args);

        // Wrapped methods

        // Wrapped object
        libtorrent::create_torrent* ct_;
    };

    v8::Handle<v8::Value> addFiles(const v8::Arguments& args);
    v8::Handle<v8::Value> setPieceHashes(const v8::Arguments& args);
};

#endif // NODE_LIBTORRENT_CREATE_TORRENT_HPP_INCLUDED
