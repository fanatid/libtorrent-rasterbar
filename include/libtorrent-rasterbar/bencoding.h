#ifndef LIBTORRENT_RASTERBAR_BENCODING_H_
#define LIBTORRENT_RASTERBAR_BENCODING_H_

#include <nan.h>
#include <libtorrent/bdecode.hpp>
#include <libtorrent/entry.hpp>

namespace libtorrent_rasterbar {

int BufferToBDecodeNode(v8::Local<v8::Value>, libtorrent::bdecode_node&);
int ValueToEntry(v8::Local<v8::Value>, libtorrent::entry&);
v8::Local<v8::Value> EntryToValue(libtorrent::entry&);

NAN_METHOD(BEncode);
NAN_METHOD(BDecode);

} // namespace libtorrent_rasterbar

#endif // LIBTORRENT_RASTERBAR_BENCODING_H_
