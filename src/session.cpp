#include <v8.h>
#include <node.h>

#include <libtorrent/add_torrent_params.hpp>
#include <libtorrent/error_code.hpp>
#include <libtorrent/fingerprint.hpp>
#include <libtorrent/lazy_entry.hpp>
#include <libtorrent/session.hpp>
#include <libtorrent/torrent_handle.hpp>
#include <libtorrent/torrent_info.hpp>

#include "add_torrent_params.hpp"
#include "entry.hpp"
#include "fingerprint.hpp"
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
    tpl->PrototypeTemplate()->Set(String::NewSymbol("save_state"),
      FunctionTemplate::New(save_state)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("load_state"),
      FunctionTemplate::New(load_state)->GetFunction());

    tpl->PrototypeTemplate()->Set(String::NewSymbol("add_torrent"),
      FunctionTemplate::New(add_torrent)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("async_add_torrent"),
      FunctionTemplate::New(async_add_torrent)->GetFunction());

    tpl->PrototypeTemplate()->Set(String::NewSymbol("pause"),
      FunctionTemplate::New(pause)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("resume"),
      FunctionTemplate::New(resume)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("is_paused"),
      FunctionTemplate::New(is_paused)->GetFunction());

    tpl->PrototypeTemplate()->Set(String::NewSymbol("is_listening"),
      FunctionTemplate::New(is_listening)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("listen_port"),
      FunctionTemplate::New(listen_port)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("listen_on"),
      FunctionTemplate::New(listen_on)->GetFunction());

    target->Set(String::NewSymbol("session"),
      Persistent<Function>::New(tpl->GetFunction()));
  };

  SessionWrap::SessionWrap(Local<Array> args) {
    int args_len = args->Length();
    if (args_len >= 1 && args_len <= 5) {
      libtorrent::fingerprint* print_;
      print_ = ObjectWrap::Unwrap<FingerprintWrap>(args->Get(0)->ToObject())->GetWrapped();
      if (args_len == 1) {
        obj_ = new libtorrent::session(*print_);
        return;
      }
      if (args->Get(1)->IsArray()) {
        Local<Array> arg1 = Array::Cast(*args->Get(0));
        std::pair<int, int> port_range = std::make_pair(
          arg1->Get(0)->IntegerValue(), arg1->Get(1)->IntegerValue());
        if (args_len == 2) {
          obj_ = new libtorrent::session(*print_, port_range);
          return;
        }
        std::string lif(*String::AsciiValue(args->Get(2)->ToString()));
        if (args_len == 3)
          obj_ = new libtorrent::session(*print_, port_range, lif.c_str());
        else if (args_len == 4)
          obj_ = new libtorrent::session(*print_, port_range, lif.c_str(), args->Get(3)->Int32Value());
        else
          obj_ = new libtorrent::session(*print_, port_range, lif.c_str(), args->Get(3)->Int32Value(), args->Get(4)->Int32Value());
      } else {
        if (args_len == 2)
          obj_ = new libtorrent::session(*print_, args->Get(1)->Int32Value());
        else
          obj_ = new libtorrent::session(*print_, args->Get(1)->Int32Value(), args->Get(2)->Int32Value());
      }
    } else {
      obj_ = new libtorrent::session();
    }
  };

  SessionWrap::~SessionWrap() {
    delete obj_;
  };

  Handle<Value> SessionWrap::NewInstance(const Arguments& args) {
    HandleScope scope;

    if (!args.IsConstructCall())
      return ThrowException(Exception::TypeError(
        String::New("Use the new operator to create instances of this object.")));

    Local<Array> data = Array::New();
    for (int i = 0, e = args.Length(); i < e; ++i)
      data->Set(i, args[i]);
    SessionWrap* s = new SessionWrap(data);
    s->Wrap(args.This());

    return scope.Close(args.This());
  };

  Handle<Value> SessionWrap::save_state(const Arguments& args) {
    HandleScope scope;

    libtorrent::session* s_;
    s_ = ObjectWrap::Unwrap<SessionWrap>(args.This())->GetWrapped();
    libtorrent::entry e_;
    if (args.Length() == 1)
      s_->save_state(e_, args[0]->IntegerValue());
    else
      s_->save_state(e_);

    return scope.Close(entry_to_object(e_));
  };

  Handle<Value> SessionWrap::load_state(const Arguments& args) {
    HandleScope scope;

    libtorrent::session* s_;
    s_ = ObjectWrap::Unwrap<SessionWrap>(args.This())->GetWrapped();
    libtorrent::entry e_ = entry_from_object(args[0]);
    // deprecated! need lazy_entry...
    s_->load_state(e_);

    return scope.Close(Undefined());
  };

  Handle<Value> SessionWrap::add_torrent(const Arguments& args) {
    HandleScope scope;

    libtorrent::session* s_;
    s_ = ObjectWrap::Unwrap<SessionWrap>(args.This())->GetWrapped();
    libtorrent::torrent_handle th_;
    libtorrent::error_code ec_;
    th_ = s_->add_torrent(add_torrent_params_from_object(args[0]->ToObject()), ec_);

    return scope.Close(TorrentHandleWrap::New(th_));
  };

  Handle<Value> SessionWrap::async_add_torrent(const Arguments& args) {
    HandleScope scope;

    libtorrent::session* s_;
    s_ = ObjectWrap::Unwrap<SessionWrap>(args.This())->GetWrapped();
    s_->async_add_torrent(add_torrent_params_from_object(args[0]->ToObject()));

    return scope.Close(Undefined());
  };

  Handle<Value> SessionWrap::pause(const Arguments& args) {
    HandleScope scope;

    libtorrent::session* s_;
    s_ = ObjectWrap::Unwrap<SessionWrap>(args.This())->GetWrapped();
    s_->pause();

    return scope.Close(Undefined());
  };

  Handle<Value> SessionWrap::resume(const Arguments& args) {
    HandleScope scope;

    libtorrent::session* s_;
    s_ = ObjectWrap::Unwrap<SessionWrap>(args.This())->GetWrapped();
    s_->resume();
    
    return scope.Close(Undefined());
  };

  Handle<Value> SessionWrap::is_paused(const Arguments& args) {
    HandleScope scope;

    libtorrent::session* s_;
    s_ = ObjectWrap::Unwrap<SessionWrap>(args.This())->GetWrapped();

    return scope.Close(Boolean::New(s_->is_paused()));
  };

  Handle<Value> SessionWrap::is_listening(const Arguments& args) {
    HandleScope scope;

    libtorrent::session* s_;
    s_ = ObjectWrap::Unwrap<SessionWrap>(args.This())->GetWrapped();

    return scope.Close(Boolean::New(s_->is_listening()));
  };

  Handle<Value> SessionWrap::listen_port(const Arguments& args) {
    HandleScope scope;

    libtorrent::session* s_;
    s_ = ObjectWrap::Unwrap<SessionWrap>(args.This())->GetWrapped();

    return scope.Close(Integer::New(s_->listen_port()));
  };

  Handle<Value> SessionWrap::listen_on(const Arguments& args) {
    HandleScope scope;

    Local<Array> arg0 = Array::Cast(*args[0]);
    std::pair<int, int> port_range = std::make_pair(
      arg0->Get(0)->IntegerValue(), arg0->Get(1)->IntegerValue());
    libtorrent::error_code ec_;
    libtorrent::session* s_;
    s_ = ObjectWrap::Unwrap<SessionWrap>(args.This())->GetWrapped();

    if (args.Length() == 1) {
      s_->listen_on(port_range, ec_);
    } else {
      std::string lif(*String::AsciiValue(args[1]->ToString()));
      if (args.Length() == 2) {
        s_->listen_on(port_range, ec_, lif.c_str());
      } else {
        s_->listen_on(port_range, ec_, lif.c_str(), args[2]->Int32Value());
      }
    }

    return scope.Close(Undefined());
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

    // set libtorrent::session::save_state_flags_t
    Local<Object> save_state_flags_t = Object::New();
    save_state_flags_t->Set(String::NewSymbol("save_settings"),
      Integer::New(libtorrent::session::save_settings));
    save_state_flags_t->Set(String::NewSymbol("save_dht_settings"),
      Integer::New(libtorrent::session::save_dht_settings));
    save_state_flags_t->Set(String::NewSymbol("save_dht_state"),
      Integer::New(libtorrent::session::save_dht_state));
    save_state_flags_t->Set(String::NewSymbol("save_proxy"),
      Integer::New(libtorrent::session::save_proxy));
    save_state_flags_t->Set(String::NewSymbol("save_i2p_proxy"),
      Integer::New(libtorrent::session::save_i2p_proxy));
    save_state_flags_t->Set(String::NewSymbol("save_encryption_settings"),
      Integer::New(libtorrent::session::save_encryption_settings));
    save_state_flags_t->Set(String::NewSymbol("save_as_map"),
      Integer::New(libtorrent::session::save_as_map));
    save_state_flags_t->Set(String::NewSymbol("save_feeds"),
      Integer::New(libtorrent::session::save_feeds));
    target->Set(String::NewSymbol("save_state_flags_t"), save_state_flags_t);
  };
}; // namespace nodelt
