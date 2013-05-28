#include <string>
#include <sstream>

#include <v8.h>
#include <node.h>

#include <libtorrent/bencode.hpp>
#include <libtorrent/entry.hpp>

#include "entry.hpp"

using namespace v8;
using namespace node;


namespace nodelt {
  Handle<Value> bdecode(const Arguments& args) {
    HandleScope scope;

    std::string buf(*String::AsciiValue(args[0]));
    libtorrent::entry e_ = libtorrent::bdecode(buf.c_str(), buf.c_str() + buf.size());

    return scope.Close(entry_to_object(e_));
  };

  Handle<Value> bencode(const Arguments& args) {
    HandleScope scope;

    std::ostringstream oss;
    libtorrent::bencode(std::ostream_iterator<char>(oss), entry_from_object(args[0]));

    return scope.Close(String::New(oss.str().c_str()));
  };

  void bind_bencode(Handle<Object> target) {
    target->Set(String::NewSymbol("bdecode"),
      FunctionTemplate::New(bdecode)->GetFunction());
    target->Set(String::NewSymbol("bencode"),
      FunctionTemplate::New(bencode)->GetFunction());
  };
}; // namespace nodelt
