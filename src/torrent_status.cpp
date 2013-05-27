#include <v8.h>
#include <node.h>

#include <libtorrent/torrent_handle.hpp>
#include <libtorrent/bitfield.hpp>

#include "torrent_handle.hpp"
#include "torrent_status.hpp"


using namespace v8;
using namespace node;


namespace nodelt {
  Local<Array> bitfield_to_array(libtorrent::bitfield& bf_) {
    Local<Array> ret = Array::New();
    for (libtorrent::bitfield::const_iterator i(bf_.begin()), e(bf_.end()); i != e; ++i)
      ret->Set(ret->Length(), Boolean::New(*i));
    return ret;
  };

  Local<Object> time_duration_to_object(boost::posix_time::time_duration& td) {
    Local<Object> ret = Object::New();
    ret->Set(String::NewSymbol("seconds"),      Integer::New(td.total_seconds()));
    ret->Set(String::NewSymbol("milliseconds"), Integer::New(td.total_milliseconds()));
    ret->Set(String::NewSymbol("microseconds"), Integer::New(td.total_microseconds()));
    return ret;
  };

  Handle<Value> torrent_status_to_object(libtorrent::torrent_status& st_) {
    HandleScope scope;
    Local<Object> st = Object::New();

    st->Set(String::NewSymbol("handle"), TorrentHandleWrap::New(st_.handle));

    st->Set(String::NewSymbol("state"), Integer::New(st_.state));
    st->Set(String::NewSymbol("paused"), Boolean::New(st_.paused));
    st->Set(String::NewSymbol("auto_managed"), Boolean::New(st_.auto_managed));
    st->Set(String::NewSymbol("sequential_download"), Boolean::New(st_.sequential_download));
    st->Set(String::NewSymbol("seeding"), Boolean::New(st_.seeding));
    st->Set(String::NewSymbol("finished"), Boolean::New(st_.finished));
    st->Set(String::NewSymbol("progress"), Number::New(st_.progress));
    st->Set(String::NewSymbol("progressPpm"), Integer::New(st_.progress_ppm));
    st->Set(String::NewSymbol("error"), String::New(st_.error.c_str()));

    st->Set(String::NewSymbol("next_announce"), time_duration_to_object(st_.next_announce));
    st->Set(String::NewSymbol("announce_interval"), time_duration_to_object(st_.announce_interval));

    st->Set(String::NewSymbol("current_tracker"), String::New(st_.current_tracker.c_str()));

    st->Set(String::NewSymbol("total_download"), Uint32::NewFromUnsigned(st_.total_download));
    st->Set(String::NewSymbol("total_upload"), Uint32::NewFromUnsigned(st_.total_upload));

    st->Set(String::NewSymbol("total_payload_download"), Uint32::NewFromUnsigned(st_.total_payload_download));
    st->Set(String::NewSymbol("total_payload_upload"), Uint32::NewFromUnsigned(st_.total_payload_upload));

    st->Set(String::NewSymbol("total_failed_bytes"), Uint32::NewFromUnsigned(st_.total_failed_bytes));
    st->Set(String::NewSymbol("total_redundant_bytes"), Uint32::NewFromUnsigned(st_.total_redundant_bytes));

    st->Set(String::NewSymbol("download_rate"), Integer::New(st_.download_rate));
    st->Set(String::NewSymbol("upload_rate"), Integer::New(st_.upload_rate));

    st->Set(String::NewSymbol("download_payload_rate"), Integer::New(st_.download_payload_rate));
    st->Set(String::NewSymbol("upload_payload_rate"), Integer::New(st_.upload_payload_rate));

    st->Set(String::NewSymbol("num_peers"), Integer::New(st_.num_peers));

    st->Set(String::NewSymbol("num_complete"), Integer::New(st_.num_complete));
    st->Set(String::NewSymbol("num_incomplete"), Integer::New(st_.num_incomplete));

    st->Set(String::NewSymbol("list_seeds"), Integer::New(st_.list_seeds));
    st->Set(String::NewSymbol("list_peers"), Integer::New(st_.list_peers));

    st->Set(String::NewSymbol("connect_candidates"), Integer::New(st_.connect_candidates));

    st->Set(String::NewSymbol("pieces"), bitfield_to_array(st_.pieces));
    st->Set(String::NewSymbol("verified_pieces"), bitfield_to_array(st_.verified_pieces));

    st->Set(String::NewSymbol("num_pieces"), Integer::New(st_.num_pieces));

    st->Set(String::NewSymbol("total_done"), Uint32::NewFromUnsigned(st_.total_done));
    st->Set(String::NewSymbol("total_wanted_done"), Uint32::NewFromUnsigned(st_.total_wanted_done));
    st->Set(String::NewSymbol("total_wanted"), Uint32::NewFromUnsigned(st_.total_wanted));

    st->Set(String::NewSymbol("num_seeds"), Integer::New(st_.num_seeds));

    st->Set(String::NewSymbol("distributed_full_copies"), Integer::New(st_.distributed_full_copies));
    st->Set(String::NewSymbol("distributed_fraction"), Integer::New(st_.distributed_fraction));

    st->Set(String::NewSymbol("distributed_copies"), Number::New(st_.distributed_copies));

    st->Set(String::NewSymbol("block_size"), Integer::New(st_.block_size));

    st->Set(String::NewSymbol("num_uploads"), Integer::New(st_.num_uploads));
    st->Set(String::NewSymbol("num_connections"), Integer::New(st_.num_connections));
    st->Set(String::NewSymbol("uploads_limit"), Integer::New(st_.uploads_limit));
    st->Set(String::NewSymbol("connections_limit"), Integer::New(st_.connections_limit));

    st->Set(String::NewSymbol("storage_mode"), Integer::New(st_.storage_mode));

    st->Set(String::NewSymbol("up_bandwidth_queue"), Integer::New(st_.up_bandwidth_queue));
    st->Set(String::NewSymbol("down_bandwidth_queue"), Integer::New(st_.down_bandwidth_queue));

    st->Set(String::NewSymbol("all_time_upload"), Uint32::NewFromUnsigned(st_.all_time_upload));
    st->Set(String::NewSymbol("all_time_download"), Uint32::NewFromUnsigned(st_.all_time_download));

    st->Set(String::NewSymbol("active_time"), Integer::New(st_.active_time));
    st->Set(String::NewSymbol("finished_time"), Integer::New(st_.finished_time));
    st->Set(String::NewSymbol("seeding_time"), Integer::New(st_.seeding_time));

    st->Set(String::NewSymbol("seed_rank"), Integer::New(st_.seed_rank));

    st->Set(String::NewSymbol("last_scrape"), Integer::New(st_.last_scrape));

    st->Set(String::NewSymbol("has_incoming"), Boolean::New(st_.has_incoming));

    st->Set(String::NewSymbol("sparse_regions"), Integer::New(st_.sparse_regions));

    st->Set(String::NewSymbol("seed_mode"), Boolean::New(st_.seed_mode));
    st->Set(String::NewSymbol("upload_mode"), Boolean::New(st_.upload_mode));
    st->Set(String::NewSymbol("share_mode"), Boolean::New(st_.share_mode));
    st->Set(String::NewSymbol("super_seeding"), Boolean::New(st_.super_seeding));

    st->Set(String::NewSymbol("priority"), Integer::New(st_.priority));

    st->Set(String::NewSymbol("added_time"), Date::New(((double) st_.added_time)*1000));
    st->Set(String::NewSymbol("completed_time"), Date::New(((double) st_.completed_time)*1000));
    st->Set(String::NewSymbol("last_seen_complete"), Date::New(((double) st_.last_seen_complete)*1000));

    st->Set(String::NewSymbol("time_since_upload"), Integer::New(st_.time_since_upload));
    st->Set(String::NewSymbol("time_since_download"), Integer::New(st_.time_since_download));

    st->Set(String::NewSymbol("queue_position"), Integer::New(st_.queue_position));
    st->Set(String::NewSymbol("need_save_resume"), Boolean::New(st_.need_save_resume));
    st->Set(String::NewSymbol("ip_filter_applies"), Boolean::New(st_.ip_filter_applies));

    std::string info_hash = libtorrent::to_hex(st_.info_hash.to_string());
    st->Set(String::NewSymbol("info_hash"), String::New(info_hash.c_str()));

    st->Set(String::NewSymbol("listen_port"), Integer::New(st_.listen_port));

    return scope.Close(st);
  };

  void bind_torrent_status(Handle<Object> target) {
    // set libtorrent::torrent_status::state_t
    Local<Object> state_t = Object::New();
    state_t->Set(String::NewSymbol("queued_for_checking"),
      Integer::New(libtorrent::torrent_status::queued_for_checking));
    state_t->Set(String::NewSymbol("checking_files"),
      Integer::New(libtorrent::torrent_status::checking_files));
    state_t->Set(String::NewSymbol("downloading_metadata"),
      Integer::New(libtorrent::torrent_status::downloading_metadata));
    state_t->Set(String::NewSymbol("downloading"),
      Integer::New(libtorrent::torrent_status::downloading));
    state_t->Set(String::NewSymbol("finished"),
      Integer::New(libtorrent::torrent_status::finished));
    state_t->Set(String::NewSymbol("seeding"),
      Integer::New(libtorrent::torrent_status::seeding));
    state_t->Set(String::NewSymbol("allocating"),
      Integer::New(libtorrent::torrent_status::allocating));
    state_t->Set(String::NewSymbol("checking_resume_data"),
      Integer::New(libtorrent::torrent_status::checking_resume_data));
    target->Set(String::NewSymbol("states"), state_t);
  };
}; // namespace nodelt
