#ifndef NODE_LIBTORRENT_FILE_STORAGE_HPP_INCLUDED
#define NODE_LIBTORRENT_FILE_STORAGE_HPP_INCLUDED

#include <v8.h>
#include <node.h>

#include <libtorrent/file_storage.hpp>


namespace nodelt {
  v8::Local<v8::Object> file_entry_to_object(const libtorrent::file_entry& e);
  libtorrent::file_entry file_entry_from_object(v8::Local<v8::Object> obj);

  v8::Local<v8::Object> file_slice_to_object(const libtorrent::file_slice& fs);

  class FileStorageWrap: public node::ObjectWrap {
    public:
      static void Initialize(v8::Handle<v8::Object> target);
      static v8::Local<v8::Object> New(const libtorrent::file_storage& fs);
      static libtorrent::file_storage* Unwrap(const v8::Local<v8::Object>& obj) {
        return node::ObjectWrap::Unwrap<FileStorageWrap>(obj)->obj_;
      };

    private:
      libtorrent::file_storage* obj_;
      FileStorageWrap();
      ~FileStorageWrap();
      static v8::Persistent<v8::Function> constructor;
      static v8::Handle<v8::Value> NewInstance(const v8::Arguments& args);

      static v8::Handle<v8::Value> is_valid(const v8::Arguments& args);
      static v8::Handle<v8::Value> add_file(const v8::Arguments& args);
      static v8::Handle<v8::Value> num_files(const v8::Arguments& args);
      static v8::Handle<v8::Value> at(const v8::Arguments& args);
      static v8::Handle<v8::Value> total_size(const v8::Arguments& args);
      static v8::Handle<v8::Value> set_num_pieces(const v8::Arguments& args);
      static v8::Handle<v8::Value> num_pieces(const v8::Arguments& args);
      static v8::Handle<v8::Value> set_piece_length(const v8::Arguments& args);
      static v8::Handle<v8::Value> piece_length(const v8::Arguments& args);
      static v8::Handle<v8::Value> piece_size(const v8::Arguments& args);
      static v8::Handle<v8::Value> set_name(const v8::Arguments& args);
      static v8::Handle<v8::Value> rename_file(const v8::Arguments& args);
      static v8::Handle<v8::Value> name(const v8::Arguments& args);
  };
};

#endif // NODE_LIBTORRENT_FILE_STORAGE_HPP_INCLUDED
