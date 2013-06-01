#ifndef NODE_LIBTORRENT_FILE_STORAGE_HPP_INCLUDED
#define NODE_LIBTORRENT_FILE_STORAGE_HPP_INCLUDED

#include <v8.h>
#include <node.h>

#include <libtorrent/file_storage.hpp>


namespace nodelt {
  class FileStorageWrap: public node::ObjectWrap {
    public:
      static void Initialize(v8::Handle<v8::Object> target);
      static libtorrent::file_storage* Unwrap(const v8::Local<v8::Object>& obj) {
        return node::ObjectWrap::Unwrap<FileStorageWrap>(obj)->obj_;
      };

    private:
      FileStorageWrap();
      ~FileStorageWrap();
      static v8::Handle<v8::Value> NewInstance(const v8::Arguments& args);

      // Wrapped methods
      static v8::Handle<v8::Value> is_valid(const v8::Arguments& args);
      static v8::Handle<v8::Value> num_files(const v8::Arguments& args);
      static v8::Handle<v8::Value> total_size(const v8::Arguments& args);
      static v8::Handle<v8::Value> set_num_pieces(const v8::Arguments& args);
      static v8::Handle<v8::Value> num_pieces(const v8::Arguments& args);

      // Wrapped object
      libtorrent::file_storage* obj_;
  };
};

#endif // NODE_LIBTORRENT_FILE_STORAGE_HPP_INCLUDED
