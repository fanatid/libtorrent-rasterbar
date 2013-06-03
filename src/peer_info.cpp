#include <v8.h>
#include <node.h>

#include <libtorrent/peer_info.hpp>

#include "peer_info.hpp"

using namespace v8;
using namespace node;


namespace nodelt {
  Local<Array> get_tcp_endpoint(const libtorrent::tcp::endpoint& ep) {
    HandleScope scope;

    Local<Array> ret = Array::New();
    ret->Set(0, String::New(ep.address().to_string().c_str()));
    ret->Set(1, Integer::New(ep.port()));
    return scope.Close(ret);
  };

  Local<Array> get_pieces(const libtorrent::peer_info& pi) {
    HandleScope scope;

    Local<Array> ret = Array::New();
    for (libtorrent::bitfield::const_iterator
         i(pi.pieces.begin()), e(pi.pieces.end()); i != e; ++i)
      ret->Set(ret->Length(), Integer::New(*i));
    return scope.Close(ret);
  };

  Local<Object> peer_info_to_object(const libtorrent::peer_info& pi) {
    HandleScope scope;
    Local<Object> obj = Object::New();

    obj->Set(String::NewSymbol("falgs"), Uint32::New(pi.flags));
    obj->Set(String::NewSymbol("source"), Integer::New(pi.source));
    obj->Set(String::NewSymbol("read_state"), Integer::New(pi.read_state));
    obj->Set(String::NewSymbol("write_state"), Integer::New(pi.write_state));
    obj->Set(String::NewSymbol("ip"), get_tcp_endpoint(pi.ip));
    obj->Set(String::NewSymbol("up_speed"), Integer::New(pi.up_speed));
    obj->Set(String::NewSymbol("down_speed"), Integer::New(pi.down_speed));
    obj->Set(String::NewSymbol("payload_up_speed"), Integer::New(pi.payload_up_speed));
    obj->Set(String::NewSymbol("payload_down_speed"), Integer::New(pi.payload_down_speed));
    obj->Set(String::NewSymbol("total_download"), Integer::New(pi.total_download));
    obj->Set(String::NewSymbol("total_upload"), Integer::New(pi.total_upload));
    obj->Set(String::NewSymbol("pid"),
      String::New(libtorrent::to_hex(pi.pid.to_string()).c_str()));
    obj->Set(String::NewSymbol("pieces"), get_pieces(pi));
    obj->Set(String::NewSymbol("upload_limit"), Integer::New(pi.upload_limit));
    obj->Set(String::NewSymbol("download_limit"), Integer::New(pi.download_limit));
    obj->Set(String::NewSymbol("last_request"),
      Integer::New(libtorrent::total_seconds(pi.last_request)));
    obj->Set(String::NewSymbol("last_active"),
      Integer::New(libtorrent::total_seconds(pi.last_active)));
    obj->Set(String::NewSymbol("download_queue_time"),
      Integer::New(libtorrent::total_seconds(pi.download_queue_time)));
    obj->Set(String::NewSymbol("queue_bytes"), Integer::New(pi.queue_bytes));
    obj->Set(String::NewSymbol("request_timeout"), Integer::New(pi.request_timeout));
    obj->Set(String::NewSymbol("send_buffer_size"), Integer::New(pi.send_buffer_size));
    obj->Set(String::NewSymbol("used_send_buffer"), Integer::New(pi.used_send_buffer));
    obj->Set(String::NewSymbol("receive_buffer_size"), Integer::New(pi.receive_buffer_size));
    obj->Set(String::NewSymbol("used_receive_buffer"), Integer::New(pi.used_receive_buffer));
    obj->Set(String::NewSymbol("num_hashfails"), Integer::New(pi.num_hashfails));
#ifndef TORRENT_DISABLE_RESOLVE_COUNTRIES
    obj->Set(String::NewSymbol("country"), String::New(pi.country));
#endif
#ifndef TORRENT_DISABLE_GEO_IP
    obj->Set(String::NewSymbol("inet_as_name"), String::New(pi.inet_as_name.c_str()));
    obj->Set(String::NewSymbol("inet_as"), Integer::New(pi.inet_as));
#endif
    obj->Set(String::NewSymbol("load_balancing"), Integer::New(pi.load_balancing));
    obj->Set(String::NewSymbol("download_queue_length"), Integer::New(pi.download_queue_length));
    obj->Set(String::NewSymbol("timed_out_requests"), Integer::New(pi.timed_out_requests));
    obj->Set(String::NewSymbol("busy_requests"), Integer::New(pi.busy_requests));
    obj->Set(String::NewSymbol("requests_in_buffer"), Integer::New(pi.requests_in_buffer));
    obj->Set(String::NewSymbol("target_dl_queue_length"), Integer::New(pi.target_dl_queue_length));
    obj->Set(String::NewSymbol("upload_queue_length"), Integer::New(pi.upload_queue_length));
    obj->Set(String::NewSymbol("failcount"), Integer::New(pi.failcount));
    obj->Set(String::NewSymbol("downloading_piece_index"), Integer::New(pi.downloading_piece_index));
    obj->Set(String::NewSymbol("downloading_block_index"), Integer::New(pi.downloading_block_index));
    obj->Set(String::NewSymbol("downloading_progress"), Integer::New(pi.downloading_progress));
    obj->Set(String::NewSymbol("downloading_total"), Integer::New(pi.downloading_total));
    obj->Set(String::NewSymbol("client"), String::New(pi.client.c_str()));
    obj->Set(String::NewSymbol("connection_type"), Integer::New(pi.connection_type));
    obj->Set(String::NewSymbol("remote_dl_rate"), Integer::New(pi.remote_dl_rate));
    obj->Set(String::NewSymbol("pending_disk_bytes"), Integer::New(pi.pending_disk_bytes));
    obj->Set(String::NewSymbol("send_quota"), Integer::New(pi.send_quota));
    obj->Set(String::NewSymbol("receive_quota"), Integer::New(pi.receive_quota));
    obj->Set(String::NewSymbol("rtt"), Integer::New(pi.rtt));
    obj->Set(String::NewSymbol("num_pieces"), Integer::New(pi.num_pieces));
    obj->Set(String::NewSymbol("download_rate_peak"), Integer::New(pi.download_rate_peak));
    obj->Set(String::NewSymbol("upload_rate_peak"), Integer::New(pi.upload_rate_peak));
    obj->Set(String::NewSymbol("progress"), Number::New(pi.progress));
    obj->Set(String::NewSymbol("progress_ppm"), Integer::New(pi.progress_ppm));
    obj->Set(String::NewSymbol("estimated_reciprocation_rate"), Integer::New(pi.estimated_reciprocation_rate));
    obj->Set(String::NewSymbol("local_endpoint"), get_tcp_endpoint(pi.local_endpoint));

    return scope.Close(obj);
  }

  void bind_peer_info(Handle<Object> target) {
    // set flags
    Local<Object> obj = Object::New();

    obj->Set(String::NewSymbol("interesting"), Integer::New(libtorrent::peer_info::interesting));
    obj->Set(String::NewSymbol("choked"), Integer::New(libtorrent::peer_info::choked));
    obj->Set(String::NewSymbol("remote_interested"), Integer::New(libtorrent::peer_info::remote_interested));
    obj->Set(String::NewSymbol("remote_choked"), Integer::New(libtorrent::peer_info::remote_choked));
    obj->Set(String::NewSymbol("supports_extensions"), Integer::New(libtorrent::peer_info::supports_extensions));
    obj->Set(String::NewSymbol("local_connection"), Integer::New(libtorrent::peer_info::local_connection));
    obj->Set(String::NewSymbol("handshake"), Integer::New(libtorrent::peer_info::handshake));
    obj->Set(String::NewSymbol("connecting"), Integer::New(libtorrent::peer_info::connecting));
    obj->Set(String::NewSymbol("on_parole"), Integer::New(libtorrent::peer_info::on_parole));
    obj->Set(String::NewSymbol("seed"), Integer::New(libtorrent::peer_info::seed));
    obj->Set(String::NewSymbol("optimistic_unchoke"), Integer::New(libtorrent::peer_info::optimistic_unchoke));
    obj->Set(String::NewSymbol("snubbed"), Integer::New(libtorrent::peer_info::snubbed));
    obj->Set(String::NewSymbol("upload_only"), Integer::New(libtorrent::peer_info::upload_only));
    obj->Set(String::NewSymbol("endgame_mode"), Integer::New(libtorrent::peer_info::endgame_mode));
    obj->Set(String::NewSymbol("holepunched"), Integer::New(libtorrent::peer_info::holepunched));
#ifndef TORRENT_DISABLE_ENCRYPTION
    obj->Set(String::NewSymbol("rc4_encrypted"), Integer::New(libtorrent::peer_info::rc4_encrypted));
    obj->Set(String::NewSymbol("plaintext_encrypted"), Integer::New(libtorrent::peer_info::plaintext_encrypted));
#endif

    obj->Set(String::NewSymbol("standard_bittorrent"), Integer::New(libtorrent::peer_info::standard_bittorrent));
    obj->Set(String::NewSymbol("web_seed"), Integer::New(libtorrent::peer_info::web_seed));

    obj->Set(String::NewSymbol("tracker"), Integer::New(libtorrent::peer_info::tracker));
    obj->Set(String::NewSymbol("dht"), Integer::New(libtorrent::peer_info::dht));
    obj->Set(String::NewSymbol("pex"), Integer::New(libtorrent::peer_info::pex));
    obj->Set(String::NewSymbol("lsd"), Integer::New(libtorrent::peer_info::lsd));
    obj->Set(String::NewSymbol("resume_data"), Integer::New(libtorrent::peer_info::resume_data));
    obj->Set(String::NewSymbol("incoming"), Integer::New(libtorrent::peer_info::incoming));

    obj->Set(String::NewSymbol("bw_idle"), Integer::New(libtorrent::peer_info::bw_idle));
    obj->Set(String::NewSymbol("bw_limit"), Integer::New(libtorrent::peer_info::bw_limit));
    obj->Set(String::NewSymbol("bw_network"), Integer::New(libtorrent::peer_info::bw_network));
    obj->Set(String::NewSymbol("bw_disk"), Integer::New(libtorrent::peer_info::bw_disk));

    target->Set(String::NewSymbol("peer_info"), obj);
  };
}; // namespace nodelt
