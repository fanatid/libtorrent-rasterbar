#ifndef NODE_LIBTORRENT_SESSION_HPP_INCLUDED
#define NODE_LIBTORRENT_SESSION_HPP_INCLUDED

#include <v8.h>
#include <node.h>

#include <libtorrent/session.hpp>


namespace nodelt {
  class SessionWrap: public node::ObjectWrap {
    public:
      static void Initialize(v8::Handle<v8::Object> target);
      libtorrent::session* GetWrapped() const { return s_; };

    private:
      SessionWrap();
      ~SessionWrap();
      static v8::Handle<v8::Value> New(const v8::Arguments& args);

      // Wrapped methods

      // Wrapped object
      libtorrent::session* s_;
  };
};

#endif // NODE_LIBTORRENT_SESSION_HPP_INCLUDED
