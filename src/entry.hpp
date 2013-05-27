#ifndef NODE_LIBTORRENT_ENTRY_HPP_INCLUDED
#define NODE_LIBTORRENT_ENTRY_HPP_INCLUDED

#include <v8.h>
#include <node.h>

#include <libtorrent/entry.hpp>


namespace nodelt {
  class EntryWrap: public node::ObjectWrap {
    public:
      static void Initialize(v8::Handle<v8::Object> target);
      static v8::Local<v8::Object> New(const libtorrent::entry& entry_);
      libtorrent::entry* GetWrapped() const { return obj_; };
    private:
      EntryWrap();
      ~EntryWrap();
      static v8::Persistent<v8::Function> constructor;
      static v8::Handle<v8::Value> NewInstance(const v8::Arguments& args);

      // Wrapped methods

      // Wrapped object
      libtorrent::entry* obj_;
  };
};

#endif // NODE_LIBTORRENT_ENTRY_HPP_INCLUDED
