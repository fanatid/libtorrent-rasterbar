#include <v8.h>
#include <node.h>

#include <libtorrent/file_storage.hpp>

#include "file_storage.hpp"

using namespace v8;
using namespace node;


namespace nodelt {
  Local<Object> file_entry_to_object(const libtorrent::file_entry& e) {
    HandleScope scope;

    Local<Object> obj = Object::New();
    obj->Set(String::NewSymbol("path"), String::New(e.path.c_str()));
    obj->Set(String::NewSymbol("offset"), Integer::New(e.offset));
    obj->Set(String::NewSymbol("size"), Integer::New(e.size));
    obj->Set(String::NewSymbol("file_base"), Integer::New(e.file_base));
    obj->Set(String::NewSymbol("mtime"), Integer::New(e.mtime));
    std::string filehash = libtorrent::to_hex(e.filehash.to_string());
    obj->Set(String::NewSymbol("filehash"), String::New(filehash.c_str()));
    obj->Set(String::NewSymbol("pad_file"), Boolean::New(e.pad_file));
    obj->Set(String::NewSymbol("hidden_attribute"), Boolean::New(e.hidden_attribute));
    obj->Set(String::NewSymbol("executable_attribute"), Boolean::New(e.executable_attribute));
    obj->Set(String::NewSymbol("symlink_attribute"), Boolean::New(e.symlink_attribute));
    obj->Set(String::NewSymbol("symlink_path"), String::New(e.symlink_path.c_str()));
    return scope.Close(obj);
  };

  libtorrent::file_entry file_entry_from_object(Local<Object> obj) {
    libtorrent::file_entry e;

    if (obj->Has(String::NewSymbol("path")))
      e.path = std::string(*String::AsciiValue(obj->Get(String::NewSymbol("path"))));
    if (obj->Has(String::NewSymbol("offset")))
      e.offset = obj->Get(String::NewSymbol("offset"))->IntegerValue();
    if (obj->Has(String::NewSymbol("size")))
      e.size = obj->Get(String::NewSymbol("size"))->IntegerValue();
    if (obj->Has(String::NewSymbol("file_base")))
      e.file_base = obj->Get(String::NewSymbol("file_base"))->IntegerValue();
    if (obj->Has(String::NewSymbol("mtime")))
      e.mtime = obj->Get(String::NewSymbol("mtime"))->IntegerValue();
    if (obj->Has(String::NewSymbol("filehash"))) {
      String::AsciiValue filehash(obj->Get(String::NewSymbol("filehash")));
      libtorrent::from_hex(*filehash, 40, (char*)&e.filehash[0]);
    }
    if (obj->Has(String::NewSymbol("pad_file")))
      e.pad_file = obj->Get(String::NewSymbol("pad_file"))->BooleanValue();
    if (obj->Has(String::NewSymbol("hidden_attribute")))
      e.hidden_attribute = obj->Get(String::NewSymbol("hidden_attribute"))->BooleanValue();
    if (obj->Has(String::NewSymbol("executable_attribute")))
      e.executable_attribute = obj->Get(String::NewSymbol("executable_attribute"))->BooleanValue();
    if (obj->Has(String::NewSymbol("symlink_attribute")))
      e.symlink_attribute = obj->Get(String::NewSymbol("symlink_attribute"))->BooleanValue();
    if (obj->Has(String::NewSymbol("symlink_path")))
      e.symlink_path = std::string(*String::AsciiValue(obj->Get(String::NewSymbol("symlink_path"))));

    return e;
  };

  Local<Object> file_slice_to_object(const libtorrent::file_slice& fs) {
    HandleScope scope;

    Local<Object> ret = Object::New();
    ret->Set(String::NewSymbol("file_index"), Integer::New(fs.file_index));
    ret->Set(String::NewSymbol("offset"), Integer::New(fs.offset));
    ret->Set(String::NewSymbol("size"), Integer::New(fs.size));
    return scope.Close(ret);
  };

  Persistent<Function> FileStorageWrap::constructor;

  void FileStorageWrap::Initialize(Handle<Object> target) {
    Local<FunctionTemplate> tpl = FunctionTemplate::New(NewInstance);
    tpl->SetClassName(String::NewSymbol("file_storage"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    tpl->PrototypeTemplate()->Set(String::NewSymbol("is_valid"),
      FunctionTemplate::New(is_valid)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("add_file"),
      FunctionTemplate::New(add_file)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("num_files"),
      FunctionTemplate::New(num_files)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("at"),
      FunctionTemplate::New(at)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("total_size"),
      FunctionTemplate::New(total_size)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("set_num_pieces"),
      FunctionTemplate::New(set_num_pieces)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("num_pieces"),
      FunctionTemplate::New(num_pieces)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("set_piece_length"),
      FunctionTemplate::New(set_piece_length)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("piece_length"),
      FunctionTemplate::New(piece_length)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("piece_size"),
      FunctionTemplate::New(piece_size)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("set_name"),
      FunctionTemplate::New(set_name)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("rename_file"),
      FunctionTemplate::New(rename_file)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("name"),
      FunctionTemplate::New(name)->GetFunction());

    target->Set(String::NewSymbol("file_storage"),
      Persistent<Function>::New(tpl->GetFunction()));

    constructor = Persistent<Function>::New(tpl->GetFunction());
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

  Local<Object> FileStorageWrap::New(const libtorrent::file_storage& fs) {
    HandleScope scope;

    Local<Object> obj = constructor->NewInstance();
    delete FileStorageWrap::Unwrap(obj);
    ObjectWrap::Unwrap<FileStorageWrap>(obj)->obj_ = new libtorrent::file_storage(fs);

    return scope.Close(obj);
  };

  Handle<Value> FileStorageWrap::add_file(const Arguments& args) {
    HandleScope scope;
    
    libtorrent::file_storage* fs = FileStorageWrap::Unwrap(args.This());
    if (args[0]->IsObject()) {
      fs->add_file(file_entry_from_object(args[0]->ToObject()));
    } else {
      std::string p(*String::AsciiValue(args[0]));
      libtorrent::size_type size(args[1]->IntegerValue());
      if (args.Length() == 3)
        fs->add_file(p, size, args[2]->IntegerValue());
      else
        fs->add_file(p, size);
    }
    return scope.Close(Undefined());
  };

  Handle<Value> FileStorageWrap::is_valid(const Arguments& args) {
    HandleScope scope;
    libtorrent::file_storage* fs = FileStorageWrap::Unwrap(args.This());
    return scope.Close(Boolean::New(fs->is_valid()));
  };

  Handle<Value> FileStorageWrap::num_files(const Arguments& args) {
    HandleScope scope;
    libtorrent::file_storage* fs = FileStorageWrap::Unwrap(args.This());
    return scope.Close(Integer::New(fs->num_files()));
  };

  Handle<Value> FileStorageWrap::at(const Arguments& args) {
    HandleScope scope;
    libtorrent::file_storage* fs = FileStorageWrap::Unwrap(args.This());
    return scope.Close(file_entry_to_object(fs->at(args[0]->IntegerValue())));
  };

  Handle<Value> FileStorageWrap::total_size(const Arguments& args) {
    HandleScope scope;
    libtorrent::file_storage* fs = FileStorageWrap::Unwrap(args.This());
    return scope.Close(Integer::New(fs->total_size()));
  };

  Handle<Value> FileStorageWrap::set_num_pieces(const Arguments& args) {
    HandleScope scope;
    libtorrent::file_storage* fs = FileStorageWrap::Unwrap(args.This());
    fs->set_num_pieces(args[0]->IntegerValue());
    return scope.Close(Undefined());
  };

  Handle<Value> FileStorageWrap::num_pieces(const Arguments& args) {
    HandleScope scope;
    libtorrent::file_storage* fs = FileStorageWrap::Unwrap(args.This());
    return scope.Close(Integer::New(fs->num_pieces()));
  };

  Handle<Value> FileStorageWrap::set_piece_length(const Arguments& args) {
    HandleScope scope;
    FileStorageWrap::Unwrap(args.This())->set_piece_length(args[0]->IntegerValue());
    return scope.Close(Undefined());
  };

  Handle<Value> FileStorageWrap::piece_length(const Arguments& args) {
    HandleScope scope;
    libtorrent::file_storage* fs = FileStorageWrap::Unwrap(args.This());
    return scope.Close(Integer::New(fs->piece_length()));
  };

  Handle<Value> FileStorageWrap::piece_size(const Arguments& args) {
    HandleScope scope;
    libtorrent::file_storage* fs = FileStorageWrap::Unwrap(args.This());
    return scope.Close(Integer::New(fs->piece_size(args[0]->IntegerValue())));
  };

  Handle<Value> FileStorageWrap::set_name(const Arguments& args) {
    HandleScope scope;
    FileStorageWrap::Unwrap(args.This())->set_name(
      std::string(*String::AsciiValue(args[0])));
    return scope.Close(Undefined());
  };

  Handle<Value> FileStorageWrap::rename_file(const Arguments& args) {
    HandleScope scope;
    FileStorageWrap::Unwrap(args.This())->rename_file(
      args[0]->IntegerValue(),
      std::string(*String::AsciiValue(args[1])));
    return scope.Close(Undefined());
  };

  Handle<Value> FileStorageWrap::name(const Arguments& args) {
    HandleScope scope;
    std::string name(FileStorageWrap::Unwrap(args.This())->name());
    return scope.Close(String::New(name.c_str()));
  };


  void bind_file_storage(Handle<Object> target) {
    FileStorageWrap::Initialize(target);
  };
}; // namespace nodelt
