#ifndef NODE_LIBTORRENT_BENCODE_HPP_INCLUDED
#define NODE_LIBTORRENT_BENCODE_HPP_INCLUDED

#include <v8.h>

namespace nodelt {
  v8::Handle<v8::Value> bencode(const v8::Arguments& args);
};

#endif // NODE_LIBTORRENT_BENCODE_HPP_INCLUDED
