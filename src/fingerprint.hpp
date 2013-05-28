#ifndef NODE_LIBTORRENT_FINGERPRINT_HPP_INCLUDED
#define NODE_LIBTORRENT_FINGERPRINT_HPP_INCLUDED

#include <v8.h>
#include <node.h>

#include <libtorrent/fingerprint.hpp>


namespace nodelt {
  class FingerprintWrap: public node::ObjectWrap {
    public:
      static void Initialize(v8::Handle<v8::Object> target);
      libtorrent::fingerprint* GetWrapped() const { return obj_; };

    private:
      FingerprintWrap(const char* id_string,
        int major, int minor, int revision, int tag);
      ~FingerprintWrap();
      static v8::Handle<v8::Value> NewInstance(const v8::Arguments& args);

      // Wrapped methods
      static v8::Handle<v8::Value> to_string(const v8::Arguments& args);

      // Wrapped object
      libtorrent::fingerprint* obj_;
  };
};

#endif // NODE_LIBTORRENT_FINGERPRINT_HPP_INCLUDED
