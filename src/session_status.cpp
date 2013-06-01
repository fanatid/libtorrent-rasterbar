#include <v8.h>

#include <libtorrent/session_status.hpp>

#include "session_status.hpp"

using namespace v8;


namespace nodelt {
#ifndef TORRENT_DISABLE_DHT
  Local<Object> dht_lookup_to_object(const libtorrent::dht_lookup& dht) {
    HandleScope scope;
    Local<Object> obj = Object::New();

    obj->Set(String::NewSymbol("type"), String::New(dht.type));
    obj->Set(String::NewSymbol("outstanding_requests"), Integer::New(dht.outstanding_requests));
    obj->Set(String::NewSymbol("timeouts"), Integer::New(dht.timeouts));
    obj->Set(String::NewSymbol("responses"), Integer::New(dht.responses));
    obj->Set(String::NewSymbol("branch_factor"), Integer::New(dht.branch_factor));
    obj->Set(String::NewSymbol("nodes_left"), Integer::New(dht.nodes_left));
    obj->Set(String::NewSymbol("last_sent"), Integer::New(dht.last_sent));
    obj->Set(String::NewSymbol("first_timeout"), Integer::New(dht.first_timeout));

    return scope.Close(obj);
  };

  Local<Object> dht_routing_bucket_to_object(const libtorrent::dht_routing_bucket& dht) {
    HandleScope scope;
    Local<Object> obj = Object::New();

    obj->Set(String::NewSymbol("num_nodes"), Integer::New(dht.num_nodes));
    obj->Set(String::NewSymbol("num_replacements"), Integer::New(dht.num_replacements));
    obj->Set(String::NewSymbol("last_active"), Integer::New(dht.last_active));

    return scope.Close(obj);
  };
#endif

  Local<Object> utp_status_to_object(const libtorrent::utp_status& st) {
    HandleScope scope;
    Local<Object> obj = Object::New();

    obj->Set(String::NewSymbol("num_idle"), Integer::New(st.num_idle));
    obj->Set(String::NewSymbol("num_syn_sent"), Integer::New(st.num_syn_sent));
    obj->Set(String::NewSymbol("num_connected"), Integer::New(st.num_connected));
    obj->Set(String::NewSymbol("num_fin_sent"), Integer::New(st.num_fin_sent));
    obj->Set(String::NewSymbol("num_close_wait"), Integer::New(st.num_close_wait));

    return scope.Close(obj);
  };

  Local<Object> session_status_to_object(const libtorrent::session_status& st) {
    HandleScope scope;
    Local<Object> obj = Object::New();

    obj->Set(String::NewSymbol("has_incoming_connections"), Boolean::New(st.has_incoming_connections));

    obj->Set(String::NewSymbol("upload_rate"), Integer::New(st.upload_rate));
    obj->Set(String::NewSymbol("download_rate"), Integer::New(st.upload_rate));
    obj->Set(String::NewSymbol("total_download"), Integer::New(st.total_download));
    obj->Set(String::NewSymbol("total_upload"), Integer::New(st.total_upload));

    obj->Set(String::NewSymbol("payload_upload_rate"), Integer::New(st.payload_upload_rate));
    obj->Set(String::NewSymbol("payload_download_rate"), Integer::New(st.payload_download_rate));
    obj->Set(String::NewSymbol("total_payload_download"), Integer::New(st.total_payload_download));
    obj->Set(String::NewSymbol("total_payload_upload"), Integer::New(st.total_payload_upload));

    obj->Set(String::NewSymbol("ip_overhead_upload_rate"), Integer::New(st.ip_overhead_upload_rate));
    obj->Set(String::NewSymbol("ip_overhead_download_rate"), Integer::New(st.ip_overhead_download_rate));
    obj->Set(String::NewSymbol("total_ip_overhead_download"), Integer::New(st.total_ip_overhead_download));
    obj->Set(String::NewSymbol("total_ip_overhead_upload"), Integer::New(st.total_ip_overhead_upload));

    obj->Set(String::NewSymbol("dht_upload_rate"), Integer::New(st.dht_upload_rate));
    obj->Set(String::NewSymbol("dht_download_rate"), Integer::New(st.dht_download_rate));
    obj->Set(String::NewSymbol("total_dht_download"), Integer::New(st.total_dht_download));
    obj->Set(String::NewSymbol("total_dht_upload"), Integer::New(st.total_dht_upload));

    obj->Set(String::NewSymbol("tracker_upload_rate"), Integer::New(st.tracker_upload_rate));
    obj->Set(String::NewSymbol("tracker_download_rate"), Integer::New(st.tracker_download_rate));
    obj->Set(String::NewSymbol("total_tracker_download"), Integer::New(st.total_tracker_download));
    obj->Set(String::NewSymbol("total_tracker_upload"), Integer::New(st.total_tracker_upload));

    obj->Set(String::NewSymbol("total_redundant_bytes"), Integer::New(st.total_redundant_bytes));
    obj->Set(String::NewSymbol("total_failed_bytes"), Integer::New(st.total_failed_bytes));

    obj->Set(String::NewSymbol("num_peers"), Integer::New(st.num_peers));
    obj->Set(String::NewSymbol("num_unchoked"), Integer::New(st.num_unchoked));
    obj->Set(String::NewSymbol("allowed_upload_slots"), Integer::New(st.allowed_upload_slots));

    obj->Set(String::NewSymbol("up_bandwidth_queue"), Integer::New(st.up_bandwidth_queue));
    obj->Set(String::NewSymbol("down_bandwidth_queue"), Integer::New(st.down_bandwidth_queue));

    obj->Set(String::NewSymbol("up_bandwidth_bytes_queue"), Integer::New(st.up_bandwidth_bytes_queue));
    obj->Set(String::NewSymbol("down_bandwidth_bytes_queue"), Integer::New(st.down_bandwidth_bytes_queue));

    obj->Set(String::NewSymbol("optimistic_unchoke_counter"), Integer::New(st.optimistic_unchoke_counter));
    obj->Set(String::NewSymbol("unchoke_counter"), Integer::New(st.unchoke_counter));

    obj->Set(String::NewSymbol("disk_write_queue"), Integer::New(st.disk_write_queue));
    obj->Set(String::NewSymbol("disk_read_queue"), Integer::New(st.disk_read_queue));

#ifndef TORRENT_DISABLE_DHT
    obj->Set(String::NewSymbol("dht_nodes"), Integer::New(st.dht_nodes));
    obj->Set(String::NewSymbol("dht_node_cache"), Integer::New(st.dht_node_cache));
    obj->Set(String::NewSymbol("dht_torrents"), Integer::New(st.dht_torrents));
    obj->Set(String::NewSymbol("dht_global_nodes"), Integer::New(st.dht_global_nodes));

    Local<Array> active_requests = Array::New();
    for (std::vector<libtorrent::dht_lookup>::const_iterator
     i(st.active_requests.begin()), e(st.active_requests.end()); i != e; ++i)
      active_requests->Set(active_requests->Length(), dht_lookup_to_object(*i));
    obj->Set(String::NewSymbol("active_requests"), active_requests);

    Local<Array> dht_routing_table = Array::New();
    for (std::vector<libtorrent::dht_routing_bucket>::const_iterator
     i(st.dht_routing_table.begin()), e(st.dht_routing_table.end()); i != e; ++i)
      dht_routing_table->Set(active_requests->Length(), dht_routing_bucket_to_object(*i));
    obj->Set(String::NewSymbol("dht_routing_table"), dht_routing_table);

    obj->Set(String::NewSymbol("dht_total_allocations"), Integer::New(st.dht_total_allocations));
#endif

    obj->Set(String::NewSymbol("utp_stats"), utp_status_to_object(st.utp_stats));

    obj->Set(String::NewSymbol("peerlist_size"), Integer::New(st.peerlist_size));

    return scope.Close(obj);
  };
}; // namespace nodelt
