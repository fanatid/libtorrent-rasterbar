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
  /*!bencode
   * bencode(entry)
   * These functions will encode data. Takes [Entry](#Entry::) object.
   * [bencode in libtorrent documentation](http://www.rasterbar.com/products/libtorrent/manual.html#bdecode-bencode)
   */
  target->Set(String::NewSymbol("bencode"),
    FunctionTemplate::New(nodelt::bencode)->GetFunction());

  // create_torrent.cpp
  nodelt::CreateTorrentWrap::Initialize(target);
  /*!addFiles
   * addFiles(file_storage, path, [flags])
   * Adds the file specified by path to the [FileStorage](#FileStorage::) object.
   * [add_files in libtorrent documentation](http://www.rasterbar.com/products/libtorrent/make_torrent.html#add-files)
   */
  target->Set(String::NewSymbol("addFiles"),
    FunctionTemplate::New(nodelt::addFiles)->GetFunction());
  /*!setPieceHashes
   * setPieceHashes(create_torrent, path)
   * Read files and set hashes in [CreateTorrent](#CreateTorrent::) object.
   * [set_piece_hashes in libtorrent documentation](http://www.rasterbar.com/products/libtorrent/make_torrent.html#set-piece-hashes)
   */
  target->Set(String::NewSymbol("setPieceHashes"),
    FunctionTemplate::New(nodelt::setPieceHashes)->GetFunction());

  // entry.cpp
  nodelt::EntryWrap::Initialize(target);

  // file_storage.cpp
  nodelt::FileStorageWrap::Initialize(target);

  // session.cpp
  nodelt::SessionWrap::Initialize(target);

  // libtorrent version
  /*!version
   * version
   * Return version rb-libtorrent.
   */
  target->Set(String::NewSymbol("version"),
    String::New(LIBTORRENT_VERSION));
}

NODE_MODULE(libtorrent, Initialize);
