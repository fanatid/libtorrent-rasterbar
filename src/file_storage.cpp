#include <v8.h>
#include <node.h>

#include <libtorrent/file_storage.hpp>

#include "file_storage.hpp"

using namespace v8;
using namespace node;


namespace nodelt {
  FileStorageWrap::FileStorageWrap() {
    fs_ = new libtorrent::file_storage();
  };

  FileStorageWrap::~FileStorageWrap() {
    delete fs_;
  };

  void FileStorageWrap::Initialize(Handle<Object> target) {
    // Prepare constructor template
    Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
    tpl->SetClassName(String::NewSymbol("FileStorage"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    // Prototype
    tpl->PrototypeTemplate()->Set(String::NewSymbol("isValid"),
      FunctionTemplate::New(isValid)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("numFiles"),
      FunctionTemplate::New(numFiles)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("totalSize"),
      FunctionTemplate::New(totalSize)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("setNumPieces"),
      FunctionTemplate::New(setNumPieces)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("numPieces"),
      FunctionTemplate::New(numPieces)->GetFunction());

    target->Set(String::NewSymbol("FileStorage"),
      Persistent<Function>::New(tpl->GetFunction()));
  };

  bool FileStorageWrap::IsInstance(Local<Value> obj) {
    if (!obj->IsObject())
      return false;
    String::Utf8Value constructor_name(obj->ToObject()->GetConstructorName());
    if (std::string(*constructor_name) != "FileStorage")
      return false;
    return true;
  };

  Handle<Value> FileStorageWrap::New(const Arguments& args) {
    if (!args.IsConstructCall())
      return ThrowException(Exception::TypeError(
        String::New("Use the new operator to create instances of this object.")));

    FileStorageWrap* w = new FileStorageWrap();
    w->Wrap(args.This());

    return args.This();
  };

  Handle<Value> FileStorageWrap::isValid(const Arguments& args) {
    HandleScope scope;

    FileStorageWrap* w = ObjectWrap::Unwrap<FileStorageWrap>(args.This());
    libtorrent::file_storage* fs = w->GetWrapped();

    return scope.Close(Boolean::New(fs->is_valid()));
  };

  Handle<Value> FileStorageWrap::numFiles(const Arguments& args) {
    HandleScope scope;

    FileStorageWrap* w = ObjectWrap::Unwrap<FileStorageWrap>(args.This());
    libtorrent::file_storage* fs = w->GetWrapped();

    return scope.Close(Number::New(fs->num_files()));
  };

  Handle<Value> FileStorageWrap::totalSize(const Arguments& args) {
    HandleScope scope;

    FileStorageWrap* w = ObjectWrap::Unwrap<FileStorageWrap>(args.This());
    libtorrent::file_storage* fs = w->GetWrapped();

    return scope.Close(Number::New(fs->total_size()));
  };

  Handle<Value> FileStorageWrap::setNumPieces(const Arguments& args) {
    HandleScope scope;

    if (args.Length() != 1 || !args[0]->IsNumber())
      return ThrowException(Exception::TypeError(
        String::New("FileStorage::set_num_pieces: bad arguments")));

    FileStorageWrap* w = ObjectWrap::Unwrap<FileStorageWrap>(args.This());
    libtorrent::file_storage* fs = w->GetWrapped();

    fs->set_num_pieces(args[0]->IntegerValue());

    return scope.Close(Undefined());
  };

  Handle<Value> FileStorageWrap::numPieces(const Arguments& args) {
    HandleScope scope;

    FileStorageWrap* w = ObjectWrap::Unwrap<FileStorageWrap>(args.This());
    libtorrent::file_storage* fs = w->GetWrapped();

    return scope.Close(Number::New(fs->num_pieces()));
  };
}; // namespace nodelt