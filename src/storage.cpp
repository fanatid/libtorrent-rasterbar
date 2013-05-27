#include <v8.h>
#include <node.h>

#include <libtorrent/storage.hpp>

#include "storage.hpp"

using namespace v8;
using namespace node;


namespace nodelt {
  void bind_storage(Handle<Object> target) {
    // set libtorrent::storage_mode_t
    Local<Object> storage_mode_t = Object::New();
    storage_mode_t->Set(String::NewSymbol("storage_mode_allocate"),
      Integer::New(libtorrent::storage_mode_allocate));
    storage_mode_t->Set(String::NewSymbol("storage_mode_sparse"),
      Integer::New(libtorrent::storage_mode_sparse));
    target->Set(String::NewSymbol("storage_mode_t"), storage_mode_t);
  };
}; // namespace nodelt
