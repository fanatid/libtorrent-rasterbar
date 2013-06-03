#include <v8.h>
#include <node.h>

#include <libtorrent/rss.hpp>

#include "add_torrent_params.hpp"
#include "rss.hpp"
#include "torrent_handle.hpp"


using namespace v8;
using namespace node;


namespace nodelt {
  libtorrent::feed_settings feed_settings_from_object(Local<Object> obj) {
    libtorrent::feed_settings fs;

    if (obj->Has(String::NewSymbol("url")))
      fs.url = std::string(*String::Utf8Value(obj->Get(String::NewSymbol("url"))));
    if (obj->Has(String::NewSymbol("auto_download")))
      fs.auto_download = obj->Get(String::NewSymbol("auto_download"))->BooleanValue();
    if (obj->Has(String::NewSymbol("auto_map_handles")))
      fs.auto_download = obj->Get(String::NewSymbol("auto_map_handles"))->BooleanValue();
    if (obj->Has(String::NewSymbol("default_ttl")))
      fs.auto_download = obj->Get(String::NewSymbol("default_ttl"))->IntegerValue();
    if (obj->Has(String::NewSymbol("add_args")))
      fs.add_args =
        add_torrent_params_from_object(obj->Get(String::NewSymbol("add_args"))->ToObject());
    return fs;
  };

  Local<Object> feed_settings_to_object(const libtorrent::feed_settings& fs) {
    HandleScope scope;
    Local<Object> obj = Object::New();

    obj->Set(String::NewSymbol("url"), String::New(fs.url.c_str()));
    obj->Set(String::NewSymbol("auto_download"), Boolean::New(fs.auto_download));
    obj->Set(String::NewSymbol("default_ttl"), Integer::New(fs.default_ttl));
    return scope.Close(obj);
  };


  Persistent<Function> FeedHandleWrap::constructor;

  void FeedHandleWrap::Initialize(Handle<Object> target) {
    Local<FunctionTemplate> tpl = FunctionTemplate::New(NewInstance);
    tpl->SetClassName(String::NewSymbol("FeedHandle"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    tpl->PrototypeTemplate()->Set(String::NewSymbol("update_feed"),
      FunctionTemplate::New(update_feed)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("get_feed_status"),
      FunctionTemplate::New(get_feed_status)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("set_settings"),
      FunctionTemplate::New(set_settings)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("settings"),
      FunctionTemplate::New(settings)->GetFunction());

    constructor = Persistent<Function>::New(tpl->GetFunction());
  };

  FeedHandleWrap::FeedHandleWrap() {
    obj_ = NULL;
  };

  FeedHandleWrap::~FeedHandleWrap() {
    if (obj_ != NULL)
      delete obj_;
  };

  Handle<Value> FeedHandleWrap::NewInstance(const v8::Arguments& args) {
    HandleScope scope;

    if (!args.IsConstructCall())
      return ThrowException(Exception::TypeError(
        String::New("Use the new operator to create instances of this object.")));

    FeedHandleWrap* fh = new FeedHandleWrap();
    fh->Wrap(args.This());

    return scope.Close(args.This());
  };

  Local<Object> FeedHandleWrap::New(const libtorrent::feed_handle& fh) {
    HandleScope scope;

    Local<Object> obj = constructor->NewInstance();
    ObjectWrap::Unwrap<FeedHandleWrap>(obj)->obj_ = new libtorrent::feed_handle(fh);

    return scope.Close(obj);
  };

  Handle<Value> FeedHandleWrap::update_feed(const Arguments& args) {
    HandleScope scope;
    FeedHandleWrap::Unwrap(args.This())->update_feed();
    return scope.Close(Undefined());
  };

  Handle<Value> FeedHandleWrap::get_feed_status(const Arguments& args) {
    HandleScope scope;

    libtorrent::feed_status s = FeedHandleWrap::Unwrap(args.This())->get_feed_status();
    Local<Object> obj = Object::New();
    obj->Set(String::NewSymbol("url"), String::New(s.url.c_str()));
    obj->Set(String::NewSymbol("title"), String::New(s.url.c_str()));
    obj->Set(String::NewSymbol("description"), String::New(s.url.c_str()));
    obj->Set(String::NewSymbol("next_update"), Integer::New(s.next_update));
    obj->Set(String::NewSymbol("updating"), Boolean::New(s.updating));
    Local<Array> items = Array::New();
    for (std::vector<libtorrent::feed_item>::iterator
         i(s.items.begin()) , e(s.items.end()); i != e; ++i) {
      Local<Object> item = Object::New();
      item->Set(String::NewSymbol("url"), String::New(i->url.c_str()));
      item->Set(String::NewSymbol("uuid"), String::New(i->uuid.c_str()));
      item->Set(String::NewSymbol("title"), String::New(i->title.c_str()));
      item->Set(String::NewSymbol("description"), String::New(i->description.c_str()));
      item->Set(String::NewSymbol("comment"), String::New(i->comment.c_str()));
      item->Set(String::NewSymbol("category"), String::New(i->category.c_str()));
      item->Set(String::NewSymbol("size"), Integer::New(i->size));
      item->Set(String::NewSymbol("handle"), TorrentHandleWrap::New(i->handle));
      item->Set(String::NewSymbol("info_hash"),
        String::New(libtorrent::to_hex(i->info_hash.to_string()).c_str()));
      items->Set(items->Length(), item);
    }
    obj->Set(String::NewSymbol("items"), items);
    obj->Set(String::NewSymbol("error"), String::New(s.error ? s.error.message().c_str() : ""));
    obj->Set(String::NewSymbol("ttl"), Integer::New(s.ttl));
    return scope.Close(Undefined());
  };

  Handle<Value> FeedHandleWrap::set_settings(const Arguments& args) {
    HandleScope scope;
    FeedHandleWrap::Unwrap(args.This())->set_settings(
      feed_settings_from_object(args[0]->ToObject()));
    return scope.Close(Undefined());
  };

  Handle<Value> FeedHandleWrap::settings(const Arguments& args) {
    HandleScope scope;
    libtorrent::feed_settings fs = FeedHandleWrap::Unwrap(args.This())->settings();
    return scope.Close(feed_settings_to_object(fs));
  };
}; //namespace nodelt
