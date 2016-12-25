#include <libtorrent-rasterbar/torrent_info.h>
#include <libtorrent-rasterbar/macros.h>

namespace libtorrent_rasterbar {

Nan::Persistent<v8::FunctionTemplate> TorrentInfo::prototype;
Nan::Persistent<v8::Function> TorrentInfo::constructor;

v8::Local<v8::Function> TorrentInfo::Init() {
  Nan::EscapableHandleScope scope;

  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("TorrentInfo").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  v8::Local<v8::Function> cons = Nan::GetFunction(tpl).ToLocalChecked();
  TorrentInfo::prototype.Reset(tpl);
  TorrentInfo::constructor.Reset(cons);

  return scope.Escape(cons);
}

NAN_METHOD(TorrentInfo::New) {
  if (!info.IsConstructCall()) return;

  boost::shared_ptr<libtorrent::torrent_info> ti;
  boost::system::error_code ec;
  if (ARGUMENTS_IS_STRING(0)) {
    std::string filename(*Nan::Utf8String(info[0]));
    ti = boost::shared_ptr<libtorrent::torrent_info>(new libtorrent::torrent_info(filename, ec));
  } else if (ARGUMENTS_IS_BUFFER(0)) {
    const char* buffer = node::Buffer::Data(info[0]);
    int size = node::Buffer::Length(info[0]);
    ti = boost::shared_ptr<libtorrent::torrent_info>(new libtorrent::torrent_info(buffer, size, ec));
  } else {
    return Nan::ThrowTypeError("Arguments must be String or Buffer");
  }

  if (ec != boost::system::errc::success) {
    return Nan::ThrowError(ec.message().c_str());
  }

  TorrentInfo* obj = new TorrentInfo(ti);
  obj->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

} // namespace libtorrent_rasterbar
