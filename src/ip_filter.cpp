#include <v8.h>
#include <node.h>

#include <libtorrent/ip_filter.hpp>

#include "ip_filter.hpp"

using namespace v8;
using namespace node;


namespace nodelt {
  Persistent<Function> IpFilterWrap::constructor;

  void IpFilterWrap::Initialize(Handle<Object> target) {
    Local<FunctionTemplate> tpl = FunctionTemplate::New(NewInstance);
    tpl->SetClassName(String::NewSymbol("ip_filter"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    tpl->PrototypeTemplate()->Set(String::NewSymbol("add_rule"),
      FunctionTemplate::New(add_rule)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("access"),
      FunctionTemplate::New(access)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("export_filter"),
      FunctionTemplate::New(export_filter)->GetFunction());

    constructor = Persistent<Function>::New(tpl->GetFunction());
  };

  IpFilterWrap::IpFilterWrap() {
    obj_ = NULL;
  };

  IpFilterWrap::~IpFilterWrap() {
    if (obj_ != NULL)
      delete obj_;
  };

  Handle<Value> IpFilterWrap::NewInstance(const Arguments& args) {
    HandleScope scope;

    if (!args.IsConstructCall())
      return ThrowException(Exception::TypeError(
        String::New("Use the new operator to create instances of this object.")));

    IpFilterWrap* fs = new IpFilterWrap();
    fs->Wrap(args.This());

    return scope.Close(args.This());
  };

  Local<Object> IpFilterWrap::New(const libtorrent::ip_filter& f) {
    HandleScope scope;

    Local<Object> obj = constructor->NewInstance();
    ObjectWrap::Unwrap<IpFilterWrap>(obj)->obj_ = new libtorrent::ip_filter(f);

    return scope.Close(obj);
  };

  Handle<Value> IpFilterWrap::add_rule(const Arguments& args) {
    HandleScope scope;

    libtorrent::address first, last;
    first = libtorrent::address::from_string(std::string(*String::AsciiValue(args[0])));
    last = libtorrent::address::from_string(std::string(*String::AsciiValue(args[1])));
    IpFilterWrap::Unwrap(args.This())->add_rule(first, last, args[2]->IntegerValue());
    return scope.Close(Undefined());
  };

  Handle<Value> IpFilterWrap::access(const Arguments& args) {
    HandleScope scope;

    int ret = IpFilterWrap::Unwrap(args.This())->access(
      libtorrent::address::from_string(std::string(*String::AsciiValue(args[0]))));
    return scope.Close(Integer::New(ret));
  };

  template <class Addr>
  Local<Object> ip_range_to_object(const libtorrent::ip_range<Addr>& s) {
    HandleScope scope;
    Local<Object> obj = Object::New();

    obj->Set(String::NewSymbol("first"), String::New(s.first.to_string().c_str()));
    obj->Set(String::NewSymbol("last"), String::New(s.first.to_string().c_str()));
    obj->Set(String::NewSymbol("flags"), Integer::New(s.flags));
    return scope.Close(obj);
  };

  Handle<Value> IpFilterWrap::export_filter(const Arguments& args) {
    HandleScope scope;

    libtorrent::ip_filter::filter_tuple_t res = IpFilterWrap::Unwrap(args.This())->export_filter();
    Local<Array> ret = Array::New();
#if TORRENT_USE_IPV6
    Local<Array> v4 = Array::New(), v6 = Array::New();
    for (std::vector<libtorrent::ip_range<libtorrent::address_v4> >::iterator
     i(res.get<0>().begin()), e(res.get<0>().end()); i != e; ++i)
      v4->Set(v4->Length(), ip_range_to_object<libtorrent::address_v4>(*i));
    for (std::vector<libtorrent::ip_range<libtorrent::address_v6> >::iterator
     i(res.get<1>().begin()), e(res.get<1>().end()); i != e; ++i)
      v6->Set(v6->Length(), ip_range_to_object<libtorrent::address_v6>(*i));
    ret->Set(0, v4);
    ret->Set(1, v6);
#else
    for (std::vector<libtorrent::ip_range<libtorrent::address_v4> >::iterator
     i(res.begin()), e(res.end()); i != e; ++i)
      ret->Set(ret->Length(), ip_range_to_object<libtorrent::address_v4>(*i));
#endif
    return scope.Close(ret);
  };


  void bind_ip_filter(Handle<Object> target) {
    IpFilterWrap::Initialize(target);
  };
}; // namespace nodelt
