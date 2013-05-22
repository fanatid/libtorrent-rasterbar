#include <v8.h>
#include <node.h>

#include <libtorrent/session.hpp>

#include "session.hpp"

using namespace v8;
using namespace node;


namespace nodelt {
  SessionWrap::SessionWrap() {
    s_ = new libtorrent::session();
  };

  SessionWrap::~SessionWrap() {
    delete s_;
  };

  void SessionWrap::Initialize(Handle<Object> target) {
    // Prepare constructor template
    Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
    tpl->SetClassName(String::NewSymbol("Session"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    // Prototype

    /*!Session::
     * Session()
     * Returns instance of [Session](#Session::)
     * [session class in libtorrent documentation](http://www.rasterbar.com/products/libtorrent/manual.html#session)
     */
    target->Set(String::NewSymbol("Session"),
      Persistent<Function>::New(tpl->GetFunction()));
  };

  Handle<Value> SessionWrap::New(const Arguments& args) {
    if (!args.IsConstructCall())
      return ThrowException(Exception::TypeError(
        String::New("Use the new operator to create instances of this object.")));

    SessionWrap* w = new SessionWrap();
    w->Wrap(args.This());

    return args.This();
  };
}; // namespace nodelt
