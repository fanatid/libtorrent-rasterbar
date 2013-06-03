#include <v8.h>
#include <node.h>

#include <libtorrent/add_torrent_params.hpp>
#include <libtorrent/disk_io_thread.hpp>
#include <libtorrent/error_code.hpp>
#include <libtorrent/extensions.hpp>
#include <libtorrent/fingerprint.hpp>
#include <libtorrent/ip_filter.hpp>
#include <libtorrent/lazy_entry.hpp>
#include <libtorrent/rss.hpp>
#include <libtorrent/session.hpp>
#include <libtorrent/session_status.hpp>
#include <libtorrent/torrent_handle.hpp>
#include <libtorrent/torrent_info.hpp>

#include <libtorrent/extensions/lt_trackers.hpp>
#include <libtorrent/extensions/metadata_transfer.hpp>
#include <libtorrent/extensions/smart_ban.hpp>
#include <libtorrent/extensions/ut_metadata.hpp>
#include <libtorrent/extensions/ut_pex.hpp>

#include "add_torrent_params.hpp"
#include "alert.hpp"
#include "disk_io_thread.hpp"
#include "entry.hpp"
#include "fingerprint.hpp"
#include "ip_filter.hpp"
#include "rss.hpp"
#include "session.hpp"
#include "session_settings.hpp"
#include "session_status.hpp"
#include "torrent_handle.hpp"
#include "torrent_info.hpp"

using namespace v8;
using namespace node;


namespace nodelt {
  void SessionWrap::Initialize(Handle<Object> target) {
    Local<FunctionTemplate> tpl = FunctionTemplate::New(NewInstance);
    tpl->SetClassName(String::NewSymbol("session"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    tpl->PrototypeTemplate()->Set(String::NewSymbol("save_state"),
      FunctionTemplate::New(save_state)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("load_state"),
      FunctionTemplate::New(load_state)->GetFunction());

    tpl->PrototypeTemplate()->Set(String::NewSymbol("post_torrent_updates"),
      FunctionTemplate::New(post_torrent_updates)->GetFunction());

    tpl->PrototypeTemplate()->Set(String::NewSymbol("get_torrents"),
      FunctionTemplate::New(get_torrents)->GetFunction());

    tpl->PrototypeTemplate()->Set(String::NewSymbol("find_torrent"),
      FunctionTemplate::New(find_torrent)->GetFunction());

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

    tpl->PrototypeTemplate()->Set(String::NewSymbol("status"),
      FunctionTemplate::New(status)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("get_cache_status"),
      FunctionTemplate::New(get_cache_status)->GetFunction());

    tpl->PrototypeTemplate()->Set(String::NewSymbol("get_cache_info"),
      FunctionTemplate::New(get_cache_info)->GetFunction());

    tpl->PrototypeTemplate()->Set(String::NewSymbol("add_feed"),
      FunctionTemplate::New(add_feed)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("remove_feed"),
      FunctionTemplate::New(remove_feed)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("get_feeds"),
      FunctionTemplate::New(get_feeds)->GetFunction());

#ifndef TORRENT_DISABLE_DHT
    tpl->PrototypeTemplate()->Set(String::NewSymbol("start_dht"),
      FunctionTemplate::New(start_dht)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("stop_dht"),
      FunctionTemplate::New(stop_dht)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("set_dht_settings"),
      FunctionTemplate::New(set_dht_settings)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("add_dht_node"),
      FunctionTemplate::New(add_dht_node)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("add_dht_router"),
      FunctionTemplate::New(add_dht_router)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("is_dht_running"),
      FunctionTemplate::New(is_dht_running)->GetFunction());
#endif

#ifndef TORRENT_DISABLE_EXTENSIONS
    tpl->PrototypeTemplate()->Set(String::NewSymbol("add_extension"),
      FunctionTemplate::New(add_extension)->GetFunction());
#endif

#ifndef TORRENT_DISABLE_DHT
    tpl->PrototypeTemplate()->Set(String::NewSymbol("load_asnum_db"),
      FunctionTemplate::New(load_asnum_db)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("load_country_db"),
      FunctionTemplate::New(load_country_db)->GetFunction());
#endif

    tpl->PrototypeTemplate()->Set(String::NewSymbol("set_ip_filter"),
      FunctionTemplate::New(set_ip_filter)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("get_ip_filter"),
      FunctionTemplate::New(get_ip_filter)->GetFunction());

    tpl->PrototypeTemplate()->Set(String::NewSymbol("set_peer_id"),
      FunctionTemplate::New(set_peer_id)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("id"),
      FunctionTemplate::New(id)->GetFunction());

    tpl->PrototypeTemplate()->Set(String::NewSymbol("is_listening"),
      FunctionTemplate::New(is_listening)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("listen_port"),
      FunctionTemplate::New(listen_port)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("listen_on"),
      FunctionTemplate::New(listen_on)->GetFunction());

    tpl->PrototypeTemplate()->Set(String::NewSymbol("remove_torrent"),
      FunctionTemplate::New(remove_torrent)->GetFunction());

    tpl->PrototypeTemplate()->Set(String::NewSymbol("set_settings"),
      FunctionTemplate::New(set_settings)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("settings"),
      FunctionTemplate::New(settings)->GetFunction());

    tpl->PrototypeTemplate()->Set(String::NewSymbol("set_proxy"),
      FunctionTemplate::New(set_proxy)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("proxy"),
      FunctionTemplate::New(proxy)->GetFunction());

#if TORRENT_USE_I2P
    tpl->PrototypeTemplate()->Set(String::NewSymbol("set_i2p_proxy"),
      FunctionTemplate::New(set_i2p_proxy)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("i2p_proxy"),
      FunctionTemplate::New(i2p_proxy)->GetFunction());
#endif

    tpl->PrototypeTemplate()->Set(String::NewSymbol("pop_alert"),
      FunctionTemplate::New(pop_alert)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("pop_alerts"),
      FunctionTemplate::New(pop_alerts)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("set_alert_mask"),
      FunctionTemplate::New(set_alert_mask)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("wait_for_alert"),
      FunctionTemplate::New(wait_for_alert)->GetFunction());

    tpl->PrototypeTemplate()->Set(String::NewSymbol("start_lsd"),
      FunctionTemplate::New(start_lsd)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("start_natpmp"),
      FunctionTemplate::New(start_natpmp)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("stop_upnp"),
      FunctionTemplate::New(stop_upnp)->GetFunction());

    tpl->PrototypeTemplate()->Set(String::NewSymbol("stop_lsd"),
      FunctionTemplate::New(stop_lsd)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("stop_natpmp"),
      FunctionTemplate::New(stop_natpmp)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("stop_upnp"),
      FunctionTemplate::New(stop_upnp)->GetFunction());

    target->Set(String::NewSymbol("session"),
      Persistent<Function>::New(tpl->GetFunction()));
  };

  SessionWrap::SessionWrap(Local<Array> args) {
    int args_len = args->Length();
    if (args_len >= 1 && args_len <= 5) {
      libtorrent::fingerprint* print_ = FingerprintWrap::Unwrap(args->Get(0)->ToObject());
      if (args_len == 1) {
        obj_ = new libtorrent::session(*print_);
        return;
      }
      if (args->Get(1)->IsArray()) {
        Local<Array> pr = Array::Cast(*args->Get(0));
        std::pair<int, int> port_range = std::make_pair(
          pr->Get(0)->IntegerValue(), pr->Get(1)->IntegerValue());
        if (args_len == 2) {
          obj_ = new libtorrent::session(*print_, port_range);
          return;
        }
        std::string interface(*String::AsciiValue(args->Get(2)->ToString()));
        if (args_len == 3)
          obj_ = new libtorrent::session(*print_, port_range, interface.c_str());
        else if (args_len == 4)
          obj_ = new libtorrent::session(*print_, port_range, interface.c_str(), args->Get(3)->Int32Value());
        else
          obj_ = new libtorrent::session(*print_, port_range, interface.c_str(), args->Get(3)->Int32Value(), args->Get(4)->Int32Value());
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

    libtorrent::session* s = SessionWrap::Unwrap(args.This());
    libtorrent::entry e;
    if (args.Length() == 1)
      s->save_state(e, args[0]->IntegerValue());
    else
      s->save_state(e);

    return scope.Close(entry_to_object(e));
  };

  Handle<Value> SessionWrap::load_state(const Arguments& args) {
    HandleScope scope;

    // deprecated! need lazy_entry...
    libtorrent::entry e = entry_from_object(args[0]);
    SessionWrap::Unwrap(args.This())->load_state(e);

    return scope.Close(Undefined());
  };


  Handle<Value> SessionWrap::post_torrent_updates(const Arguments& args) {
    HandleScope scope;
    SessionWrap::Unwrap(args.This())->post_torrent_updates();
    return scope.Close(Undefined());
  };


  Handle<Value> SessionWrap::get_torrents(const Arguments& args) {
    HandleScope scope;

    std::vector<libtorrent::torrent_handle> torrents;
    torrents = SessionWrap::Unwrap(args.This())->get_torrents();
    Local<Array> ret = Array::New();
    for (std::vector<libtorrent::torrent_handle>::iterator
         i(torrents.begin()), e(torrents.end()); i != e; ++i)
      ret->Set(ret->Length(), TorrentHandleWrap::New(*i));

    return scope.Close(ret);
  };


  Handle<Value> SessionWrap::find_torrent(const Arguments& args) {
    HandleScope scope;

    libtorrent::sha1_hash info_hash;
    libtorrent::from_hex(*String::AsciiValue(args[0]), 40, (char*)&info_hash[0]);
    libtorrent::torrent_handle th = SessionWrap::Unwrap(args.This())->find_torrent(info_hash);

    return scope.Close(TorrentHandleWrap::New(th));
  };


  Handle<Value> SessionWrap::add_torrent(const Arguments& args) {
    HandleScope scope;

    libtorrent::torrent_handle th;
    libtorrent::error_code ec;
    th = SessionWrap::Unwrap(args.This())->add_torrent(
      add_torrent_params_from_object(args[0]->ToObject()), ec);

    return scope.Close(TorrentHandleWrap::New(th));
  };

  Handle<Value> SessionWrap::async_add_torrent(const Arguments& args) {
    HandleScope scope;
    SessionWrap::Unwrap(args.This())->async_add_torrent(
      add_torrent_params_from_object(args[0]->ToObject()));
    return scope.Close(Undefined());
  };


  Handle<Value> SessionWrap::pause(const Arguments& args) {
    HandleScope scope;
    SessionWrap::Unwrap(args.This())->pause();
    return scope.Close(Undefined());
  };

  Handle<Value> SessionWrap::resume(const Arguments& args) {
    HandleScope scope;
    SessionWrap::Unwrap(args.This())->resume();
    return scope.Close(Undefined());
  };

  Handle<Value> SessionWrap::is_paused(const Arguments& args) {
    HandleScope scope;
    libtorrent::session* s = SessionWrap::Unwrap(args.This());
    return scope.Close(Boolean::New(s->is_paused()));
  };


  Handle<Value> SessionWrap::status(const Arguments& args) {
    HandleScope scope;
    libtorrent::session_status st = SessionWrap::Unwrap(args.This())->status();
    return scope.Close(session_status_to_object(st));
  };

  Handle<Value> SessionWrap::get_cache_status(const Arguments& args) {
    HandleScope scope;

    libtorrent::cache_status st = SessionWrap::Unwrap(args.This())->get_cache_status();
    Local<Object> obj = Object::New();

    obj->Set(String::NewSymbol("blocks_written"), Integer::New(st.blocks_written));
    obj->Set(String::NewSymbol("writes"), Integer::New(st.writes));
    obj->Set(String::NewSymbol("blocks_read"), Integer::New(st.blocks_read));
    obj->Set(String::NewSymbol("blocks_read_hit"), Integer::New(st.blocks_read_hit));
    obj->Set(String::NewSymbol("reads"), Integer::New(st.reads));
    obj->Set(String::NewSymbol("queued_bytes"), Integer::New(st.queued_bytes));
    obj->Set(String::NewSymbol("cache_size"), Integer::New(st.cache_size));
    obj->Set(String::NewSymbol("read_cache_size"), Integer::New(st.read_cache_size));
    obj->Set(String::NewSymbol("cache_size"), Integer::New(st.cache_size));
    obj->Set(String::NewSymbol("total_used_buffers"), Integer::New(st.total_used_buffers));

    obj->Set(String::NewSymbol("average_queue_time"), Integer::New(st.average_queue_time));
    obj->Set(String::NewSymbol("average_read_time"), Integer::New(st.average_read_time));
    obj->Set(String::NewSymbol("average_write_time"), Integer::New(st.average_write_time));
    obj->Set(String::NewSymbol("average_hash_time"), Integer::New(st.average_hash_time));
    obj->Set(String::NewSymbol("average_job_time"), Integer::New(st.average_job_time));
    obj->Set(String::NewSymbol("average_sort_time"), Integer::New(st.average_sort_time));
    obj->Set(String::NewSymbol("job_queue_length"), Integer::New(st.job_queue_length));

    obj->Set(String::NewSymbol("cumulative_job_time"), Integer::New(st.cumulative_job_time));
    obj->Set(String::NewSymbol("cumulative_read_time"), Integer::New(st.cumulative_read_time));
    obj->Set(String::NewSymbol("cumulative_write_time"), Integer::New(st.cumulative_write_time));
    obj->Set(String::NewSymbol("cumulative_hash_time"), Integer::New(st.cumulative_hash_time));
    obj->Set(String::NewSymbol("cumulative_sort_time"), Integer::New(st.cumulative_sort_time));
    obj->Set(String::NewSymbol("total_read_back"), Integer::New(st.total_read_back));
    obj->Set(String::NewSymbol("read_queue_size"), Integer::New(st.cache_size));

    return scope.Close(obj);
  };


  Handle<Value> SessionWrap::get_cache_info(const Arguments& args) {
    HandleScope scope;

    Local<Array> ret = Array::New();
    libtorrent::sha1_hash info_hash;
    libtorrent::from_hex(*String::AsciiValue(args[0]), 40, (char*)&info_hash[0]);
    std::vector<libtorrent::cached_piece_info> v;
    SessionWrap::Unwrap(args.This())->get_cache_info(info_hash, v);
    libtorrent::ptime now = libtorrent::time_now();
    for (std::vector<libtorrent::cached_piece_info>::iterator i(v.begin()), e(v.end()); i != e; ++i)
    {
      Local<Object> obj = Object::New();

      obj->Set(String::NewSymbol("piece"), Integer::New(i->piece));
      Local<Array> blocks = Array::New();
      for (std::vector<bool>::const_iterator j(i->blocks.begin()), e(i->blocks.end()); j != e; ++j)
        blocks->Set(blocks->Length(), Boolean::New(*j));
      obj->Set(String::NewSymbol("blocks"), blocks);
      obj->Set(String::NewSymbol("last_use"), Date::New(libtorrent::total_milliseconds(now - i->last_use)));
      obj->Set(String::NewSymbol("next_to_hash"), Integer::New(i->next_to_hash));
      obj->Set(String::NewSymbol("kind"), Integer::New(i->kind));

      ret->Set(ret->Length(), obj);
    }

    return scope.Close(ret);
  };


  Handle<Value> SessionWrap::add_feed(const Arguments& args) {
    HandleScope scope;

    libtorrent::feed_settings fs = feed_settings_from_object(args[0]->ToObject());
    libtorrent::feed_handle fh = SessionWrap::Unwrap(args.This())->add_feed(fs);
    return scope.Close(FeedHandleWrap::New(fh));
  };

  Handle<Value> SessionWrap::remove_feed(const Arguments& args) {
    HandleScope scope;
    SessionWrap::Unwrap(args.This())->remove_feed(
      *FeedHandleWrap::Unwrap(args[0]->ToObject()));
    return scope.Close(Undefined());
  };

  Handle<Value> SessionWrap::get_feeds(const Arguments& args) {
    HandleScope scope;
    
    std::vector<libtorrent::feed_handle> feeds;
    SessionWrap::Unwrap(args.This())->get_feeds(feeds);
    Local<Array> ret = Array::New();
    for (std::vector<libtorrent::feed_handle>::iterator
         i(feeds.begin()), e(feeds.end()); i != e; ++i)
      ret->Set(ret->Length(), FeedHandleWrap::New(*i));
    return scope.Close(ret);
  };

#ifndef TORRENT_DISABLE_DHT
  Handle<Value> SessionWrap::start_dht(const Arguments& args) {
    HandleScope scope;
    SessionWrap::Unwrap(args.This())->start_dht();
    return scope.Close(Undefined());
  };

  Handle<Value> SessionWrap::stop_dht(const Arguments& args) {
    HandleScope scope;
    SessionWrap::Unwrap(args.This())->stop_dht();
    return scope.Close(Undefined());
  };

  Handle<Value> SessionWrap::set_dht_settings(const Arguments& args) {
    HandleScope scope;
    SessionWrap::Unwrap(args.This())->set_dht_settings(
      dht_settings_from_object(args[0]->ToObject()));
    return scope.Close(Undefined());
  };

  Handle<Value> SessionWrap::add_dht_node(const Arguments& args) {
    HandleScope scope;
    SessionWrap::Unwrap(args.This())->add_dht_node(std::make_pair(
      std::string((*String::AsciiValue(args[0]))), args[0]->IntegerValue()));
    return scope.Close(Undefined());
  };

  Handle<Value> SessionWrap::add_dht_router(const Arguments& args) {
    HandleScope scope;
    SessionWrap::Unwrap(args.This())->add_dht_router(std::make_pair(
      std::string((*String::AsciiValue(args[0]))), args[0]->IntegerValue()));
    return scope.Close(Undefined());
  };

  Handle<Value> SessionWrap::is_dht_running(const Arguments& args) {
    HandleScope scope;
    bool ret = SessionWrap::Unwrap(args.This())->is_dht_running();
    return scope.Close(Boolean::New(ret));
  };
#endif

#ifndef TORRENT_DISABLE_EXTENSIONS
  Handle<Value> SessionWrap::add_extension(const Arguments& args) {
    HandleScope scope;

    libtorrent::session* s = SessionWrap::Unwrap(args.This());
    std::string name(*String::Utf8Value(args[0]));
    if (name == "ut_metadata")
      s->add_extension(libtorrent::create_ut_metadata_plugin);
    else if (name == "ut_pex")
      s->add_extension(libtorrent::create_ut_pex_plugin);
    else if (name == "smart_ban")
      s->add_extension(libtorrent::create_smart_ban_plugin);
    else if (name == "lt_trackers")
      s->add_extension(libtorrent::create_lt_trackers_plugin);
    else if (name == "metadata_transfer")
      s->add_extension(libtorrent::create_metadata_plugin);

    return scope.Close(Undefined());
  };
#endif

#ifndef TORRENT_DISABLE_GEO_IP
  Handle<Value> SessionWrap::load_asnum_db(const Arguments& args) {
    HandleScope scope;
    SessionWrap::Unwrap(args.This())->load_asnum_db(
      std::string((*String::Utf8Value(args[0]))).c_str());
    return scope.Close(Undefined());
  };

  Handle<Value> SessionWrap::load_country_db(const Arguments& args) {
    HandleScope scope;
    SessionWrap::Unwrap(args.This())->load_country_db(
      std::string((*String::Utf8Value(args[0]))).c_str());
    return scope.Close(Undefined());
  };
#endif

  Handle<Value> SessionWrap::set_ip_filter(const Arguments& args) {
    HandleScope scope;
    SessionWrap::Unwrap(args.This())->set_ip_filter(
      *IpFilterWrap::Unwrap(args[0]->ToObject()));
    return scope.Close(Undefined());
  };

  Handle<Value> SessionWrap::get_ip_filter(const Arguments& args) {
    HandleScope scope;
    libtorrent::ip_filter f = SessionWrap::Unwrap(args.This())->get_ip_filter();
    return scope.Close(IpFilterWrap::New(f));
  };


  Handle<Value> SessionWrap::set_peer_id(const Arguments& args) {
    HandleScope scope;

    libtorrent::peer_id pid;
    libtorrent::from_hex(*String::AsciiValue(args[0]->ToString()), 40, (char*)&pid[0]);
    SessionWrap::Unwrap(args.This())->set_peer_id(pid);

    return scope.Close(Undefined());
  };

  Handle<Value> SessionWrap::id(const Arguments& args) {
    HandleScope scope;
    std::string ret(SessionWrap::Unwrap(args.This())->id().to_string());
    return scope.Close(String::New(ret.c_str()));
  };


  Handle<Value> SessionWrap::is_listening(const Arguments& args) {
    HandleScope scope;
    libtorrent::session* s = SessionWrap::Unwrap(args.This());
    return scope.Close(Boolean::New(s->is_listening()));
  };

  Handle<Value> SessionWrap::listen_port(const Arguments& args) {
    HandleScope scope;
    libtorrent::session* s = SessionWrap::Unwrap(args.This());
    return scope.Close(Integer::New(s->listen_port()));
  };

  Handle<Value> SessionWrap::listen_on(const Arguments& args) {
    HandleScope scope;

    Local<Array> pr = Array::Cast(*args[0]);
    std::pair<int, int> port_range = std::make_pair(
      pr->Get(0)->IntegerValue(), pr->Get(1)->IntegerValue());
    libtorrent::error_code ec;
    libtorrent::session* s = SessionWrap::Unwrap(args.This());

    if (args.Length() == 1) {
      s->listen_on(port_range, ec);
    } else {
      std::string interface(*String::AsciiValue(args[1]->ToString()));
      if (args.Length() == 2) {
        s->listen_on(port_range, ec, interface.c_str());
      } else {
        s->listen_on(port_range, ec, interface.c_str(), args[2]->Int32Value());
      }
    }

    return scope.Close(Undefined());
  };


  Handle<Value> SessionWrap::remove_torrent(const Arguments& args) {
    HandleScope scope;

    libtorrent::torrent_handle* th = TorrentHandleWrap::Unwrap(args[0]->ToObject());
    if (args.Length() == 2)
      SessionWrap::Unwrap(args.This())->remove_torrent(*th, args[1]->IntegerValue());
    else
      SessionWrap::Unwrap(args.This())->remove_torrent(*th);

    return scope.Close(Undefined());
  };


  Handle<Value> SessionWrap::set_settings(const Arguments& args) {
    HandleScope scope;
    SessionWrap::Unwrap(args.This())->set_settings(
      session_settings_from_object(args[0]->ToObject()));
    return scope.Close(Undefined());
  };

  Handle<Value> SessionWrap::settings(const Arguments& args) {
    HandleScope scope;
    libtorrent::session_settings s = SessionWrap::Unwrap(args.This())->settings();
    return scope.Close(session_settings_to_object(s));
  };


  Handle<Value> SessionWrap::set_proxy(const Arguments& args) {
    HandleScope scope;
    SessionWrap::Unwrap(args.This())->set_proxy(
      proxy_settings_from_object(args[0]->ToObject()));
    return scope.Close(Undefined());
  };

  Handle<Value> SessionWrap::proxy(const Arguments& args) {
    HandleScope scope;
    libtorrent::proxy_settings s = SessionWrap::Unwrap(args.This())->proxy();
    return scope.Close(proxy_settings_to_object(s));
  };

#if TORRENT_USE_I2P
  Handle<Value> SessionWrap::set_i2p_proxy(const Arguments& args) {
    HandleScope scope;
    SessionWrap::Unwrap(args.This())->set_i2p_proxy(
      proxy_settings_from_object(args[0]->ToObject()));
    return scope.Close(Undefined());
  };

  Handle<Value> SessionWrap::i2p_proxy(const Arguments& args) {
    HandleScope scope;
    libtorrent::proxy_settings s = SessionWrap::Unwrap(args.This())->i2p_proxy();
    return scope.Close(proxy_settings_to_object(s));
  };
#endif

  Handle<Value> SessionWrap::pop_alert(const Arguments& args) {
    HandleScope scope;
    return scope.Close(
      alert_to_object(*SessionWrap::Unwrap(args.This())->pop_alert()));
  };

  Handle<Value> SessionWrap::pop_alerts(const Arguments& args) {
    HandleScope scope;

    Local<Array> ret = Array::New();
    std::deque<libtorrent::alert*> alerts;
    SessionWrap::Unwrap(args.This())->pop_alerts(&alerts);
    for (std::deque<libtorrent::alert*>::iterator
         i(alerts.begin()), e(alerts.end()); i != e; ++i)
      ret->Set(ret->Length(), alert_to_object(**i));
    return scope.Close(ret);
  };

  Handle<Value> SessionWrap::set_alert_mask(const Arguments& args) {
    HandleScope scope;
    SessionWrap::Unwrap(args.This())->set_alert_mask(args[0]->Uint32Value());
    return scope.Close(Undefined());
  };

  Handle<Value> SessionWrap::wait_for_alert(const Arguments& args) {
    HandleScope scope;
    
    const libtorrent::alert* alert;
    alert = SessionWrap::Unwrap(args.This())->wait_for_alert(
      libtorrent::milliseconds(args[0]->IntegerValue()));
    return scope.Close(alert_to_object(*alert));
  };


  Handle<Value> SessionWrap::start_lsd(const Arguments& args) {
    HandleScope scope;
    SessionWrap::Unwrap(args.This())->start_lsd();
    return scope.Close(Undefined());
  };

  Handle<Value> SessionWrap::start_natpmp(const Arguments& args) {
    HandleScope scope;
    SessionWrap::Unwrap(args.This())->start_natpmp();
    return scope.Close(Undefined());
  };

  Handle<Value> SessionWrap::start_upnp(const Arguments& args) {
    HandleScope scope;
    SessionWrap::Unwrap(args.This())->start_upnp();
    return scope.Close(Undefined());
  };


  Handle<Value> SessionWrap::stop_lsd(const Arguments& args) {
    HandleScope scope;
    SessionWrap::Unwrap(args.This())->stop_lsd();
    return scope.Close(Undefined());
  };

  Handle<Value> SessionWrap::stop_natpmp(const Arguments& args) {
    HandleScope scope;
    SessionWrap::Unwrap(args.This())->stop_natpmp();
    return scope.Close(Undefined());
  };

  Handle<Value> SessionWrap::stop_upnp(const Arguments& args) {
    HandleScope scope;
    SessionWrap::Unwrap(args.This())->stop_upnp();
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

    // set libtorrent::session::options_t
    Local<Object> options_t = Object::New();
    options_t->Set(String::NewSymbol("none"),
      Integer::New(libtorrent::session::none));
    options_t->Set(String::NewSymbol("delete_files"),
      Integer::New(libtorrent::session::delete_files));
    target->Set(String::NewSymbol("options_t"), options_t);

    // set libtorrent::session::session_flags_t
    Local<Object> session_flags_t = Object::New();
    session_flags_t->Set(String::NewSymbol("start_default_features"),
      Integer::New(libtorrent::session::add_default_plugins));
    session_flags_t->Set(String::NewSymbol("start_default_features"),
      Integer::New(libtorrent::session::start_default_features));
    target->Set(String::NewSymbol("session_flags_t"), session_flags_t);
  };
}; // namespace nodelt
