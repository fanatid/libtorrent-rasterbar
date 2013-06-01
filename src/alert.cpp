#include <v8.h>
#include <node.h>

#include <libtorrent/alert.hpp>

#include "alert.hpp"

using namespace v8;
using namespace node;


namespace nodelt {
  v8::Local<v8::Object> alert_to_object(const libtorrent::alert& alert) {
    HandleScope scope;
    Local<Object> obj = Object::New();

    obj->Set(String::NewSymbol("message"), String::New(alert.message().c_str()));
    obj->Set(String::NewSymbol("what"), String::New(alert.what()));
    obj->Set(String::NewSymbol("category"), Integer::New(alert.category()));
    return scope.Close(obj);
  };

  void bind_alert(Handle<Object> target) {
    Local<Object> category_t = Object::New();
    category_t->Set(String::NewSymbol("error_notification"),
      Integer::New(libtorrent::alert::error_notification));
    category_t->Set(String::NewSymbol("peer_notification"),
      Integer::New(libtorrent::alert::peer_notification));
    category_t->Set(String::NewSymbol("port_mapping_notification"),
      Integer::New(libtorrent::alert::port_mapping_notification));
    category_t->Set(String::NewSymbol("storage_notification"),
      Integer::New(libtorrent::alert::storage_notification));
    category_t->Set(String::NewSymbol("tracker_notification"),
      Integer::New(libtorrent::alert::tracker_notification));
    category_t->Set(String::NewSymbol("debug_notification"),
      Integer::New(libtorrent::alert::debug_notification));
    category_t->Set(String::NewSymbol("status_notification"),
      Integer::New(libtorrent::alert::status_notification));
    category_t->Set(String::NewSymbol("progress_notification"),
      Integer::New(libtorrent::alert::progress_notification));
    category_t->Set(String::NewSymbol("ip_block_notification"),
      Integer::New(libtorrent::alert::ip_block_notification));
    category_t->Set(String::NewSymbol("performance_warning"),
      Integer::New(libtorrent::alert::performance_warning));
    category_t->Set(String::NewSymbol("dht_notification"),
      Integer::New(libtorrent::alert::dht_notification));
    category_t->Set(String::NewSymbol("stats_notification"),
      Integer::New(libtorrent::alert::stats_notification));
    category_t->Set(String::NewSymbol("rss_notification"),
      Integer::New(libtorrent::alert::rss_notification));
    category_t->Set(String::NewSymbol("all_categories"),
      Integer::New(libtorrent::alert::all_categories));
    target->Set(String::NewSymbol("category_t"), category_t);
  };
}; // namespace nodelt
