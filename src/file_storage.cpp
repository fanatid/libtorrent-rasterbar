#include <v8.h>
#include <node.h>

#include <libtorrent/file_storage.hpp>

#include "file_storage.hpp"

using namespace v8;
using namespace node;


namespace nodelt {
  void FileStorageWrap::Initialize(Handle<Object> target) {
    // Prepare constructor template
    Local<FunctionTemplate> tpl = FunctionTemplate::New(NewInstance);
    tpl->SetClassName(String::NewSymbol("file_storage"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    // Prototype
    tpl->PrototypeTemplate()->Set(String::NewSymbol("is_valid"),
      FunctionTemplate::New(is_valid)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("num_files"),
      FunctionTemplate::New(num_files)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("total_size"),
      FunctionTemplate::New(total_size)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("set_num_pieces"),
      FunctionTemplate::New(set_num_pieces)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("num_pieces"),
      FunctionTemplate::New(num_pieces)->GetFunction());

    target->Set(String::NewSymbol("file_storage"),
      Persistent<Function>::New(tpl->GetFunction()));
  };

  FileStorageWrap::FileStorageWrap() {
    obj_ = new libtorrent::file_storage();
  };

  FileStorageWrap::~FileStorageWrap() {
    delete obj_;
  };

  Handle<Value> FileStorageWrap::NewInstance(const Arguments& args) {
    HandleScope scope;

    if (!args.IsConstructCall())
      return ThrowException(Exception::TypeError(
        String::New("Use the new operator to create instances of this object.")));

    FileStorageWrap* fs = new FileStorageWrap();
    fs->Wrap(args.This());

    return scope.Close(args.This());
  };

  Handle<Value> FileStorageWrap::is_valid(const Arguments& args) {
    HandleScope scope;

    libtorrent::file_storage* fs_;
    fs_ = ObjectWrap::Unwrap<FileStorageWrap>(args.This())->GetWrapped();

    return scope.Close(Boolean::New(fs_->is_valid()));
  };

  Handle<Value> FileStorageWrap::num_files(const Arguments& args) {
    HandleScope scope;

    libtorrent::file_storage* fs_;
    fs_ = ObjectWrap::Unwrap<FileStorageWrap>(args.This())->GetWrapped();

    return scope.Close(Integer::New(fs_->num_files()));
  };

  Handle<Value> FileStorageWrap::total_size(const Arguments& args) {
    HandleScope scope;

    libtorrent::file_storage* fs_;
    fs_ = ObjectWrap::Unwrap<FileStorageWrap>(args.This())->GetWrapped();

    return scope.Close(Integer::New(fs_->total_size()));
  };

  Handle<Value> FileStorageWrap::set_num_pieces(const Arguments& args) {
    HandleScope scope;

    libtorrent::file_storage* fs_;
    fs_ = ObjectWrap::Unwrap<FileStorageWrap>(args.This())->GetWrapped();
    fs_->set_num_pieces(args[0]->IntegerValue());

    return scope.Close(Undefined());
  };

  Handle<Value> FileStorageWrap::num_pieces(const Arguments& args) {
    HandleScope scope;

    libtorrent::file_storage* fs_;
    fs_ = ObjectWrap::Unwrap<FileStorageWrap>(args.This())->GetWrapped();

    return scope.Close(Integer::New(fs_->num_pieces()));
  };

  void bind_file_storage(Handle<Object> target) {
    FileStorageWrap::Initialize(target);
  };
}; // namespace nodelt