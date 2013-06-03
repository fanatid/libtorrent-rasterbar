#include <v8.h>
#include <node.h>

#include <libtorrent/torrent_handle.hpp>

#include "peer_info.hpp"
#include "torrent_handle.hpp"
#include "torrent_info.hpp"
#include "torrent_status.hpp"


using namespace v8;
using namespace node;


namespace nodelt {
  Persistent<Function> TorrentHandleWrap::constructor;

  void TorrentHandleWrap::Initialize(Handle<Object> target) {
    Local<FunctionTemplate> tpl = FunctionTemplate::New(NewInstance);
    tpl->SetClassName(String::NewSymbol("TorrentHandle"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    tpl->PrototypeTemplate()->Set(String::NewSymbol("get_peer_info"),
      FunctionTemplate::New(get_peer_info)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("status"),
      FunctionTemplate::New(status)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("get_download_queue"),
      FunctionTemplate::New(get_download_queue)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("file_progress"),
      FunctionTemplate::New(file_progress)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("trackers"),
      FunctionTemplate::New(trackers)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("replace_trackers"),
      FunctionTemplate::New(replace_trackers)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("add_tracker"),
      FunctionTemplate::New(add_tracker)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("add_url_seed"),
      FunctionTemplate::New(add_url_seed)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("remove_url_seed"),
      FunctionTemplate::New(remove_url_seed)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("url_seeds"),
      FunctionTemplate::New(url_seeds)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("add_http_seed"),
      FunctionTemplate::New(add_http_seed)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("remove_http_seed"),
      FunctionTemplate::New(remove_http_seed)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("http_seeds"),
      FunctionTemplate::New(http_seeds)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("get_torrent_info"),
      FunctionTemplate::New(get_torrent_info)->GetFunction());

    tpl->PrototypeTemplate()->Set(String::NewSymbol("add_piece"),
      FunctionTemplate::New(add_piece)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("read_piece"),
      FunctionTemplate::New(read_piece)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("have_piece"),
      FunctionTemplate::New(have_piece)->GetFunction());

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

  Local<Object> TorrentHandleWrap::New(const libtorrent::torrent_handle& th) {
    HandleScope scope;

    Local<Object> obj = constructor->NewInstance();
    ObjectWrap::Unwrap<TorrentHandleWrap>(obj)->obj_ = new libtorrent::torrent_handle(th);

    return scope.Close(obj);
  };

  Handle<Value> TorrentHandleWrap::get_peer_info(const Arguments& args) {
    HandleScope scope;

    std::vector<libtorrent::peer_info> res;
    TorrentHandleWrap::Unwrap(args.This())->get_peer_info(res);
    Local<Array> ret = Array::New();
    for (std::vector<libtorrent::peer_info>::iterator
         i(res.begin()), e(res.end()); i != e; ++i)
      ret->Set(ret->Length(), peer_info_to_object(*i));
    return scope.Close(ret);
  };

  Handle<Value> TorrentHandleWrap::status(const Arguments& args) {
    HandleScope scope;

    libtorrent::torrent_handle* th = TorrentHandleWrap::Unwrap(args.This());
    libtorrent::torrent_status st;
    if (args.Length() == 1)
      st = th->status(args[0]->IntegerValue());
    else
      st = th->status();
    return scope.Close(torrent_status_to_object(st));
  };

  Handle<Value> TorrentHandleWrap::get_download_queue(const Arguments& args) {
    HandleScope scope;

    std::vector<libtorrent::partial_piece_info> res;
    TorrentHandleWrap::Unwrap(args.This())->get_download_queue(res);
    Local<Array> ret = Array::New();
    for (std::vector<libtorrent::partial_piece_info>::iterator
         i(res.begin()), e(res.end()); i != e; ++i) {
      Local<Object> obj = Object::New();
      obj->Set(String::NewSymbol("piece_index"), Integer::New(i->piece_index));
      obj->Set(String::NewSymbol("blocks_in_piece"), Integer::New(i->blocks_in_piece));
      obj->Set(String::NewSymbol("finished"), Integer::New(i->piece_index));
      obj->Set(String::NewSymbol("writing"), Integer::New(i->piece_index));
      obj->Set(String::NewSymbol("requested"), Integer::New(i->piece_index));
      Local<Array> blocks = Array::New();
      for (int k = 0; k < i->blocks_in_piece; ++k) {
        Local<Object> block = Object::New();
        block->Set(String::NewSymbol("state"), Uint32::New(i->blocks[k].state));
        block->Set(String::NewSymbol("num_peers"), Uint32::New(i->blocks[k].num_peers));
        block->Set(String::NewSymbol("bytes_progress"), Uint32::New(i->blocks[k].bytes_progress));
        block->Set(String::NewSymbol("block_size"), Uint32::New(i->blocks[k].block_size));
        Local<Array> peer = Array::New();
        peer->Set(0, String::New(i->blocks[k].peer().address().to_string().c_str()));
        peer->Set(1, Integer::New(i->blocks[k].peer().port()));
        block->Set(String::NewSymbol("peer"), peer);
        blocks->Set(blocks->Length(), block);
      }
      obj->Set(String::NewSymbol("blocks"), blocks);
      ret->Set(ret->Length(), obj);
    }
    return scope.Close(ret);
  };

  Handle<Value> TorrentHandleWrap::file_progress(const Arguments& args) {
    HandleScope scope;

    libtorrent::torrent_handle* th = TorrentHandleWrap::Unwrap(args.This());
    std::vector<libtorrent::size_type> res;
    res.reserve(th->get_torrent_info().num_files());
    Local<Array> ret = Array::New();
    if (args.Length() == 1)
      th->file_progress(res, args[0]->IntegerValue());
    else
      th->file_progress(res);
    for (std::vector<libtorrent::size_type>::iterator
         i(res.begin()), e(res.end()); i != e; ++i)
      ret->Set(ret->Length(), Integer::New(*i));

    return scope.Close(ret);
  };

  Handle<Value> TorrentHandleWrap::trackers(const Arguments& args) {
    HandleScope scope;

    std::vector<libtorrent::announce_entry> const res =
      TorrentHandleWrap::Unwrap(args.This())->trackers();
    Local<Array> ret = Array::New();
    for (std::vector<libtorrent::announce_entry>::const_iterator
         i(res.begin()), e(res.end()); i != e; ++i)
      ret->Set(ret->Length(), announce_entry_to_object(*i));
    return scope.Close(ret);
  };

  Handle<Value> TorrentHandleWrap::replace_trackers(const Arguments& args) {
    HandleScope scope;

    std::vector<libtorrent::announce_entry> trackers;
    Local<Array> src = Array::Cast(*args[0]);
    for (uint32_t i = 0, e = src->Length(); i < e; ++i)
        trackers.push_back(announce_entry_from_object(src->Get(i)->ToObject()));
    TorrentHandleWrap::Unwrap(args.This())->replace_trackers(trackers);
    return scope.Close(Undefined());
  };

  Handle<Value> TorrentHandleWrap::add_tracker(const Arguments& args) {
    HandleScope scope;
    TorrentHandleWrap::Unwrap(args.This())->add_tracker(
      announce_entry_from_object(args[0]->ToObject()));
    return scope.Close(Undefined());
  };

  Handle<Value> TorrentHandleWrap::add_url_seed(const Arguments& args) {
    HandleScope scope;
    TorrentHandleWrap::Unwrap(args.This())->add_url_seed(
      std::string(*String::Utf8Value(args[0])));
    return scope.Close(Undefined());
  };

  Handle<Value> TorrentHandleWrap::remove_url_seed(const Arguments& args) {
    HandleScope scope;
    TorrentHandleWrap::Unwrap(args.This())->remove_url_seed(
      std::string(*String::Utf8Value(args[0])));
    return scope.Close(Undefined());
  };

  Handle<Value> TorrentHandleWrap::url_seeds(const Arguments& args) {
    HandleScope scope;

    std::set<std::string> urls = TorrentHandleWrap::Unwrap(args.This())->url_seeds();
    Local<Array> ret = Array::New();
    for (std::set<std::string>::iterator
         i(urls.begin()), e(urls.end()); i != e; ++i)
      ret->Set(ret->Length(), String::New(i->c_str()));
    return scope.Close(ret);
  };

  Handle<Value> TorrentHandleWrap::add_http_seed(const Arguments& args) {
    HandleScope scope;
    TorrentHandleWrap::Unwrap(args.This())->add_http_seed(
      std::string(*String::Utf8Value(args[0])));
    return scope.Close(Undefined());
  };

  Handle<Value> TorrentHandleWrap::remove_http_seed(const Arguments& args) {
    HandleScope scope;
    TorrentHandleWrap::Unwrap(args.This())->remove_http_seed(
      std::string(*String::Utf8Value(args[0])));
    return scope.Close(Undefined());
  };

  Handle<Value> TorrentHandleWrap::http_seeds(const Arguments& args) {
    HandleScope scope;

    std::set<std::string> urls = TorrentHandleWrap::Unwrap(args.This())->http_seeds();
    Local<Array> ret = Array::New();
    for (std::set<std::string>::iterator
         i(urls.begin()), e(urls.end()); i != e; ++i)
      ret->Set(ret->Length(), String::New(i->c_str()));
    return scope.Close(Undefined());
  };

  Handle<Value> TorrentHandleWrap::get_torrent_info(const Arguments& args) {
    HandleScope scope;
    libtorrent::torrent_info ti = TorrentHandleWrap::Unwrap(args.This())->get_torrent_info();
    return scope.Close(TorrentInfoWrap::New(ti));
  };




  Handle<Value> TorrentHandleWrap::add_piece(const Arguments& args) {
    HandleScope scope;

    libtorrent::torrent_handle* th = TorrentHandleWrap::Unwrap(args.This());
    std::string data(*String::AsciiValue(args[1]));
    if (args.Length() == 3)
      th->add_piece(args[0]->IntegerValue(), data.c_str(), args[2]->IntegerValue());
    else
      th->add_piece(args[0]->IntegerValue(), data.c_str());
    return scope.Close(Undefined());
  };

  Handle<Value> TorrentHandleWrap::read_piece(const Arguments& args) {
    HandleScope scope;
    TorrentHandleWrap::Unwrap(args.This())->read_piece(args[0]->IntegerValue());
    return scope.Close(Undefined());
  };

  Handle<Value> TorrentHandleWrap::have_piece(const Arguments& args) {
    HandleScope scope;
    bool ret = TorrentHandleWrap::Unwrap(args.This())->have_piece(args[0]->IntegerValue());
    return scope.Close(Boolean::New(ret));
  };

  Handle<Value> TorrentHandleWrap::set_upload_limit(const Arguments& args) {
    HandleScope scope;

    libtorrent::torrent_handle* th = TorrentHandleWrap::Unwrap(args.This());
    th->set_upload_limit(args[0]->Int32Value());

    return scope.Close(Undefined());
  };

  Handle<Value> TorrentHandleWrap::set_download_limit(const Arguments& args) {
    HandleScope scope;

    libtorrent::torrent_handle* th = TorrentHandleWrap::Unwrap(args.This());
    th->set_download_limit(args[0]->Int32Value());

    return scope.Close(Undefined());
  };

  Handle<Value> TorrentHandleWrap::upload_limit(const Arguments& args) {
    HandleScope scope;

    libtorrent::torrent_handle* th = TorrentHandleWrap::Unwrap(args.This());

    return scope.Close(Int32::New(th->upload_limit()));
  };

  Handle<Value> TorrentHandleWrap::download_limit(const Arguments& args) {
    HandleScope scope;

    libtorrent::torrent_handle* th = TorrentHandleWrap::Unwrap(args.This());

    return scope.Close(Int32::New(th->download_limit()));
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
