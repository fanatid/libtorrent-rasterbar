#include <v8.h>
#include <node.h>

#include <libtorrent/torrent_info.hpp>

#include "file_storage.hpp"
#include "torrent_info.hpp"

using namespace v8;
using namespace node;


namespace nodelt {
  Persistent<Function> TorrentInfoWrap::constructor;

  void TorrentInfoWrap::Initialize(Handle<Object> target) {
    Local<FunctionTemplate> tpl = FunctionTemplate::New(NewInstance);
    tpl->SetClassName(String::NewSymbol("torrent_info"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    tpl->PrototypeTemplate()->Set(String::NewSymbol("remap_files"),
      FunctionTemplate::New(remap_files)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("add_tracker"),
      FunctionTemplate::New(add_tracker)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("add_url_seed"),
      FunctionTemplate::New(add_url_seed)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("add_http_seed"),
      FunctionTemplate::New(add_http_seed)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("web_seeds"),
      FunctionTemplate::New(web_seeds)->GetFunction());

    tpl->PrototypeTemplate()->Set(String::NewSymbol("name"),
      FunctionTemplate::New(name)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("comment"),
      FunctionTemplate::New(comment)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("creator"),
      FunctionTemplate::New(creator)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("total_size"),
      FunctionTemplate::New(total_size)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("piece_length"),
      FunctionTemplate::New(piece_length)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("num_pieces"),
      FunctionTemplate::New(num_pieces)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("info_hash"),
      FunctionTemplate::New(info_hash)->GetFunction());

    tpl->PrototypeTemplate()->Set(String::NewSymbol("hash_for_piece"),
      FunctionTemplate::New(hash_for_piece)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("merkle_tree"),
      FunctionTemplate::New(merkle_tree)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("set_merkle_tree"),
      FunctionTemplate::New(set_merkle_tree)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("piece_size"),
      FunctionTemplate::New(piece_size)->GetFunction());

    tpl->PrototypeTemplate()->Set(String::NewSymbol("num_files"),
      FunctionTemplate::New(num_files)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("file_at"),
      FunctionTemplate::New(file_at)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("files"),
      FunctionTemplate::New(files)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("orig_files"),
      FunctionTemplate::New(orig_files)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("rename_file"),
      FunctionTemplate::New(rename_file)->GetFunction());

    tpl->PrototypeTemplate()->Set(String::NewSymbol("priv"),
      FunctionTemplate::New(priv)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("trackers"),
      FunctionTemplate::New(trackers)->GetFunction());

    tpl->PrototypeTemplate()->Set(String::NewSymbol("creation_date"),
      FunctionTemplate::New(creation_date)->GetFunction());

    tpl->PrototypeTemplate()->Set(String::NewSymbol("add_node"),
      FunctionTemplate::New(add_node)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("nodes"),
      FunctionTemplate::New(nodes)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("metadata"),
      FunctionTemplate::New(metadata)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("metadata_size"),
      FunctionTemplate::New(metadata_size)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("map_block"),
      FunctionTemplate::New(map_block)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("map_file"),
      FunctionTemplate::New(map_file)->GetFunction());

    target->Set(String::NewSymbol("torrent_info"),
      Persistent<Function>::New(tpl->GetFunction()));

    constructor = Persistent<Function>::New(tpl->GetFunction());
  };

  TorrentInfoWrap::TorrentInfoWrap() {
    obj_ = NULL;
  };

  TorrentInfoWrap::TorrentInfoWrap(const std::string& filename) {
    obj_ = new libtorrent::torrent_info(filename);
  };

  TorrentInfoWrap::~TorrentInfoWrap() {
    if (obj_ != NULL)
      delete obj_;
  };

  Handle<Value> TorrentInfoWrap::NewInstance(const Arguments& args) {
    HandleScope scope;

    if (!args.IsConstructCall())
      return ThrowException(Exception::TypeError(
        String::New("Use the new operator to create instances of this object.")));

    TorrentInfoWrap* ti;
    if (args.Length() == 1 && args[0]->IsString()) {
      std::string filename(*String::Utf8Value(args[0]->ToString()));
      ti = new TorrentInfoWrap(filename);
    } else {
      ti = new TorrentInfoWrap();
    }
    ti->Wrap(args.This());

    return scope.Close(args.This());
  };

  Local<Object> TorrentInfoWrap::New(const libtorrent::torrent_info& ti) {
    HandleScope scope;

    Local<Object> obj = constructor->NewInstance();
    ObjectWrap::Unwrap<TorrentInfoWrap>(obj)->obj_ = new libtorrent::torrent_info(ti);

    return scope.Close(obj);
  };

  Handle<Value> TorrentInfoWrap::remap_files(const Arguments& args) {
    HandleScope scope;
    TorrentInfoWrap::Unwrap(args.This())->remap_files(
      *FileStorageWrap::Unwrap(args[0]->ToObject()));
    return scope.Close(Undefined());
  };

  Handle<Value> TorrentInfoWrap::add_tracker(const Arguments& args) {
    HandleScope scope;
    TorrentInfoWrap::Unwrap(args.This())->add_tracker(
      std::string(*String::AsciiValue(args[0])), args[1]->IntegerValue());
    return scope.Close(Undefined());
  };

  Local<Object> web_seed_entry_headers_t_to_object(const libtorrent::web_seed_entry::headers_t& h) {
    HandleScope scope;

    Local<Array> ret = Array::New();
    for (std::vector<std::pair<std::string, std::string> >::const_iterator
         i(h.begin()), e(h.end()); i != e; ++i) {
      Local<Array> obj = Array::New();
      obj->Set(0, String::New(i->first.c_str()));
      obj->Set(1, String::New(i->second.c_str()));
      ret->Set(ret->Length(), obj);
    }
    return scope.Close(ret);
  };

  libtorrent::web_seed_entry::headers_t web_seed_entry_headers_t_from_object(Local<Object> obj) {
    HandleScope scope;

    libtorrent::web_seed_entry::headers_t h;
    for (uint32_t i(0), e(Array::Cast(*obj)->Length()); i < e; ++i) {
      Local<Array> pair = Array::Cast(*obj->Get(i));
      h.push_back(std::make_pair(
        std::string(*String::AsciiValue(pair->Get(0))),
        std::string(*String::AsciiValue(pair->Get(1)))));
    }
    return h;
  };

  Handle<Value> TorrentInfoWrap::add_url_seed(const Arguments& args) {
    HandleScope scope;
    
    libtorrent::torrent_info* ti = TorrentInfoWrap::Unwrap(args.This());
    std::string url(*String::AsciiValue(args[0]));
    if (args.Length() > 1) {
      std::string extern_auth(*String::AsciiValue(args[1]));
      if (args.Length() == 2)
        ti->add_url_seed(url, extern_auth);
      else
        ti->add_url_seed(url, extern_auth,
          web_seed_entry_headers_t_from_object(args[2]->ToObject()));
    } else {
      ti->add_url_seed(url);
    }
    return scope.Close(Undefined());
  };

  Handle<Value> TorrentInfoWrap::add_http_seed(const Arguments& args) {
    HandleScope scope;
    
    libtorrent::torrent_info* ti = TorrentInfoWrap::Unwrap(args.This());
    std::string url(*String::AsciiValue(args[0]));
    if (args.Length() > 1) {
      std::string extern_auth(*String::AsciiValue(args[1]));
      if (args.Length() == 2)
        ti->add_http_seed(url, extern_auth);
      else
        ti->add_http_seed(url, extern_auth,
          web_seed_entry_headers_t_from_object(args[2]->ToObject()));
    } else {
      ti->add_http_seed(url);
    }
    return scope.Close(Undefined());
  };

  Handle<Value> TorrentInfoWrap::web_seeds(const Arguments& args) {
    HandleScope scope;

    libtorrent::torrent_info* ti = TorrentInfoWrap::Unwrap(args.This());
    const std::vector<libtorrent::web_seed_entry> ws = ti->web_seeds();
    Local<Array> ret = Array::New();
    for (std::vector<libtorrent::web_seed_entry>::const_iterator
         i(ws.begin()), e(ws.end()); i != e; ++i) {
      Local<Object> obj = Object::New();
      obj->Set(String::NewSymbol("url"), String::New(i->url.c_str()));
      obj->Set(String::NewSymbol("type"), Integer::New(i->type));
      obj->Set(String::NewSymbol("auth"), String::New(i->auth.c_str()));
      obj->Set(String::NewSymbol("extra_headers"), web_seed_entry_headers_t_to_object(i->extra_headers));
      int retry = libtorrent::total_seconds(i->retry - libtorrent::min_time());
      obj->Set(String::NewSymbol("retry"), Integer::New(retry));
      obj->Set(String::NewSymbol("resolving"), Boolean::New(i->resolving));
      obj->Set(String::NewSymbol("removed"), Boolean::New(i->removed));
      Local<Array> endpoint = Array::New();
      endpoint->Set(0, String::New(i->endpoint.address().to_string().c_str()));
      endpoint->Set(1, Integer::New(i->endpoint.port()));
      obj->Set(String::NewSymbol("endpoint"), endpoint);
      ret->Set(ret->Length(), obj);
    }
    return scope.Close(ret);
  };

  Handle<Value> TorrentInfoWrap::name(const Arguments& args) {
    HandleScope scope;
    return scope.Close(String::New(
      TorrentInfoWrap::Unwrap(args.This())->name().c_str()));
  };

  Handle<Value> TorrentInfoWrap::comment(const Arguments& args) {
    HandleScope scope;
    return scope.Close(String::New(
      TorrentInfoWrap::Unwrap(args.This())->comment().c_str()));
  };

  Handle<Value> TorrentInfoWrap::creator(const Arguments& args) {
    HandleScope scope;
    return scope.Close(String::New(
      TorrentInfoWrap::Unwrap(args.This())->creator().c_str()));
  };

  Handle<Value> TorrentInfoWrap::total_size(const Arguments& args) {
    HandleScope scope;
    return scope.Close(Integer::New(
      TorrentInfoWrap::Unwrap(args.This())->total_size()));
  };

  Handle<Value> TorrentInfoWrap::piece_length(const Arguments& args) {
    HandleScope scope;
    return scope.Close(Integer::New(
      TorrentInfoWrap::Unwrap(args.This())->piece_length()));
  };

  Handle<Value> TorrentInfoWrap::num_pieces(const Arguments& args) {
    HandleScope scope;
    return scope.Close(Integer::New(
      TorrentInfoWrap::Unwrap(args.This())->num_pieces()));
  };

  Handle<Value> TorrentInfoWrap::info_hash(const Arguments& args) {
    HandleScope scope;
    libtorrent::sha1_hash h(TorrentInfoWrap::Unwrap(args.This())->info_hash());
    return scope.Close(String::New(libtorrent::to_hex(h.to_string()).c_str()));
  };

  Handle<Value> TorrentInfoWrap::hash_for_piece(const Arguments& args) {
    HandleScope scope;
    libtorrent::sha1_hash hash;
    hash = TorrentInfoWrap::Unwrap(args.This())->hash_for_piece(args[0]->IntegerValue());
    return scope.Close(String::New(libtorrent::to_hex(hash.to_string()).c_str()));
  };

  Handle<Value> TorrentInfoWrap::merkle_tree(const Arguments& args) {
    HandleScope scope;

    std::vector<libtorrent::sha1_hash> t;
    t = TorrentInfoWrap::Unwrap(args.This())->merkle_tree();
    Local<Array> ret = Array::New();
    for (std::vector<libtorrent::sha1_hash>::iterator
         i(t.begin()), e(t.end()); i != e; ++i)
      ret->Set(ret->Length(), String::New(libtorrent::to_hex(i->to_string()).c_str()));
    return scope.Close(ret);
  };

  Handle<Value> TorrentInfoWrap::set_merkle_tree(const Arguments& args) {
    HandleScope scope;

    std::vector<libtorrent::sha1_hash> arg;
    Local<Array> t = Array::New();
    for (uint32_t i(0), e(t->Length()); i < e; ++i) {
      libtorrent::sha1_hash h;
      libtorrent::from_hex(*String::AsciiValue(t->Get(0)), 40, (char*)&h[0]);
      arg.push_back(h);
    }
    TorrentInfoWrap::Unwrap(args.This())->set_merkle_tree(arg);
    return scope.Close(Undefined());
  };

  Handle<Value> TorrentInfoWrap::piece_size(const Arguments& args) {
    HandleScope scope;
    return scope.Close(Integer::New(
      TorrentInfoWrap::Unwrap(args.This())->piece_size(args[0]->IntegerValue())));
  };


  Handle<Value> TorrentInfoWrap::num_files(const Arguments& args) {
    HandleScope scope;
    return scope.Close(Integer::New(
      TorrentInfoWrap::Unwrap(args.This())->num_files()));
  };

  Handle<Value> TorrentInfoWrap::file_at(const Arguments& args) {
    HandleScope scope;
    return scope.Close(file_entry_to_object(
      TorrentInfoWrap::Unwrap(args.This())->file_at(args[0]->IntegerValue())));
  };

  Handle<Value> TorrentInfoWrap::files(const Arguments& args) {
    HandleScope scope;
    return scope.Close(FileStorageWrap::New(
      TorrentInfoWrap::Unwrap(args.This())->files()));
  };

  Handle<Value> TorrentInfoWrap::orig_files(const Arguments& args) {
    HandleScope scope;
    return scope.Close(FileStorageWrap::New(
      TorrentInfoWrap::Unwrap(args.This())->orig_files()));
  };

  Handle<Value> TorrentInfoWrap::rename_file(const Arguments& args) {
    HandleScope scope;
    TorrentInfoWrap::Unwrap(args.This())->rename_file(
      args[0]->IntegerValue(),
      std::string(*String::AsciiValue(args[1])));
    return scope.Close(Undefined());
  };


  Handle<Value> TorrentInfoWrap::priv(const Arguments& args) {
    HandleScope scope;
    return scope.Close(Boolean::New(
      TorrentInfoWrap::Unwrap(args.This())->priv()));
  };

  Handle<Value> TorrentInfoWrap::trackers(const Arguments& args) {
    HandleScope scope;

    std::vector<libtorrent::announce_entry> t;
    t = TorrentInfoWrap::Unwrap(args.This())->trackers();
    Local<Array> ret = Array::New();
    for (std::vector<libtorrent::announce_entry>::iterator
         i(t.begin()), e(t.end()); i != e; ++i)
      ret->Set(ret->Length(), announce_entry_to_object(*i));
    return scope.Close(ret);
  };


  Handle<Value> TorrentInfoWrap::creation_date(const Arguments& args) {
    HandleScope scope;
    return scope.Close(Date::New(
      ((double) *TorrentInfoWrap::Unwrap(args.This())->creation_date())*1000));
  };


  Handle<Value> TorrentInfoWrap::add_node(const Arguments& args) {
    HandleScope scope;
    TorrentInfoWrap::Unwrap(args.This())->add_node(std::make_pair(
      std::string(*String::AsciiValue(args[0])),
      args[1]->IntegerValue()));
    return scope.Close(Undefined());
  };

  Handle<Value> TorrentInfoWrap::nodes(const Arguments& args) {
    HandleScope scope;
    
    std::vector<std::pair<std::string, int> > ns;
    ns = TorrentInfoWrap::Unwrap(args.This())->nodes();
    Local<Array> ret = Array::New();
    for (std::vector<std::pair<std::string, int> >::iterator
         i(ns.begin()), e(ns.end()); i != e; ++i) {
      Local<Array> obj = Array::New();
      obj->Set(0, String::New(i->first.c_str()));
      obj->Set(1, Integer::New(i->second));
      ret->Set(ret->Length(), obj);
    }
    return scope.Close(ret);
  };

  Handle<Value> TorrentInfoWrap::metadata(const Arguments& args) {
    HandleScope scope;
    return scope.Close(String::New(
      &TorrentInfoWrap::Unwrap(args.This())->metadata()[0]));
  };

  Handle<Value> TorrentInfoWrap::metadata_size(const Arguments& args) {
    HandleScope scope;
    return scope.Close(Integer::New(
      TorrentInfoWrap::Unwrap(args.This())->metadata_size()));
  };

  Handle<Value> TorrentInfoWrap::map_block(const Arguments& args) {
    HandleScope scope;

    std::vector<libtorrent::file_slice> res;
    res = TorrentInfoWrap::Unwrap(args.This())->map_block(args[0]->IntegerValue(),
      args[1]->IntegerValue(), args[2]->IntegerValue());
    Local<Array> ret = Array::New();
    for (std::vector<libtorrent::file_slice>::iterator
         i(res.begin()), e(res.end()); i != e; ++i)
      ret->Set(ret->Length(), file_slice_to_object(*i));
    return scope.Close(ret);
  };

  Handle<Value> TorrentInfoWrap::map_file(const Arguments& args) {
    HandleScope scope;
    
    libtorrent::peer_request res;
    res = TorrentInfoWrap::Unwrap(args.This())->map_file(args[0]->IntegerValue(),
      args[1]->IntegerValue(), args[2]->IntegerValue());
    Local<Object> ret = Object::New();
    ret->Set(String::NewSymbol("piece"), Integer::New(res.piece));
    ret->Set(String::NewSymbol("start"), Integer::New(res.start));
    ret->Set(String::NewSymbol("length"), Integer::New(res.length));
    return scope.Close(ret);
  };


  v8::Local<v8::Object> announce_entry_to_object(const libtorrent::announce_entry& ae) {
    HandleScope scope;

    Local<Object> obj = Object::New();
    obj->Set(String::NewSymbol("url"), String::New(ae.url.c_str()));
    obj->Set(String::NewSymbol("tier"), Uint32::New(ae.tier));
    obj->Set(String::NewSymbol("fail_limit"), Uint32::New(ae.fail_limit));
    obj->Set(String::NewSymbol("fails"), Uint32::New(ae.fails));
    obj->Set(String::NewSymbol("source"), Uint32::New(ae.source));
    obj->Set(String::NewSymbol("verified"), Boolean::New(ae.verified));
    obj->Set(String::NewSymbol("updating"), Boolean::New(ae.updating));
    obj->Set(String::NewSymbol("start_sent"), Boolean::New(ae.start_sent));
    obj->Set(String::NewSymbol("complete_sent"), Boolean::New(ae.complete_sent));
    obj->Set(String::NewSymbol("send_stats"), Boolean::New(ae.send_stats));
    return scope.Close(obj);
  };

  libtorrent::announce_entry announce_entry_from_object(v8::Local<v8::Object> obj) {
    libtorrent::announce_entry ae(std::string(*String::Utf8Value(
      obj->Get(String::NewSymbol("url")))));

    if (obj->Has(String::NewSymbol("tier")))
      ae.tier = obj->Get(String::NewSymbol("tier"))->Uint32Value();
    if (obj->Has(String::NewSymbol("fail_limit")))
      ae.fail_limit = obj->Get(String::NewSymbol("fail_limit"))->Uint32Value();
    if (obj->Has(String::NewSymbol("source")))
      ae.source = obj->Get(String::NewSymbol("source"))->Uint32Value();
    if (obj->Has(String::NewSymbol("verified")))
      ae.verified = obj->Get(String::NewSymbol("verified"))->Uint32Value();
    if (obj->Has(String::NewSymbol("send_stats")))
      ae.send_stats = obj->Get(String::NewSymbol("send_stats"))->Uint32Value();
    return ae;
  };

  void bind_torrent_info(Handle<Object> target) {
    TorrentInfoWrap::Initialize(target);

    Local<Object> tracker_source = Object::New();
    tracker_source->Set(String::NewSymbol("source_torrent"),
      Integer::New(libtorrent::announce_entry::source_torrent));
    tracker_source->Set(String::NewSymbol("source_client"),
      Integer::New(libtorrent::announce_entry::source_client));
    tracker_source->Set(String::NewSymbol("source_magnet_link"),
      Integer::New(libtorrent::announce_entry::source_magnet_link));
    tracker_source->Set(String::NewSymbol("source_tex"),
      Integer::New(libtorrent::announce_entry::source_tex));
    target->Set(String::NewSymbol("tracker_source"), tracker_source);
  };
}; // namespace nodelt
