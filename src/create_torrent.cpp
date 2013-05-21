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
  CreateTorrentWrap::CreateTorrentWrap(libtorrent::file_storage& fs) {
    ct_ = new libtorrent::create_torrent(fs);
  };

  CreateTorrentWrap::~CreateTorrentWrap() {
    delete ct_;
  };

  void CreateTorrentWrap::Initialize(Handle<Object> target) {
    // Prepare constructor template
    Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
    tpl->SetClassName(String::NewSymbol("CreateTorrent"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    // Prototype
    tpl->PrototypeTemplate()->Set(String::NewSymbol("generate"),
      FunctionTemplate::New(generate)->GetFunction());

    target->Set(String::NewSymbol("CreateTorrent"),
      Persistent<Function>::New(tpl->GetFunction()));
  };

  bool CreateTorrentWrap::IsInstance(Local<Value> obj) {
    HandleScope scope;

    if (!obj->IsObject())
      return false;
    String::Utf8Value constructor_name(obj->ToObject()->GetConstructorName());
    if (std::string(*constructor_name) != "CreateTorrent")
      return false;
    return true;
  };

  Handle<Value> CreateTorrentWrap::New(const Arguments& args) {
    HandleScope scope;

    if (!args.IsConstructCall())
      return ThrowException(Exception::TypeError(
        String::New("Use the new operator to create instances of this object.")));

    if (args.Length() != 1 || !FileStorageWrap::IsInstance(args[0]))
      return ThrowException(Exception::TypeError(
        String::New("CreateTorrent constructor: bad arguments")));

    FileStorageWrap* fsw = ObjectWrap::Unwrap<FileStorageWrap>(args[0]->ToObject());
    libtorrent::file_storage* fs = fsw->GetWrapped();
    CreateTorrentWrap* w = new CreateTorrentWrap(*fs);
    w->Wrap(args.This());

    return args.This();
  };

  Handle<Value> CreateTorrentWrap::generate(const Arguments& args) {
    HandleScope scope;

    CreateTorrentWrap* w = ObjectWrap::Unwrap<CreateTorrentWrap>(args.This());
    libtorrent::entry entry_ = w->GetWrapped()->generate();

    Local<Object> entry = EntryWrap::constructor->NewInstance();
    ObjectWrap::Unwrap<EntryWrap>(entry)->create_entry(entry_);

    return scope.Close(entry);
  };

  Handle<Value> addFiles(const Arguments& args) {
    HandleScope scope;

    if (args.Length() < 2 || args.Length() > 4)
      return ThrowException(Exception::TypeError(
        String::New("addFiles: bad arguments")));

    if (!FileStorageWrap::IsInstance(args[0]) ||
     !args[1]->IsString() ||
     (args.Length() == 3 && !args[2]->IsNumber()))
      return ThrowException(Exception::TypeError(
        String::New("add_files: bad arguments")));

    FileStorageWrap* fsw = ObjectWrap::Unwrap<FileStorageWrap>(args[0]->ToObject());
    libtorrent::file_storage* fs = fsw->GetWrapped();
    String::Utf8Value path(args[1]->ToString());

    if (args.Length() == 2)
      libtorrent::add_files(*fs, std::string(*path));
    else
      libtorrent::add_files(*fs, std::string(*path), args[2]->ToUint32()->Value());

    return scope.Close(Undefined());
  };

  Handle<Value> setPieceHashes(const Arguments& args) {
    HandleScope scope;

    if (args.Length() != 2 ||
     !CreateTorrentWrap::IsInstance(args[0]) ||
     !args[1]->IsString())
      return ThrowException(Exception::TypeError(
        String::New("setPieceHashes: bad arguments")));

    CreateTorrentWrap* ctw = ObjectWrap::Unwrap<CreateTorrentWrap>(args[0]->ToObject());
    libtorrent::create_torrent* ct = ctw->GetWrapped();
    String::Utf8Value path(args[0]->ToString());
    libtorrent::error_code ec;
    libtorrent::set_piece_hashes(*ct, std::string(*path), ec);

    return scope.Close(Undefined());
  };
}; // namespace nodelt
