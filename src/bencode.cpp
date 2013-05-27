#include <string>
#include <sstream>

#include <v8.h>
#include <node.h>

#include <libtorrent/bencode.hpp>

#include "entry.hpp"

using namespace v8;
using namespace node;


namespace nodelt {
  Handle<Value> bencode(const Arguments& args) {
    HandleScope scope;

    EntryWrap* w = ObjectWrap::Unwrap<EntryWrap>(args[0]->ToObject());
    std::ostringstream oss;
    libtorrent::bencode(std::ostream_iterator<char>(oss), *w->GetWrapped());

    return scope.Close(String::New(oss.str().c_str()));
  };

  void bind_bencode(Handle<Object> target) {
    target->Set(String::NewSymbol("bencode"),
      FunctionTemplate::New(nodelt::bencode)->GetFunction());
  };
}; // namespace nodelt
