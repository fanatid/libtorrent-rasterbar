#include <node.h>
#include <v8.h>

#include <libtorrent/version.hpp>

#include "bencode.hpp"
#include "create_torrent.hpp"
#include "entry.hpp"
#include "file_storage.hpp"
#include "session.hpp"

using namespace v8;

void Initialize(Handle<Object> target) {
  // bencode.cpp
  target->Set(String::NewSymbol("bencode"),
    FunctionTemplate::New(nodelt::bencode)->GetFunction());

  // create_torrent.cpp
  nodelt::CreateTorrentWrap::Initialize(target);
  target->Set(String::NewSymbol("addFiles"),
    FunctionTemplate::New(nodelt::addFiles)->GetFunction());
  target->Set(String::NewSymbol("setPieceHashes"),
    FunctionTemplate::New(nodelt::setPieceHashes)->GetFunction());

  // entry.cpp
  nodelt::EntryWrap::Initialize(target);

  // file_storage.cpp
  nodelt::FileStorageWrap::Initialize(target);

  // session.cpp
  nodelt::SessionWrap::Initialize(target);

  // libtorrent version
  target->Set(String::NewSymbol("version"),
    String::New(LIBTORRENT_VERSION));
}

NODE_MODULE(libtorrent, Initialize);
