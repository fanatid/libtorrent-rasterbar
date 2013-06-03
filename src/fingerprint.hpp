#ifndef NODE_LIBTORRENT_FINGERPRINT_HPP_INCLUDED
#define NODE_LIBTORRENT_FINGERPRINT_HPP_INCLUDED

#include <v8.h>
#include <node.h>

#include <libtorrent/fingerprint.hpp>


namespace nodelt {
  class FingerprintWrap: public node::ObjectWrap {
    public:
      static void Initialize(v8::Handle<v8::Object> target);
      static libtorrent::fingerprint* Unwrap(const v8::Local<v8::Object>& obj) {
        return node::ObjectWrap::Unwrap<FingerprintWrap>(obj)->obj_;
      };

    private:
      libtorrent::fingerprint* obj_;
      FingerprintWrap(const char* id_string,
        int major, int minor, int revision, int tag);
      ~FingerprintWrap();
      static v8::Handle<v8::Value> NewInstance(const v8::Arguments& args);

      static v8::Handle<v8::Value> to_string(const v8::Arguments& args);
  };
};

#endif // NODE_LIBTORRENT_FINGERPRINT_HPP_INCLUDED
