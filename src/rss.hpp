#ifndef NODE_LIBTORRENT_RSS_HPP_INCLUDED
#define NODE_LIBTORRENT_RSS_HPP_INCLUDED

#include <v8.h>
#include <node.h>

#include <libtorrent/rss.hpp>


namespace nodelt {
  libtorrent::feed_settings feed_settings_from_object(v8::Local<v8::Object> obj);
  v8::Local<v8::Object> feed_settings_to_object(const libtorrent::feed_settings& fs);

  class FeedHandleWrap: public node::ObjectWrap {
    public:
      static void Initialize(v8::Handle<v8::Object> target);
      static v8::Local<v8::Object> New(const libtorrent::feed_handle& fh);
      static libtorrent::feed_handle* Unwrap(const v8::Local<v8::Object>& obj) {
        return node::ObjectWrap::Unwrap<FeedHandleWrap>(obj)->obj_;
      };

    private:
      libtorrent::feed_handle* obj_;
      FeedHandleWrap();
      ~FeedHandleWrap();
      static v8::Persistent<v8::Function> constructor;
      static v8::Handle<v8::Value> NewInstance(const v8::Arguments& args);

      static v8::Handle<v8::Value> update_feed(const v8::Arguments& args);
      static v8::Handle<v8::Value> get_feed_status(const v8::Arguments& args);
      static v8::Handle<v8::Value> set_settings(const v8::Arguments& args);
      static v8::Handle<v8::Value> settings(const v8::Arguments& args);
  };
};

#endif // NODE_LIBTORRENT_RSS_HPP_INCLUDED
