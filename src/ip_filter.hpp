#ifndef NODE_LIBTORRENT_IP_FILTER_HPP_INCLUDED
#define NODE_LIBTORRENT_IP_FILTER_HPP_INCLUDED

#include <v8.h>
#include <node.h>

#include <libtorrent/ip_filter.hpp>


namespace nodelt {
  class IpFilterWrap: public node::ObjectWrap {
    public:
      static void Initialize(v8::Handle<v8::Object> target);
      static v8::Local<v8::Object> New(const libtorrent::ip_filter& f);
      static libtorrent::ip_filter* Unwrap(const v8::Local<v8::Object>& obj) {
        return node::ObjectWrap::Unwrap<IpFilterWrap>(obj)->obj_;
      };

    private:
      libtorrent::ip_filter* obj_;
      IpFilterWrap();
      ~IpFilterWrap();
      static v8::Persistent<v8::Function> constructor;
      static v8::Handle<v8::Value> NewInstance(const v8::Arguments& args);

      static v8::Handle<v8::Value> add_rule(const v8::Arguments& args);
      static v8::Handle<v8::Value> access(const v8::Arguments& args);
      static v8::Handle<v8::Value> export_filter(const v8::Arguments& args);
  };
};

#endif // NODE_LIBTORRENT_IP_FILTER_HPP_INCLUDED
