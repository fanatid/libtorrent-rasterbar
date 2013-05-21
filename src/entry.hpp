#ifndef NODE_LIBTORRENT_ENTRY_HPP_INCLUDED
#define NODE_LIBTORRENT_ENTRY_HPP_INCLUDED

#include <v8.h>
#include <node.h>
#include <libtorrent/entry.hpp>


namespace nodelt {
  class EntryWrap: public node::ObjectWrap {
    public:
      static void Initialize(v8::Handle<v8::Object> target);
      libtorrent::entry* GetWrapped() const { return entry_; };
      static bool IsInstance(v8::Local<v8::Value> obj);
      static v8::Persistent<v8::Function> constructor;
      void create_entry(const libtorrent::entry& entry);
    private:
      EntryWrap();
      ~EntryWrap();
      static v8::Handle<v8::Value> New(const v8::Arguments& args);

      // Wrapped methods

      // Wrapped object
      libtorrent::entry* entry_;
  };
};

#endif // NODE_LIBTORRENT_ENTRY_HPP_INCLUDED
