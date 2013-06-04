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
    Local<FunctionTemplate> tpl = FunctionTemplate::New(NewInstance);
    tpl->SetClassName(String::NewSymbol("create_torrent"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    tpl->PrototypeTemplate()->Set(String::NewSymbol("generate"),
      FunctionTemplate::New(generate)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("files"),
      FunctionTemplate::New(files)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("set_comment"),
      FunctionTemplate::New(set_comment)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("set_creator"),
      FunctionTemplate::New(set_creator)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("set_hash"),
      FunctionTemplate::New(set_hash)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("set_file_hash"),
      FunctionTemplate::New(set_file_hash)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("add_url_seed"),
      FunctionTemplate::New(add_url_seed)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("add_http_seed"),
      FunctionTemplate::New(add_http_seed)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("add_node"),
      FunctionTemplate::New(add_node)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("add_tracker"),
      FunctionTemplate::New(add_tracker)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("set_priv"),
      FunctionTemplate::New(set_priv)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("num_pieces"),
      FunctionTemplate::New(num_pieces)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("piece_length"),
      FunctionTemplate::New(piece_length)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("piece_size"),
      FunctionTemplate::New(piece_size)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("priv"),
      FunctionTemplate::New(priv)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("set_root_cert"),
      FunctionTemplate::New(set_root_cert)->GetFunction());

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

    CreateTorrentWrap* ct = new CreateTorrentWrap(*FileStorageWrap::Unwrap(args[0]->ToObject()));
    ct->Wrap(args.This());

    return scope.Close(args.This());
  };

  Handle<Value> CreateTorrentWrap::generate(const Arguments& args) {
    HandleScope scope;
    libtorrent::entry e = CreateTorrentWrap::Unwrap(args.This())->generate();
    return scope.Close(entry_to_object(e));
  };

  Handle<Value> CreateTorrentWrap::files(const Arguments& args) {
    HandleScope scope;
    return scope.Close(FileStorageWrap::New(
      CreateTorrentWrap::Unwrap(args.This())->files()));
  };

  Handle<Value> CreateTorrentWrap::set_comment(const Arguments& args) {
    HandleScope scope;
    CreateTorrentWrap::Unwrap(args.This())->set_comment(
      *String::AsciiValue(args[0]));
    return scope.Close(Undefined());
  };

  Handle<Value> CreateTorrentWrap::set_creator(const Arguments& args) {
    HandleScope scope;
    CreateTorrentWrap::Unwrap(args.This())->set_creator(
      *String::AsciiValue(args[0]));
    return scope.Close(Undefined());
  };

  Handle<Value> CreateTorrentWrap::set_hash(const Arguments& args) {
    HandleScope scope;
    libtorrent::sha1_hash h;
    libtorrent::from_hex(*String::AsciiValue(args[1]), 40, (char*)&h[0]);
    CreateTorrentWrap::Unwrap(args.This())->set_hash(args[0]->IntegerValue(), h);
    return scope.Close(Undefined());
  };

  Handle<Value> CreateTorrentWrap::set_file_hash(const Arguments& args) {
    HandleScope scope;
    libtorrent::sha1_hash h;
    libtorrent::from_hex(*String::AsciiValue(args[1]), 40, (char*)&h[0]);
    CreateTorrentWrap::Unwrap(args.This())->set_file_hash(args[0]->IntegerValue(), h);
    return scope.Close(Undefined());
  };

  Handle<Value> CreateTorrentWrap::add_url_seed(const Arguments& args) {
    HandleScope scope;
    CreateTorrentWrap::Unwrap(args.This())->add_url_seed(
      std::string(*String::AsciiValue(args[0])));
    return scope.Close(Undefined());
  };

  Handle<Value> CreateTorrentWrap::add_http_seed(const Arguments& args) {
    HandleScope scope;
    CreateTorrentWrap::Unwrap(args.This())->add_http_seed(
      std::string(*String::AsciiValue(args[0])));
    return scope.Close(Undefined());
  };

  Handle<Value> CreateTorrentWrap::add_node(const Arguments& args) {
    HandleScope scope;
    CreateTorrentWrap::Unwrap(args.This())->add_node(std::make_pair(
      std::string(*String::AsciiValue(args[0])),
      args[1]->IntegerValue()));
    return scope.Close(Undefined());
  };

  Handle<Value> CreateTorrentWrap::add_tracker(const Arguments& args) {
    HandleScope scope;
    libtorrent::create_torrent* ct = CreateTorrentWrap::Unwrap(args.This());
    std::string url(*String::AsciiValue(args[0]));
    if (args.Length() == 2)
      ct->add_tracker(url, args[1]->IntegerValue());
    else
      ct->add_tracker(url);
    return scope.Close(Undefined());
  };

  Handle<Value> CreateTorrentWrap::set_priv(const Arguments& args) {
    HandleScope scope;
    CreateTorrentWrap::Unwrap(args.This())->set_priv(args[0]->BooleanValue());
    return scope.Close(Undefined());
  };

  Handle<Value> CreateTorrentWrap::num_pieces(const Arguments& args) {
    HandleScope scope;
    return scope.Close(Integer::New(
      CreateTorrentWrap::Unwrap(args.This())->num_pieces()));
  };

  Handle<Value> CreateTorrentWrap::piece_length(const Arguments& args) {
    HandleScope scope;
    return scope.Close(Integer::New(
      CreateTorrentWrap::Unwrap(args.This())->piece_length()));
  };

  Handle<Value> CreateTorrentWrap::piece_size(const Arguments& args) {
    HandleScope scope;
    return scope.Close(Integer::New(
      CreateTorrentWrap::Unwrap(args.This())->piece_size(args[0]->IntegerValue())));
  };

  Handle<Value> CreateTorrentWrap::priv(const Arguments& args) {
    HandleScope scope;
    return scope.Close(Boolean::New(
      CreateTorrentWrap::Unwrap(args.This())->priv()));
  };

  Handle<Value> CreateTorrentWrap::set_root_cert(const Arguments& args) {
    HandleScope scope;
    CreateTorrentWrap::Unwrap(args.This())->set_root_cert(
      std::string(*String::AsciiValue(args[0])));
    return scope.Close(Undefined());
  };


  Handle<Value> add_files(const Arguments& args) {
    HandleScope scope;

    libtorrent::file_storage* fs = FileStorageWrap::Unwrap(args[0]->ToObject());
    std::string path(*String::Utf8Value(args[1]->ToString()));
    if (args.Length() == 2)
      libtorrent::add_files(*fs, path);
    else
      libtorrent::add_files(*fs, path, args[2]->ToUint32()->Value());
    return scope.Close(Undefined());
  };

  Handle<Value> set_piece_hashes(const Arguments& args) {
    HandleScope scope;

    libtorrent::create_torrent* ct = CreateTorrentWrap::Unwrap(args[0]->ToObject());
    std::string path(*String::Utf8Value(args[1]->ToString()));
    libtorrent::error_code ec;
    libtorrent::set_piece_hashes(*ct, path, ec);
    return scope.Close(Undefined());
  };

  void bind_create_torrent(v8::Handle<v8::Object> target) {
    CreateTorrentWrap::Initialize(target);

    Local<Object> create_torrent_flags_t = Object::New();
    create_torrent_flags_t->Set(String::NewSymbol("optimize"),
      Integer::New(libtorrent::create_torrent::optimize));
    create_torrent_flags_t->Set(String::NewSymbol("merkle"),
      Integer::New(libtorrent::create_torrent::merkle));
    create_torrent_flags_t->Set(String::NewSymbol("modification_time"),
      Integer::New(libtorrent::create_torrent::modification_time));
    create_torrent_flags_t->Set(String::NewSymbol("symlinks"),
      Integer::New(libtorrent::create_torrent::symlinks));
    create_torrent_flags_t->Set(String::NewSymbol("calculate_file_hashes"),
      Integer::New(libtorrent::create_torrent::calculate_file_hashes));
    target->Set(String::NewSymbol("create_torrent_flags_t"), create_torrent_flags_t);

    target->Set(String::NewSymbol("add_files"),
      FunctionTemplate::New(add_files)->GetFunction());
    target->Set(String::NewSymbol("set_piece_hashes"),
      FunctionTemplate::New(set_piece_hashes)->GetFunction());
    };
}; // namespace nodelt
