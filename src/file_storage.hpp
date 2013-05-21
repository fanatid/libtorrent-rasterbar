#ifndef NODE_LIBTORRENT_FILE_STORAGE_HPP_INCLUDED
#define NODE_LIBTORRENT_FILE_STORAGE_HPP_INCLUDED

#include <v8.h>
#include <node.h>

#include <libtorrent/file_storage.hpp>


namespace nodelt {
  class FileStorageWrap: public node::ObjectWrap {
    public:
      static void Initialize(v8::Handle<v8::Object> target);
      libtorrent::file_storage* GetWrapped() const { return fs_; };
      static bool IsInstance(v8::Local<v8::Value> obj);

    private:
      FileStorageWrap();
      ~FileStorageWrap();
      static v8::Handle<v8::Value> New(const v8::Arguments& args);

      // Wrapped methods
      static v8::Handle<v8::Value> isValid(const v8::Arguments& args);
      static v8::Handle<v8::Value> numFiles(const v8::Arguments& args);
      static v8::Handle<v8::Value> totalSize(const v8::Arguments& args);
      static v8::Handle<v8::Value> setNumPieces(const v8::Arguments& args);
      static v8::Handle<v8::Value> numPieces(const v8::Arguments& args);

      // Wrapped object
      libtorrent::file_storage* fs_;
  };
};

#endif // NODE_LIBTORRENT_FILE_STORAGE_HPP_INCLUDED
