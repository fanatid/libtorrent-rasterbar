#include <v8.h>
#include <node.h>

#include <libtorrent/add_torrent_params.hpp>
#include <libtorrent/error_code.hpp>
#include <libtorrent/session.hpp>
#include <libtorrent/torrent_handle.hpp>
#include <libtorrent/torrent_info.hpp>

#include "add_torrent_params.hpp"
#include "session.hpp"
#include "torrent_handle.hpp"
#include "torrent_info.hpp"

using namespace v8;
using namespace node;


namespace nodelt {
  void SessionWrap::Initialize(Handle<Object> target) {
    // Prepare constructor template
    Local<FunctionTemplate> tpl = FunctionTemplate::New(NewInstance);
    tpl->SetClassName(String::NewSymbol("session"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    // Prototype
    tpl->PrototypeTemplate()->Set(String::NewSymbol("is_listening"),
      FunctionTemplate::New(is_listening)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("listen_port"),
      FunctionTemplate::New(listen_port)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("listen_on"),
      FunctionTemplate::New(listen_on)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("add_torrent"),
      FunctionTemplate::New(add_torrent)->GetFunction());

    target->Set(String::NewSymbol("session"),
      Persistent<Function>::New(tpl->GetFunction()));
  };

  SessionWrap::SessionWrap() {
    obj_ = new libtorrent::session();
  };

  SessionWrap::~SessionWrap() {
    delete obj_;
  };

  Handle<Value> SessionWrap::NewInstance(const Arguments& args) {
    HandleScope scope;

    if (!args.IsConstructCall())
      return ThrowException(Exception::TypeError(
        String::New("Use the new operator to create instances of this object.")));

    SessionWrap* s = new SessionWrap();
    s->Wrap(args.This());

    return scope.Close(args.This());
  };

  Handle<Value> SessionWrap::is_listening(const Arguments& args) {
    HandleScope scope;

    libtorrent::session* s;
    s = ObjectWrap::Unwrap<SessionWrap>(args.This())->GetWrapped();

    return scope.Close(Boolean::New(s->is_listening()));
  };

  Handle<Value> SessionWrap::listen_port(const Arguments& args) {
    HandleScope scope;

    libtorrent::session* s;
    s = ObjectWrap::Unwrap<SessionWrap>(args.This())->GetWrapped();

    return scope.Close(Integer::New(s->listen_port()));
  };

  Handle<Value> SessionWrap::listen_on(const Arguments& args) {
    HandleScope scope;

    Local<Array> arg0 = Array::Cast(*args[0]);
    std::pair<int, int> port_range = std::make_pair(
      arg0->Get(0)->IntegerValue(), arg0->Get(1)->IntegerValue());
    libtorrent::error_code ec_;
    libtorrent::session* s;
    s = ObjectWrap::Unwrap<SessionWrap>(args.This())->GetWrapped();

    if (args.Length() == 1) {
      s->listen_on(port_range, ec_);
    } else {
      std::string path(*String::Utf8Value(args[1]->ToString()));
      if (args.Length() == 2) {
        s->listen_on(port_range, ec_, path.c_str());
      } else {
        s->listen_on(port_range, ec_, path.c_str(), args[2]->Int32Value());
      }
    }

    return scope.Close(Undefined());
  };

  Handle<Value> SessionWrap::add_torrent(const Arguments& args) {
    HandleScope scope;

    libtorrent::session* s;
    s = ObjectWrap::Unwrap<SessionWrap>(args.This())->GetWrapped();
    libtorrent::torrent_handle th_;
    libtorrent::error_code ec_;

    th_ = s->add_torrent(object_to_add_torrent_params(args[0]->ToObject()), ec_);

    return scope.Close(TorrentHandleWrap::New(th_));
  };

  void bind_session(Handle<Object> target) {
    SessionWrap::Initialize(target);

    // set libtorrent::session::listen_on_flags_t
    Local<Object> listen_on_flags_t = Object::New();
    listen_on_flags_t->Set(String::NewSymbol("listen_reuse_address"),
      Integer::New(libtorrent::session::listen_reuse_address));
    listen_on_flags_t->Set(String::NewSymbol("listen_no_system_port"),
      Integer::New(libtorrent::session::listen_no_system_port));
    target->Set(String::NewSymbol("listen_on_flags_t"), listen_on_flags_t);
  };
}; // namespace nodelt
