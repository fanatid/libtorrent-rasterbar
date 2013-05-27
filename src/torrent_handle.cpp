#include <v8.h>
#include <node.h>

#include <libtorrent/torrent_handle.hpp>

#include "torrent_handle.hpp"
#include "torrent_status.hpp"


using namespace v8;
using namespace node;


namespace nodelt {
  Persistent<Function> TorrentHandleWrap::constructor;

  void TorrentHandleWrap::Initialize(Handle<Object> target) {
    // Prepare constructor template
    Local<FunctionTemplate> tpl = FunctionTemplate::New(NewInstance);
    tpl->SetClassName(String::NewSymbol("TorrentHandle"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    // Prototype
    tpl->PrototypeTemplate()->Set(String::NewSymbol("status"),
      FunctionTemplate::New(status)->GetFunction());

    tpl->PrototypeTemplate()->Set(String::NewSymbol("set_upload_limit"),
      FunctionTemplate::New(set_upload_limit)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("set_download_limit"),
      FunctionTemplate::New(set_download_limit)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("upload_limit"),
      FunctionTemplate::New(upload_limit)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("download_limit"),
      FunctionTemplate::New(download_limit)->GetFunction());

    constructor = Persistent<Function>::New(tpl->GetFunction());
  };

  TorrentHandleWrap::TorrentHandleWrap() {
    obj_ = NULL;
  };

  TorrentHandleWrap::~TorrentHandleWrap() {
    if (obj_ != NULL)
      delete obj_;
  };

  Handle<Value> TorrentHandleWrap::NewInstance(const v8::Arguments& args) {
    HandleScope scope;

    if (!args.IsConstructCall())
      return ThrowException(Exception::TypeError(
        String::New("Use the new operator to create instances of this object.")));

    TorrentHandleWrap* th = new TorrentHandleWrap();
    th->Wrap(args.This());

    return scope.Close(args.This());
  };

  Local<Object> TorrentHandleWrap::New(const libtorrent::torrent_handle& th_) {
    HandleScope scope;

    Local<Object> th = constructor->NewInstance();
    ObjectWrap::Unwrap<TorrentHandleWrap>(th)->obj_ = new libtorrent::torrent_handle(th_);

    return scope.Close(th);
  };

  Handle<Value> TorrentHandleWrap::status(const Arguments& args) {
    HandleScope scope;

    libtorrent::torrent_handle* th_;
    libtorrent::torrent_status st_;

    th_ = ObjectWrap::Unwrap<TorrentHandleWrap>(args.This())->GetWrapped();
    if (args.Length() == 1) {
      st_ = th_->status(args[0]->IntegerValue());
    } else {
      st_ = th_->status();
    }

    return scope.Close(torrent_status_to_object(st_));
  };

  Handle<Value> TorrentHandleWrap::set_upload_limit(const Arguments& args) {
    HandleScope scope;

    libtorrent::torrent_handle* th_;
    th_ = ObjectWrap::Unwrap<TorrentHandleWrap>(args.This())->GetWrapped();
    th_->set_upload_limit(args[0]->Int32Value());

    return scope.Close(Undefined());
  };

  Handle<Value> TorrentHandleWrap::set_download_limit(const Arguments& args) {
    HandleScope scope;

    libtorrent::torrent_handle* th_;
    th_ = ObjectWrap::Unwrap<TorrentHandleWrap>(args.This())->GetWrapped();
    th_->set_download_limit(args[0]->Int32Value());

    return scope.Close(Undefined());
  };

  Handle<Value> TorrentHandleWrap::upload_limit(const Arguments& args) {
    HandleScope scope;

    libtorrent::torrent_handle* th_;
    th_ = ObjectWrap::Unwrap<TorrentHandleWrap>(args.This())->GetWrapped();

    return scope.Close(Int32::New(th_->upload_limit()));
  };

  Handle<Value> TorrentHandleWrap::download_limit(const Arguments& args) {
    HandleScope scope;

    libtorrent::torrent_handle* th_;
    th_ = ObjectWrap::Unwrap<TorrentHandleWrap>(args.This())->GetWrapped();

    return scope.Close(Int32::New(th_->download_limit()));
  };

  void bind_torrent_handle(Handle<Object> target) {
    TorrentHandleWrap::Initialize(target);

    // set libtorrent::torrent_handle::status_flags_t
    Local<Object> status_flags_t = Object::New();
    status_flags_t->Set(String::NewSymbol("query_distributed_copies"),
      Integer::New(libtorrent::torrent_handle::query_distributed_copies));
    status_flags_t->Set(String::NewSymbol("query_accurate_download_counters"),
      Integer::New(libtorrent::torrent_handle::query_accurate_download_counters));
    status_flags_t->Set(String::NewSymbol("query_last_seen_complete"),
      Integer::New(libtorrent::torrent_handle::query_last_seen_complete));
    status_flags_t->Set(String::NewSymbol("query_pieces"),
      Integer::New(libtorrent::torrent_handle::query_pieces));
    status_flags_t->Set(String::NewSymbol("query_verified_pieces"),
      Integer::New(libtorrent::torrent_handle::query_verified_pieces));
    target->Set(String::NewSymbol("status_flags_t"), status_flags_t);
  };
}; // namespace nodelt
