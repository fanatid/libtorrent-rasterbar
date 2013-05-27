#include <v8.h>
#include <node.h>

#include <libtorrent/torrent_info.hpp>

#include "torrent_info.hpp"

using namespace v8;
using namespace node;


namespace nodelt {
  void TorrentInfoWrap::Initialize(Handle<Object> target) {
    // Prepare constructor template
    Local<FunctionTemplate> tpl = FunctionTemplate::New(NewInstance);
    tpl->SetClassName(String::NewSymbol("torrent_info"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    // Prototype

    target->Set(String::NewSymbol("torrent_info"),
      Persistent<Function>::New(tpl->GetFunction()));
  };

  TorrentInfoWrap::TorrentInfoWrap(std::string const& filename) {
    obj_ = new libtorrent::torrent_info(filename);
  };

  TorrentInfoWrap::~TorrentInfoWrap() {
    delete obj_;
  };

  Handle<Value> TorrentInfoWrap::NewInstance(const Arguments& args) {
    HandleScope scope;

    if (!args.IsConstructCall())
      return ThrowException(Exception::TypeError(
        String::New("Use the new operator to create instances of this object.")));

    std::string filename(*String::Utf8Value(args[0]->ToString()));
    TorrentInfoWrap* ti = new TorrentInfoWrap(filename);
    ti->Wrap(args.This());

    return scope.Close(args.This());
  };

  void bind_torrent_info(Handle<Object> target) {
    TorrentInfoWrap::Initialize(target);
  };
}; // namespace nodelt
