#include <v8.h>
#include <node.h>

#include <libtorrent/torrent_handle.hpp>
#include <libtorrent/bitfield.hpp>

#include "torrent_handle.hpp"
#include "torrent_status.hpp"


using namespace v8;
using namespace node;


namespace nodelt {
  Local<Array> bitfield_to_array(libtorrent::bitfield& bf) {
    HandleScope scope;

    Local<Array> obj = Array::New();
    for (libtorrent::bitfield::const_iterator i(bf.begin()), e(bf.end()); i != e; ++i)
      obj->Set(obj->Length(), Boolean::New(*i));

    return scope.Close(obj);
  };

  Local<Object> time_duration_to_object(boost::posix_time::time_duration& td) {
    HandleScope scope;

    Local<Object> obj = Object::New();
    obj->Set(String::NewSymbol("seconds"),      Integer::New(td.total_seconds()));
    obj->Set(String::NewSymbol("milliseconds"), Integer::New(td.total_milliseconds()));
    obj->Set(String::NewSymbol("microseconds"), Integer::New(td.total_microseconds()));

    return scope.Close(obj);
  };

  Handle<Value> torrent_status_to_object(libtorrent::torrent_status& st) {
    HandleScope scope;
    Local<Object> obj = Object::New();

    obj->Set(String::NewSymbol("handle"), TorrentHandleWrap::New(st.handle));

    obj->Set(String::NewSymbol("state"), Integer::New(st.state));
    obj->Set(String::NewSymbol("paused"), Boolean::New(st.paused));
    obj->Set(String::NewSymbol("auto_managed"), Boolean::New(st.auto_managed));
    obj->Set(String::NewSymbol("sequential_download"), Boolean::New(st.sequential_download));
    obj->Set(String::NewSymbol("seeding"), Boolean::New(st.seeding));
    obj->Set(String::NewSymbol("finished"), Boolean::New(st.finished));
    obj->Set(String::NewSymbol("progress"), Number::New(st.progress));
    obj->Set(String::NewSymbol("progressPpm"), Integer::New(st.progress_ppm));
    obj->Set(String::NewSymbol("error"), String::New(st.error.c_str()));

    obj->Set(String::NewSymbol("next_announce"), time_duration_to_object(st.next_announce));
    obj->Set(String::NewSymbol("announce_interval"), time_duration_to_object(st.announce_interval));

    obj->Set(String::NewSymbol("current_tracker"), String::New(st.current_tracker.c_str()));

    obj->Set(String::NewSymbol("total_download"), Uint32::NewFromUnsigned(st.total_download));
    obj->Set(String::NewSymbol("total_upload"), Uint32::NewFromUnsigned(st.total_upload));

    obj->Set(String::NewSymbol("total_payload_download"), Uint32::NewFromUnsigned(st.total_payload_download));
    obj->Set(String::NewSymbol("total_payload_upload"), Uint32::NewFromUnsigned(st.total_payload_upload));

    obj->Set(String::NewSymbol("total_failed_bytes"), Uint32::NewFromUnsigned(st.total_failed_bytes));
    obj->Set(String::NewSymbol("total_redundant_bytes"), Uint32::NewFromUnsigned(st.total_redundant_bytes));

    obj->Set(String::NewSymbol("download_rate"), Integer::New(st.download_rate));
    obj->Set(String::NewSymbol("upload_rate"), Integer::New(st.upload_rate));

    obj->Set(String::NewSymbol("download_payload_rate"), Integer::New(st.download_payload_rate));
    obj->Set(String::NewSymbol("upload_payload_rate"), Integer::New(st.upload_payload_rate));

    obj->Set(String::NewSymbol("num_peers"), Integer::New(st.num_peers));

    obj->Set(String::NewSymbol("num_complete"), Integer::New(st.num_complete));
    obj->Set(String::NewSymbol("num_incomplete"), Integer::New(st.num_incomplete));

    obj->Set(String::NewSymbol("list_seeds"), Integer::New(st.list_seeds));
    obj->Set(String::NewSymbol("list_peers"), Integer::New(st.list_peers));

    obj->Set(String::NewSymbol("connect_candidates"), Integer::New(st.connect_candidates));

    obj->Set(String::NewSymbol("pieces"), bitfield_to_array(st.pieces));
    obj->Set(String::NewSymbol("verified_pieces"), bitfield_to_array(st.verified_pieces));

    obj->Set(String::NewSymbol("num_pieces"), Integer::New(st.num_pieces));

    obj->Set(String::NewSymbol("total_done"), Uint32::NewFromUnsigned(st.total_done));
    obj->Set(String::NewSymbol("total_wanted_done"), Uint32::NewFromUnsigned(st.total_wanted_done));
    obj->Set(String::NewSymbol("total_wanted"), Uint32::NewFromUnsigned(st.total_wanted));

    obj->Set(String::NewSymbol("num_seeds"), Integer::New(st.num_seeds));

    obj->Set(String::NewSymbol("distributed_full_copies"), Integer::New(st.distributed_full_copies));
    obj->Set(String::NewSymbol("distributed_fraction"), Integer::New(st.distributed_fraction));

    obj->Set(String::NewSymbol("distributed_copies"), Number::New(st.distributed_copies));

    obj->Set(String::NewSymbol("block_size"), Integer::New(st.block_size));

    obj->Set(String::NewSymbol("num_uploads"), Integer::New(st.num_uploads));
    obj->Set(String::NewSymbol("num_connections"), Integer::New(st.num_connections));
    obj->Set(String::NewSymbol("uploads_limit"), Integer::New(st.uploads_limit));
    obj->Set(String::NewSymbol("connections_limit"), Integer::New(st.connections_limit));

    obj->Set(String::NewSymbol("storage_mode"), Integer::New(st.storage_mode));

    obj->Set(String::NewSymbol("up_bandwidth_queue"), Integer::New(st.up_bandwidth_queue));
    obj->Set(String::NewSymbol("down_bandwidth_queue"), Integer::New(st.down_bandwidth_queue));

    obj->Set(String::NewSymbol("all_time_upload"), Uint32::NewFromUnsigned(st.all_time_upload));
    obj->Set(String::NewSymbol("all_time_download"), Uint32::NewFromUnsigned(st.all_time_download));

    obj->Set(String::NewSymbol("active_time"), Integer::New(st.active_time));
    obj->Set(String::NewSymbol("finished_time"), Integer::New(st.finished_time));
    obj->Set(String::NewSymbol("seeding_time"), Integer::New(st.seeding_time));

    obj->Set(String::NewSymbol("seed_rank"), Integer::New(st.seed_rank));

    obj->Set(String::NewSymbol("last_scrape"), Integer::New(st.last_scrape));

    obj->Set(String::NewSymbol("has_incoming"), Boolean::New(st.has_incoming));

    obj->Set(String::NewSymbol("sparse_regions"), Integer::New(st.sparse_regions));

    obj->Set(String::NewSymbol("seed_mode"), Boolean::New(st.seed_mode));
    obj->Set(String::NewSymbol("upload_mode"), Boolean::New(st.upload_mode));
    obj->Set(String::NewSymbol("share_mode"), Boolean::New(st.share_mode));
    obj->Set(String::NewSymbol("super_seeding"), Boolean::New(st.super_seeding));

    obj->Set(String::NewSymbol("priority"), Integer::New(st.priority));

    obj->Set(String::NewSymbol("added_time"), Date::New(((double) st.added_time)*1000));
    obj->Set(String::NewSymbol("completed_time"), Date::New(((double) st.completed_time)*1000));
    obj->Set(String::NewSymbol("last_seen_complete"), Date::New(((double) st.last_seen_complete)*1000));

    obj->Set(String::NewSymbol("time_since_upload"), Integer::New(st.time_since_upload));
    obj->Set(String::NewSymbol("time_since_download"), Integer::New(st.time_since_download));

    obj->Set(String::NewSymbol("queue_position"), Integer::New(st.queue_position));
    obj->Set(String::NewSymbol("need_save_resume"), Boolean::New(st.need_save_resume));
    obj->Set(String::NewSymbol("ip_filter_applies"), Boolean::New(st.ip_filter_applies));

    std::string info_hash = libtorrent::to_hex(st.info_hash.to_string());
    obj->Set(String::NewSymbol("info_hash"), String::New(info_hash.c_str()));

    obj->Set(String::NewSymbol("listen_port"), Integer::New(st.listen_port));

    return scope.Close(obj);
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
