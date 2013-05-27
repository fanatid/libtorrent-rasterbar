#include <v8.h>
#include <node.h>
#include <libtorrent/entry.hpp>
#include "entry.hpp"

using namespace v8;
using namespace node;


namespace nodelt {
  Persistent<Function> EntryWrap::constructor;

  void EntryWrap::Initialize(Handle<Object> target) {
    // Prepare constructor template
    Local<FunctionTemplate> tpl = FunctionTemplate::New(NewInstance);
    tpl->SetClassName(String::NewSymbol("entry"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    // Prototype

    constructor = Persistent<Function>::New(tpl->GetFunction());
  };

  EntryWrap::EntryWrap() {
    obj_ = NULL;
  };

  EntryWrap::~EntryWrap() {
    if (obj_ != NULL)
      delete obj_;
  };

  Handle<Value> EntryWrap::NewInstance(const Arguments& args) {
    HandleScope scope;

    if (!args.IsConstructCall())
      return ThrowException(Exception::TypeError(
        String::New("Use the new operator to create instances of this object.")));

    EntryWrap* w = new EntryWrap();
    w->Wrap(args.This());

    return scope.Close(args.This());
  };

  Local<Object> EntryWrap::New(const libtorrent::entry& entry_) {
    HandleScope scope;

    Local<Object> entry = constructor->NewInstance();
    ObjectWrap::Unwrap<EntryWrap>(entry)->obj_ = new libtorrent::entry(entry_);

    return scope.Close(entry);
  };

  void bind_entry(Handle<Object> target) {
    EntryWrap::Initialize(target);
  };
}; // namespace nodelt
