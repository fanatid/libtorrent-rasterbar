#ifndef NODE_LIBTORRENT_ENTRY_HPP_INCLUDED
#define NODE_LIBTORRENT_ENTRY_HPP_INCLUDED

#include <v8.h>

#include <libtorrent/entry.hpp>


namespace nodelt {
  v8::Local<v8::Value> entry_to_object(const libtorrent::entry& e_);
  libtorrent::entry entry_from_object(v8::Local<v8::Value> obj);
};

#endif // NODE_LIBTORRENT_ENTRY_HPP_INCLUDED
