#include <node.h>
#include <v8.h>
#include <libtorrent/version.hpp>
#include "version.hpp"

using namespace v8;

void bind_version(Handle<Object> target) {
  target->Set(String::NewSymbol("version"), String::New(LIBTORRENT_VERSION));
}
