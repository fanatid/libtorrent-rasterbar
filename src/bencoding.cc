#include <libtorrent/bencode.hpp>
#include <libtorrent-rasterbar/bencoding.h>
#include <libtorrent-rasterbar/macros.h>

namespace libtorrent_rasterbar {

int BufferToBDecodeNode(v8::Local<v8::Value> buffer, libtorrent::bdecode_node& bnode) {
  char const* start = node::Buffer::Data(buffer);
  char const* end = start + node::Buffer::Length(buffer);
  boost::system::error_code ec;

  if (libtorrent::bdecode(start, end, bnode, ec) != 0) {
    Nan::ThrowError(ec.message().c_str());
    return 1;
  }

  return 0;
}

// TODO: remove recursion
int ValueToEntry(v8::Local<v8::Value> value, libtorrent::entry& entry) {
  Nan::HandleScope scope;

  if (value->IsNumber()) {
    entry = (libtorrent::entry::integer_type) value->IntegerValue();
  } else if (value->IsString()) {
    entry = std::string(*Nan::Utf8String(value));
  } else if (value->IsArray()) {
    libtorrent::entry::list_type list;
    v8::Local<v8::Object> obj = value->ToObject();
    for (uint32_t i = 0, length = v8::Local<v8::Array>::Cast(value)->Length(); i < length; ++i) {
      v8::Local<v8::Value> objValue = Nan::Get(obj, i).ToLocalChecked();
      libtorrent::entry item;
      if (ValueToEntry(objValue, item) != 0) return 1;
      list.push_back(item);
    }
    entry = list;
  } else if (value->IsObject()) {
    if (node::Buffer::HasInstance(value)) {
      entry = std::string(node::Buffer::Data(value), node::Buffer::Length(value));
    } else {
      libtorrent::entry::dictionary_type dict;
      v8::Local<v8::Object> obj = value->ToObject();
      v8::Local<v8::Array> keys = Nan::GetOwnPropertyNames(obj).ToLocalChecked();
      for (uint32_t i = 0, length = keys->Length(); i < length; ++i) {
        v8::Local<v8::Value> key = Nan::Get(keys, i).ToLocalChecked();
        v8::Local<v8::Value> objValue = Nan::Get(obj, key).ToLocalChecked();
        libtorrent::entry item;
        if (ValueToEntry(objValue, item) != 0) return 1;
        dict.insert(std::make_pair(std::string(*Nan::Utf8String(key)), item));
      }
      entry = dict;
    }
  } else {
    Nan::ThrowTypeError("Unknow bencoding type");
    return 1;
  }

  return 0;
}

// TODO: remove recursion
v8::Local<v8::Value> EntryToValue(libtorrent::entry& entry) {
  Nan::EscapableHandleScope scope;

  switch (entry.type()) {
    case libtorrent::entry::int_t: {
      return scope.Escape(v8::Local<v8::Value>::Cast(Nan::New<v8::Number>(entry.integer())));
    }

    case libtorrent::entry::string_t: {
      v8::Local<v8::Object> buffer = Nan::CopyBuffer(entry.string().c_str(), entry.string().size()).ToLocalChecked();
      return scope.Escape(v8::Local<v8::Value>::Cast(buffer));
    }

    case libtorrent::entry::list_t: {
      v8::Local<v8::Array> list = Nan::New<v8::Array>();
      for (auto it = entry.list().begin(), end = entry.list().end(); it != end; ++it) {
        Nan::Set(list, list->Length(), EntryToValue(*it));
      }
      return scope.Escape(v8::Local<v8::Value>::Cast(list));
    }

    case libtorrent::entry::dictionary_t: {
      v8::Local<v8::Object> dict = Nan::New<v8::Object>();
      for (auto it = entry.dict().begin(), end = entry.dict().end(); it != end; ++it) {
        Nan::Set(dict, Nan::New(it->first.c_str()).ToLocalChecked(), EntryToValue(it->second));
      }
      return scope.Escape(v8::Local<v8::Value>::Cast(dict));
    }

    default: {
      return scope.Escape(v8::Local<v8::Value>::Cast(Nan::New<v8::Object>()));
    }
  }
}

NAN_METHOD(BEncode) {
  REQUIRE_ARGUMENTS(1);

  libtorrent::entry entry;
  if (ValueToEntry(info[0], entry) != 0) return;

  std::vector<char> data;
  libtorrent::bencode(std::back_inserter(data), entry);

  Nan::MaybeLocal<v8::Object> buffer = Nan::CopyBuffer(&*data.begin(), data.size());
  info.GetReturnValue().Set(buffer.ToLocalChecked());
}

NAN_METHOD(BDecode) {
  if (!ARGUMENTS_IS_BUFFER(0)) {
    return Nan::ThrowTypeError("Argument 0 must be a Buffer");
  }

  libtorrent::bdecode_node node;
  if (BufferToBDecodeNode(info[0], node) != 0) return;

  libtorrent::entry entry;
  entry = node;
  info.GetReturnValue().Set(EntryToValue(entry));
}

} // namespace libtorrent_rasterbar
