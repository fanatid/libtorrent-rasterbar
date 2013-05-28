#include <node.h>
#include <v8.h>

#include <libtorrent/version.hpp>

using namespace v8;


namespace nodelt {
  void bind_add_torrent_params(Handle<Object> target);
  void bind_bencode(Handle<Object> target);
  void bind_create_torrent(Handle<Object> target);
  void bind_entry(Handle<Object> target);
  void bind_file_storage(Handle<Object> target);
  void bind_fingerprint(Handle<Object> target);
  void bind_session(Handle<Object> target);
  void bind_storage(Handle<Object> target);
  void bind_torrent_handle(Handle<Object> target);
  void bind_torrent_info(Handle<Object> target);
  void bind_torrent_status(Handle<Object> target);

  void Initialize(Handle<Object> target) {
    bind_add_torrent_params(target);
    bind_bencode(target);
    bind_create_torrent(target);
    bind_entry(target);
    bind_file_storage(target);
    bind_fingerprint(target);
    bind_session(target);
    bind_storage(target);
    bind_torrent_handle(target);
    bind_torrent_info(target);
    bind_torrent_status(target);

    target->Set(String::NewSymbol("version"),       String::New(LIBTORRENT_VERSION));
    target->Set(String::NewSymbol("version_major"), Integer::New(LIBTORRENT_VERSION_MAJOR));
    target->Set(String::NewSymbol("version_minor"), Integer::New(LIBTORRENT_VERSION_MINOR));
  };
}; // namespace nodelt

NODE_MODULE(libtorrent, nodelt::Initialize);
