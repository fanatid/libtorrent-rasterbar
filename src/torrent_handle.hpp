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
      static libtorrent::torrent_handle* Unwrap(v8::Local<v8::Object> const& obj) {
        return node::ObjectWrap::Unwrap<TorrentHandleWrap>(obj)->obj_;
      };

    private:
      TorrentHandleWrap();
      ~TorrentHandleWrap();
      static v8::Persistent<v8::Function> constructor;
      static v8::Handle<v8::Value> NewInstance(const v8::Arguments& args);

      // Wrapped methods
      static v8::Handle<v8::Value> status(const v8::Arguments& args);

      static v8::Handle<v8::Value> set_upload_limit(const v8::Arguments& args);
      static v8::Handle<v8::Value> set_download_limit(const v8::Arguments& args);
      static v8::Handle<v8::Value> upload_limit(const v8::Arguments& args);
      static v8::Handle<v8::Value> download_limit(const v8::Arguments& args);

      // Wrapped object
      libtorrent::torrent_handle* obj_;
  };
};

#endif // NODE_LIBTORRENT_TORRENT_HANDLE_HPP_INCLUDED
