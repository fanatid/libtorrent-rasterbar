#include <node.h>
#include <v8.h>

#include "bencode.hpp"
#include "create_torrent.hpp"
#include "entry.hpp"
#include "file_storage.hpp"
#include "version.hpp"

using namespace v8;

void Initialize(Handle<Object> target) {
  bind_bencode(target);
  bind_create_torrent(target);
  bind_entry(target);
  bind_file_storage(target);
  bind_version(target);
}

NODE_MODULE(libtorrent, Initialize);
