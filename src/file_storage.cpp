#include <v8.h>
#include <node.h>
#include <libtorrent/file_storage.hpp>
#include "file_storage.hpp"

using namespace v8;
using namespace libtorrent;


FileStorageWrap::FileStorageWrap() {
  fs_ = new file_storage();
};

FileStorageWrap::~FileStorageWrap() {
  delete fs_;
};

void FileStorageWrap::Initialize(Handle<Object> target) {
  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
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

bool FileStorageWrap::IsInstance(Local<Value> obj) {
  if (!obj->IsObject())
    return false;
  String::Utf8Value constructor_name(obj->ToObject()->GetConstructorName());
  if (std::string(*constructor_name) != "file_storage")
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

Handle<Value> FileStorageWrap::is_valid(const Arguments& args) {
  HandleScope scope;

  FileStorageWrap* w = ObjectWrap::Unwrap<FileStorageWrap>(args.This());
  file_storage* fs = w->GetWrapped();

  return scope.Close(Boolean::New(fs->is_valid()));
};

Handle<Value> FileStorageWrap::num_files(const Arguments& args) {
  HandleScope scope;

  FileStorageWrap* w = ObjectWrap::Unwrap<FileStorageWrap>(args.This());
  file_storage* fs = w->GetWrapped();

  return scope.Close(Number::New(fs->num_files()));
};

Handle<Value> FileStorageWrap::total_size(const Arguments& args) {
  HandleScope scope;

  FileStorageWrap* w = ObjectWrap::Unwrap<FileStorageWrap>(args.This());
  file_storage* fs = w->GetWrapped();

  return scope.Close(Number::New(fs->total_size()));
};

Handle<Value> FileStorageWrap::set_num_pieces(const Arguments& args) {
  HandleScope scope;

  if (args.Length() != 1 || !args[0]->IsNumber())
    return ThrowException(Exception::TypeError(
      String::New("file_storage::set_num_pieces: bad arguments")));

  FileStorageWrap* w = ObjectWrap::Unwrap<FileStorageWrap>(args.This());
  file_storage* fs = w->GetWrapped();

  fs->set_num_pieces(args[0]->IntegerValue());

  return scope.Close(Undefined());
};

Handle<Value> FileStorageWrap::num_pieces(const Arguments& args) {
  HandleScope scope;

  FileStorageWrap* w = ObjectWrap::Unwrap<FileStorageWrap>(args.This());
  file_storage* fs = w->GetWrapped();

  return scope.Close(Number::New(fs->num_pieces()));
};

void bind_file_storage(Handle<Object> target) {
  FileStorageWrap::Initialize(target);
}
