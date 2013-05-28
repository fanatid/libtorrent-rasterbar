#ifndef NODE_LIBTORRENT_SESSION_HPP_INCLUDED
#define NODE_LIBTORRENT_SESSION_HPP_INCLUDED

#include <v8.h>
#include <node.h>

#include <libtorrent/session.hpp>


namespace nodelt {
  class SessionWrap: public node::ObjectWrap {
    public:
      static void Initialize(v8::Handle<v8::Object> target);
      libtorrent::session* GetWrapped() const { return obj_; };

    private:
      SessionWrap(v8::Local<v8::Array> args = v8::Array::New());
      ~SessionWrap();
      static v8::Handle<v8::Value> NewInstance(const v8::Arguments& args);

      // Wrapped methods
      static v8::Handle<v8::Value> is_listening(const v8::Arguments& args);
      static v8::Handle<v8::Value> listen_port(const v8::Arguments& args);
      static v8::Handle<v8::Value> listen_on(const v8::Arguments& args);
      static v8::Handle<v8::Value> add_torrent(const v8::Arguments& args);

      // Wrapped object
      libtorrent::session* obj_;
  };
};

#endif // NODE_LIBTORRENT_SESSION_HPP_INCLUDED
