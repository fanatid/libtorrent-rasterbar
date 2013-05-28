#include <string>
#include <v8.h>
#include <node.h>

#include <libtorrent/create_torrent.hpp>
#include <libtorrent/file_storage.hpp>

#include "create_torrent.hpp"
#include "entry.hpp"
#include "file_storage.hpp"

using namespace v8;
using namespace node;


namespace nodelt {
  void CreateTorrentWrap::Initialize(Handle<Object> target) {
    // Prepare constructor template
    Local<FunctionTemplate> tpl = FunctionTemplate::New(NewInstance);
    tpl->SetClassName(String::NewSymbol("create_torrent"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    // Prototype
    tpl->PrototypeTemplate()->Set(String::NewSymbol("generate"),
      FunctionTemplate::New(generate)->GetFunction());

    target->Set(String::NewSymbol("create_torrent"),
      Persistent<Function>::New(tpl->GetFunction()));
  };

  CreateTorrentWrap::CreateTorrentWrap(libtorrent::file_storage& fs_) {
    obj_ = new libtorrent::create_torrent(fs_);
  };

  CreateTorrentWrap::~CreateTorrentWrap() {
    delete obj_;
  };

  Handle<Value> CreateTorrentWrap::NewInstance(const Arguments& args) {
    HandleScope scope;

    if (!args.IsConstructCall())
      return ThrowException(Exception::TypeError(
        String::New("Use the new operator to create instances of this object.")));

    FileStorageWrap* fs = ObjectWrap::Unwrap<FileStorageWrap>(args[0]->ToObject());
    CreateTorrentWrap* ct = new CreateTorrentWrap(*fs->GetWrapped());
    ct->Wrap(args.This());

    return scope.Close(args.This());
  };

  Handle<Value> CreateTorrentWrap::generate(const Arguments& args) {
    HandleScope scope;

    CreateTorrentWrap* ct = ObjectWrap::Unwrap<CreateTorrentWrap>(args.This());
    libtorrent::entry entry_ = ct->GetWrapped()->generate();

    return scope.Close(entry_to_object(entry_));
  };

  Handle<Value> add_files(const Arguments& args) {
    HandleScope scope;

    libtorrent::file_storage* fs_;
    std::string path;

    fs_ = ObjectWrap::Unwrap<FileStorageWrap>(args[0]->ToObject())->GetWrapped();
    path = std::string(*String::Utf8Value(args[1]->ToString()));
    if (args.Length() == 2)
      libtorrent::add_files(*fs_, path);
    else
      libtorrent::add_files(*fs_, path, args[2]->ToUint32()->Value());

    return scope.Close(Undefined());
  };

  Handle<Value> set_piece_hashes(const Arguments& args) {
    HandleScope scope;

    libtorrent::create_torrent* ct_;
    std::string path;
    libtorrent::error_code ec_;

    ct_ = ObjectWrap::Unwrap<CreateTorrentWrap>(args[0]->ToObject())->GetWrapped();
    path = std::string(*String::Utf8Value(args[1]->ToString()));
    libtorrent::set_piece_hashes(*ct_, path, ec_);

    return scope.Close(Undefined());
  };

  void bind_create_torrent(v8::Handle<v8::Object> target) {
    CreateTorrentWrap::Initialize(target);

    target->Set(String::NewSymbol("add_files"),
      FunctionTemplate::New(add_files)->GetFunction());
    target->Set(String::NewSymbol("set_piece_hashes"),
      FunctionTemplate::New(set_piece_hashes)->GetFunction());
    };
}; // namespace nodelt
