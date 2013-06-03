#include <v8.h>
#include <node.h>

#include <libtorrent/fingerprint.hpp>

#include "fingerprint.hpp"

using namespace v8;
using namespace node;


namespace nodelt {
  void FingerprintWrap::Initialize(Handle<Object> target) {
    Local<FunctionTemplate> tpl = FunctionTemplate::New(NewInstance);
    tpl->SetClassName(String::NewSymbol("fingerprint"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    tpl->PrototypeTemplate()->Set(String::NewSymbol("to_string"),
      FunctionTemplate::New(to_string)->GetFunction());

    target->Set(String::NewSymbol("fingerprint"),
      Persistent<Function>::New(tpl->GetFunction()));
  };

  FingerprintWrap::FingerprintWrap(const char* id_string,
    int major, int minor, int revision, int tag) {
    obj_ = new libtorrent::fingerprint(id_string, major, minor, revision, tag);
  };

  FingerprintWrap::~FingerprintWrap() {
    delete obj_;
  };

  Handle<Value> FingerprintWrap::NewInstance(const Arguments& args) {
    HandleScope scope;

    if (!args.IsConstructCall())
      return ThrowException(Exception::TypeError(
        String::New("Use the new operator to create instances of this object.")));

    FingerprintWrap* fp = new FingerprintWrap(
      std::string(*String::AsciiValue(args[0]->ToString())).c_str(),
      args[1]->Int32Value(),
      args[2]->Int32Value(),
      args[3]->Int32Value(),
      args[4]->Int32Value());
    fp->Wrap(args.This());

    libtorrent::fingerprint* fp_ = FingerprintWrap::Unwrap(args.This());
    args.This()->Set(String::NewSymbol("name"),             String::New( fp_->name));
    args.This()->Set(String::NewSymbol("major_version"),    Integer::New(fp_->major_version));
    args.This()->Set(String::NewSymbol("minor_version"),    Integer::New(fp_->minor_version));
    args.This()->Set(String::NewSymbol("revision_version"), Integer::New(fp_->revision_version));
    args.This()->Set(String::NewSymbol("tag_version"),      Integer::New(fp_->tag_version));

    return scope.Close(args.This());
  };

  Handle<Value> FingerprintWrap::to_string(const Arguments& args) {
    HandleScope scope;

    libtorrent::fingerprint* fp = FingerprintWrap::Unwrap(args.This());

    return scope.Close(String::New(fp->to_string().c_str()));
  };


  void bind_fingerprint(Handle<Object> target) {
    FingerprintWrap::Initialize(target);
  };
}; // namespace nodelt
