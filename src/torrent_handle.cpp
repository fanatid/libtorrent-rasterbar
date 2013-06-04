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
    tpl->PrototypeTemplate()->Set(String::NewSymbol("set_metadata"),
      FunctionTemplate::New(set_metadata)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("is_valid"),
      FunctionTemplate::New(is_valid)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("pause"),
      FunctionTemplate::New(pause)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("resume"),
      FunctionTemplate::New(resume)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("clear_error"),
      FunctionTemplate::New(clear_error)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("set_priority"),
      FunctionTemplate::New(set_priority)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("super_seeding"),
      FunctionTemplate::New(super_seeding)->GetFunction());

    tpl->PrototypeTemplate()->Set(String::NewSymbol("auto_managed"),
      FunctionTemplate::New(auto_managed)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("queue_position"),
      FunctionTemplate::New(queue_position)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("queue_position_up"),
      FunctionTemplate::New(queue_position_up)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("queue_position_down"),
      FunctionTemplate::New(queue_position_down)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("queue_position_top"),
      FunctionTemplate::New(queue_position_top)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("queue_position_bottom"),
      FunctionTemplate::New(queue_position_bottom)->GetFunction());

#ifndef TORRENT_DISABLE_RESOLVE_COUNTRIES
    tpl->PrototypeTemplate()->Set(String::NewSymbol("resolve_countries"),
      FunctionTemplate::New(resolve_countries)->GetFunction());
#endif

    tpl->PrototypeTemplate()->Set(String::NewSymbol("add_piece"),
      FunctionTemplate::New(add_piece)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("read_piece"),
      FunctionTemplate::New(read_piece)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("have_piece"),
      FunctionTemplate::New(have_piece)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("set_piece_deadline"),
      FunctionTemplate::New(set_piece_deadline)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("reset_piece_deadline"),
      FunctionTemplate::New(reset_piece_deadline)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("piece_availability"),
      FunctionTemplate::New(piece_availability)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("piece_priority"),
      FunctionTemplate::New(piece_priority)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("prioritize_pieces"),
      FunctionTemplate::New(prioritize_pieces)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("piece_priorities"),
      FunctionTemplate::New(piece_priorities)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("prioritize_files"),
      FunctionTemplate::New(prioritize_files)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("file_priorities"),
      FunctionTemplate::New(file_priorities)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("file_priority"),
      FunctionTemplate::New(file_priority)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("use_interface"),
      FunctionTemplate::New(use_interface)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("save_resume_data"),
      FunctionTemplate::New(save_resume_data)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("need_save_resume_data"),
      FunctionTemplate::New(need_save_resume_data)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("force_reannounce"),
      FunctionTemplate::New(force_reannounce)->GetFunction());

#ifndef TORRENT_DISABLE_DHT
    tpl->PrototypeTemplate()->Set(String::NewSymbol("force_dht_announce"),
      FunctionTemplate::New(force_dht_announce)->GetFunction());
#endif

    tpl->PrototypeTemplate()->Set(String::NewSymbol("scrape_tracker"),
      FunctionTemplate::New(scrape_tracker)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("name"),
      FunctionTemplate::New(name)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("set_upload_mode"),
      FunctionTemplate::New(set_upload_mode)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("set_share_mode"),
      FunctionTemplate::New(set_share_mode)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("flush_cache"),
      FunctionTemplate::New(flush_cache)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("apply_ip_filter"),
      FunctionTemplate::New(apply_ip_filter)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("set_upload_limit"),
      FunctionTemplate::New(set_upload_limit)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("set_download_limit"),
      FunctionTemplate::New(set_download_limit)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("upload_limit"),
      FunctionTemplate::New(upload_limit)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("download_limit"),
      FunctionTemplate::New(download_limit)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("set_sequential_download"),
      FunctionTemplate::New(set_sequential_download)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("connect_peer"),
      FunctionTemplate::New(connect_peer)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("save_path"),
      FunctionTemplate::New(save_path)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("set_max_uploads"),
      FunctionTemplate::New(set_max_uploads)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("max_uploads"),
      FunctionTemplate::New(max_uploads)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("set_max_connections"),
      FunctionTemplate::New(set_max_connections)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("max_connections"),
      FunctionTemplate::New(max_connections)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("set_tracker_login"),
      FunctionTemplate::New(set_tracker_login)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("move_storage"),
      FunctionTemplate::New(move_storage)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("info_hash"),
      FunctionTemplate::New(info_hash)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("force_recheck"),
      FunctionTemplate::New(force_recheck)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("rename_file"),
      FunctionTemplate::New(rename_file)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("set_ssl_certificate"),
      FunctionTemplate::New(set_ssl_certificate)->GetFunction());

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

  Handle<Value> TorrentHandleWrap::set_metadata(const Arguments& args) {
    HandleScope scope;
    
    std::string md(*String::AsciiValue(args[0]));
    TorrentHandleWrap::Unwrap(args.This())->set_metadata(md.c_str(), md.size());
    return scope.Close(Undefined());
  };

  Handle<Value> TorrentHandleWrap::is_valid(const Arguments& args) {
    HandleScope scope;
    return scope.Close(Boolean::New(
      TorrentHandleWrap::Unwrap(args.This())->is_valid()));
  };

  Handle<Value> TorrentHandleWrap::pause(const Arguments& args) {
    HandleScope scope;
    if (args.Length() == 1)
      TorrentHandleWrap::Unwrap(args.This())->pause(args[0]->IntegerValue());
    else
      TorrentHandleWrap::Unwrap(args.This())->pause();
    return scope.Close(Undefined());
  };

  Handle<Value> TorrentHandleWrap::resume(const Arguments& args) {
    HandleScope scope;
    TorrentHandleWrap::Unwrap(args.This())->resume();
    return scope.Close(Undefined());
  };

  Handle<Value> TorrentHandleWrap::clear_error(const Arguments& args) {
    HandleScope scope;
    TorrentHandleWrap::Unwrap(args.This())->clear_error();
    return scope.Close(Undefined());
  };

  Handle<Value> TorrentHandleWrap::set_priority(const Arguments& args) {
    HandleScope scope;
    TorrentHandleWrap::Unwrap(args.This())->set_priority(args[0]->IntegerValue());
    return scope.Close(Undefined());
  };

  Handle<Value> TorrentHandleWrap::super_seeding(const Arguments& args) {
    HandleScope scope;
    TorrentHandleWrap::Unwrap(args.This())->super_seeding(args[0]->BooleanValue());
    return scope.Close(Undefined());
  };


  Handle<Value> TorrentHandleWrap::auto_managed(const Arguments& args) {
    HandleScope scope;
    TorrentHandleWrap::Unwrap(args.This())->auto_managed(args[0]->BooleanValue());
    return scope.Close(Undefined());
  };

  Handle<Value> TorrentHandleWrap::queue_position(const Arguments& args) {
    HandleScope scope;
    return scope.Close(Integer::New(
      TorrentHandleWrap::Unwrap(args.This())->queue_position()));
  };

  Handle<Value> TorrentHandleWrap::queue_position_up(const Arguments& args) {
    HandleScope scope;
    TorrentHandleWrap::Unwrap(args.This())->queue_position_up();
    return scope.Close(Undefined());
  };

  Handle<Value> TorrentHandleWrap::queue_position_down(const Arguments& args) {
    HandleScope scope;
    TorrentHandleWrap::Unwrap(args.This())->queue_position_down();
    return scope.Close(Undefined());
  };

  Handle<Value> TorrentHandleWrap::queue_position_top(const Arguments& args) {
    HandleScope scope;
    TorrentHandleWrap::Unwrap(args.This())->queue_position_top();
    return scope.Close(Undefined());
  };

  Handle<Value> TorrentHandleWrap::queue_position_bottom(const Arguments& args) {
    HandleScope scope;
    TorrentHandleWrap::Unwrap(args.This())->queue_position_bottom();
    return scope.Close(Undefined());
  };

#ifndef TORRENT_DISABLE_RESOLVE_COUNTRIES
  Handle<Value> TorrentHandleWrap::resolve_countries(const Arguments& args) {
    HandleScope scope;

    if (args.Length() == 1) {
      TorrentHandleWrap::Unwrap(args.This())->resolve_countries(args[0]->BooleanValue());
      return scope.Close(Undefined());
    } else {
      return scope.Close(Boolean::New(
        TorrentHandleWrap::Unwrap(args.This())->resolve_countries()));
    }
  };
#endif

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

  Handle<Value> TorrentHandleWrap::set_piece_deadline(const Arguments& args) {
    HandleScope scope;
    libtorrent::torrent_handle* th = TorrentHandleWrap::Unwrap(args.This());
    int index = args[0]->IntegerValue(), deadline = args[1]->IntegerValue();
    if (args.Length() == 3)
      th->set_piece_deadline(index, deadline, args[2]->IntegerValue());
    else
      th->set_piece_deadline(index, deadline);
    return scope.Close(Undefined());
  };

  Handle<Value> TorrentHandleWrap::reset_piece_deadline(const Arguments& args) {
    HandleScope scope;
    TorrentHandleWrap::Unwrap(args.This())->reset_piece_deadline(
      args[0]->IntegerValue());
    return scope.Close(Undefined());
  };

  Handle<Value> TorrentHandleWrap::piece_availability(const Arguments& args) {
    HandleScope scope;
    
    std::vector<int> a;
    Local<Array> avail = Array::Cast(*args[0]);
    for (uint32_t i(0), e(avail->Length()); i < e; ++i)
      a.push_back(avail->Get(i)->IntegerValue());
    TorrentHandleWrap::Unwrap(args.This())->piece_availability(a);
    return scope.Close(Undefined());
  };

  Handle<Value> TorrentHandleWrap::piece_priority(const Arguments& args) {
    HandleScope scope;

    libtorrent::torrent_handle* th = TorrentHandleWrap::Unwrap(args.This());
    if (args.Length() == 2) {
      th->piece_priority(args[0]->IntegerValue(), args[1]->IntegerValue());
      return scope.Close(Undefined());
    } else {
      return scope.Close(Integer::New(th->piece_priority(args[0]->IntegerValue())));
    }
  };

  Handle<Value> TorrentHandleWrap::prioritize_pieces(const Arguments& args) {
    HandleScope scope;
    
    std::vector<int> p;
    Local<Array> pieces = Array::Cast(*args[0]);
    for (uint32_t i(0), e(pieces->Length()); i < e; ++i)
      p.push_back(pieces->Get(i)->IntegerValue());
    TorrentHandleWrap::Unwrap(args.This())->prioritize_pieces(p);
    return scope.Close(Undefined());
  };

  Handle<Value> TorrentHandleWrap::piece_priorities(const Arguments& args) {
    HandleScope scope;
    
    std::vector<int> p(TorrentHandleWrap::Unwrap(args.This())->piece_priorities());
    Local<Array> ret = Array::New();
    for (std::vector<int>::iterator i(p.begin()), e(p.end()); i != e; ++i)
      ret->Set(ret->Length(), Integer::New(*i));
    return scope.Close(ret);
  };

  Handle<Value> TorrentHandleWrap::prioritize_files(const Arguments& args) {
    HandleScope scope;
    
    std::vector<int> f;
    Local<Array> files = Array::Cast(*args[0]);
    for (uint32_t i(0), e(files->Length()); i < e; ++i)
      f.push_back(files->Get(i)->IntegerValue());
    TorrentHandleWrap::Unwrap(args.This())->prioritize_files(f);
    return scope.Close(Undefined());
  };

  Handle<Value> TorrentHandleWrap::file_priorities(const Arguments& args) {
    HandleScope scope;
    
    std::vector<int> f(TorrentHandleWrap::Unwrap(args.This())->file_priorities());
    Local<Array> ret = Array::New();
    for (std::vector<int>::iterator i(f.begin()), e(f.end()); i != e; ++i)
      ret->Set(ret->Length(), Integer::New(*i));
    return scope.Close(ret);
    return scope.Close(Undefined());
  };

  Handle<Value> TorrentHandleWrap::file_priority(const Arguments& args) {
    HandleScope scope;

    libtorrent::torrent_handle* th = TorrentHandleWrap::Unwrap(args.This());
    if (args.Length() == 2) {
      th->file_priority(args[0]->IntegerValue(), args[1]->IntegerValue());
      return scope.Close(Undefined());
    } else {
      return scope.Close(Integer::New(th->file_priority(args[0]->IntegerValue())));
    }
    return scope.Close(Undefined());
  };

  Handle<Value> TorrentHandleWrap::use_interface(const Arguments& args) {
    HandleScope scope;
    TorrentHandleWrap::Unwrap(args.This())->use_interface(*String::AsciiValue(args[0]));
    return scope.Close(Undefined());
  };

  Handle<Value> TorrentHandleWrap::save_resume_data(const Arguments& args) {
    HandleScope scope;
    if (args.Length() == 1)
      TorrentHandleWrap::Unwrap(args.This())->save_resume_data(args[0]->IntegerValue());
    else
      TorrentHandleWrap::Unwrap(args.This())->save_resume_data();
    return scope.Close(Undefined());
  };

  Handle<Value> TorrentHandleWrap::need_save_resume_data(const Arguments& args) {
    HandleScope scope;
    return scope.Close(Boolean::New(
      TorrentHandleWrap::Unwrap(args.This())->need_save_resume_data()));
  };

  Handle<Value> TorrentHandleWrap::force_reannounce(const Arguments& args) {
    HandleScope scope;
    TorrentHandleWrap::Unwrap(args.This())->force_reannounce();
    return scope.Close(Undefined());
  };

#ifndef TORRENT_DISABLE_DHT
  Handle<Value> TorrentHandleWrap::force_dht_announce(const Arguments& args) {
    HandleScope scope;
    TorrentHandleWrap::Unwrap(args.This())->force_dht_announce();
    return scope.Close(Undefined());
  };
#endif

  Handle<Value> TorrentHandleWrap::scrape_tracker(const Arguments& args) {
    HandleScope scope;
    TorrentHandleWrap::Unwrap(args.This())->scrape_tracker();
    return scope.Close(Undefined());
  };

  Handle<Value> TorrentHandleWrap::name(const Arguments& args) {
    HandleScope scope;
    return scope.Close(String::New(
      TorrentHandleWrap::Unwrap(args.This())->name().c_str()));
  };

  Handle<Value> TorrentHandleWrap::set_upload_mode(const Arguments& args) {
    HandleScope scope;
    TorrentHandleWrap::Unwrap(args.This())->set_upload_mode(args[0]->BooleanValue());
    return scope.Close(Undefined());
  };

  Handle<Value> TorrentHandleWrap::set_share_mode(const Arguments& args) {
    HandleScope scope;
    TorrentHandleWrap::Unwrap(args.This())->set_share_mode(args[0]->BooleanValue());
    return scope.Close(Undefined());
  };

  Handle<Value> TorrentHandleWrap::flush_cache(const Arguments& args) {
    HandleScope scope;
    TorrentHandleWrap::Unwrap(args.This())->flush_cache();
    return scope.Close(Undefined());
  };

  Handle<Value> TorrentHandleWrap::apply_ip_filter(const Arguments& args) {
    HandleScope scope;
    TorrentHandleWrap::Unwrap(args.This())->apply_ip_filter(args[0]->BooleanValue());
    return scope.Close(Undefined());
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

  Handle<Value> TorrentHandleWrap::set_sequential_download(const Arguments& args) {
    HandleScope scope;
    TorrentHandleWrap::Unwrap(args.This())->set_sequential_download(args[0]->BooleanValue());
    return scope.Close(Undefined());
  };

  Handle<Value> TorrentHandleWrap::connect_peer(const Arguments& args) {
    HandleScope scope;
    
    libtorrent::torrent_handle* th = TorrentHandleWrap::Unwrap(args.This());
    Local<Array> arg0 = Array::Cast(*args[0]);
    libtorrent::tcp::endpoint ip(
      libtorrent::address::from_string(std::string(*String::AsciiValue(arg0->Get(0)))),
      arg0->Get(0)->IntegerValue());
    if (args.Length() == 2)
      th->connect_peer(ip, args[1]->IntegerValue());
    else
      th->connect_peer(ip);
    return scope.Close(Undefined());
  };

  Handle<Value> TorrentHandleWrap::save_path(const Arguments& args) {
    HandleScope scope;
    return scope.Close(String::New(
      TorrentHandleWrap::Unwrap(args.This())->save_path().c_str()));
  };

  Handle<Value> TorrentHandleWrap::set_max_uploads(const Arguments& args) {
    HandleScope scope;
    TorrentHandleWrap::Unwrap(args.This())->set_max_uploads(args[0]->IntegerValue());
    return scope.Close(Undefined());
  };

  Handle<Value> TorrentHandleWrap::max_uploads(const Arguments& args) {
    HandleScope scope;
    return scope.Close(Integer::New(
      TorrentHandleWrap::Unwrap(args.This())->max_uploads()));
  };

  Handle<Value> TorrentHandleWrap::set_max_connections(const Arguments& args) {
    HandleScope scope;
    TorrentHandleWrap::Unwrap(args.This())->set_max_connections(args[0]->IntegerValue());
    return scope.Close(Undefined());
  };

  Handle<Value> TorrentHandleWrap::max_connections(const Arguments& args) {
    HandleScope scope;
    return scope.Close(Integer::New(
      TorrentHandleWrap::Unwrap(args.This())->max_connections()));
  };

  Handle<Value> TorrentHandleWrap::set_tracker_login(const Arguments& args) {
    HandleScope scope;
    TorrentHandleWrap::Unwrap(args.This())->set_tracker_login(
      std::string(*String::AsciiValue(args[0])),
      std::string(*String::AsciiValue(args[1])));
    return scope.Close(Undefined());
  };

  Handle<Value> TorrentHandleWrap::move_storage(const Arguments& args) {
    HandleScope scope;
    TorrentHandleWrap::Unwrap(args.This())->move_storage(
      std::string(*String::AsciiValue(args[0])));
    return scope.Close(Undefined());
  };

  Handle<Value> TorrentHandleWrap::info_hash(const Arguments& args) {
    HandleScope scope;
    libtorrent::sha1_hash h(TorrentHandleWrap::Unwrap(args.This())->info_hash());
    return scope.Close(String::New(libtorrent::to_hex(h.to_string()).c_str()));
  };

  Handle<Value> TorrentHandleWrap::force_recheck(const Arguments& args) {
    HandleScope scope;
    TorrentHandleWrap::Unwrap(args.This())->force_recheck();
    return scope.Close(Undefined());
  };

  Handle<Value> TorrentHandleWrap::rename_file(const Arguments& args) {
    HandleScope scope;
    TorrentHandleWrap::Unwrap(args.This())->rename_file(args[0]->IntegerValue(),
      std::string(*String::AsciiValue(args[1])));
    return scope.Close(Undefined());
  };

  Handle<Value> TorrentHandleWrap::set_ssl_certificate(const Arguments& args) {
    HandleScope scope;

    libtorrent::torrent_handle* th = TorrentHandleWrap::Unwrap(args.This());
    std::string
      certificate(*String::AsciiValue(args[0])),
      private_key(*String::AsciiValue(args[1])),
      dh_params(*String::AsciiValue(args[2]));
    if (args.Length() == 4)
      th->set_ssl_certificate(certificate, private_key, dh_params,
        std::string(*String::AsciiValue(args[3])));
    else
      th->set_ssl_certificate(certificate, private_key, dh_params);
    return scope.Close(Undefined());
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
