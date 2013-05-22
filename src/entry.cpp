#include <v8.h>
#include <node.h>
#include <libtorrent/entry.hpp>
#include "entry.hpp"

using namespace v8;
using namespace node;


namespace nodelt {
  Persistent<Function> EntryWrap::constructor;

  EntryWrap::EntryWrap() {
    entry_ = NULL;
  };

  EntryWrap::~EntryWrap() {
    if (entry_ != NULL)
      delete entry_;
  };

  void EntryWrap::Initialize(Handle<Object> target) {
    // Prepare constructor template
    Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
    tpl->SetClassName(String::NewSymbol("Entry"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    // Prototype

    /*!Entry::
     * 
     * [entry in libtorrent documentation](http://www.rasterbar.com/products/libtorrent/manual.html#entry)
     */
    constructor = Persistent<Function>::New(tpl->GetFunction());
  };

  bool EntryWrap::IsInstance(Local<Value> obj) {
    HandleScope scope;

    if (!obj->IsObject())
      return false;
    String::Utf8Value constructor_name(obj->ToObject()->GetConstructorName());
    if (std::string(*constructor_name) != "Entry")
      return false;
    return true;
  };

  void EntryWrap::create_entry(const libtorrent::entry& entry) {
    entry_ = new libtorrent::entry(entry);
  };

  Handle<Value> EntryWrap::New(const Arguments& args) {
    if (!args.IsConstructCall())
      return ThrowException(Exception::TypeError(
        String::New("Use the new operator to create instances of this object.")));

    if (args.Length() != 0)
      return ThrowException(Exception::Error(
        String::New("Entry constructor: bad arguments")));

    EntryWrap* w = new EntryWrap();
    w->Wrap(args.This());

    return args.This();
  };
}; // namespace nodelt
