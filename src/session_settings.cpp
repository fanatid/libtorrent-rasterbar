#include <v8.h>

#include <libtorrent/session_settings.hpp>

#include "session_settings.hpp"

using namespace v8;


namespace nodelt {
#ifndef TORRENT_DISABLE_DHT
  libtorrent::dht_settings const dht_settings_from_object(Handle<Object> obj) {
    libtorrent::dht_settings dht;

    if (obj->Has(String::NewSymbol("max_peers_reply")))
      dht.max_peers_reply = obj->Get(String::NewSymbol("max_peers_reply"))->IntegerValue();
    if (obj->Has(String::NewSymbol("search_branching")))
      dht.search_branching = obj->Get(String::NewSymbol("search_branching"))->IntegerValue();
    if (obj->Has(String::NewSymbol("max_fail_count")))
      dht.max_fail_count = obj->Get(String::NewSymbol("max_fail_count"))->IntegerValue();
    if (obj->Has(String::NewSymbol("max_torrents")))
      dht.max_torrents = obj->Get(String::NewSymbol("max_torrents"))->IntegerValue();
    if (obj->Has(String::NewSymbol("max_dht_items")))
      dht.max_dht_items = obj->Get(String::NewSymbol("max_dht_items"))->IntegerValue();
    if (obj->Has(String::NewSymbol("max_torrent_search_reply")))
      dht.max_torrent_search_reply = obj->Get(String::NewSymbol("max_torrent_search_reply"))->IntegerValue();
    if (obj->Has(String::NewSymbol("restrict_routing_ips")))
      dht.restrict_routing_ips = obj->Get(String::NewSymbol("restrict_routing_ips"))->BooleanValue();
    if (obj->Has(String::NewSymbol("restrict_search_ips")))
      dht.restrict_search_ips = obj->Get(String::NewSymbol("restrict_search_ips"))->BooleanValue();

    return dht;
  };
#endif

  Local<Object> proxy_settings_to_object(const libtorrent::proxy_settings& s) {
    HandleScope scope;
    Local<Object> obj = Object::New();

    obj->Set(String::NewSymbol("hostname"), String::New(s.hostname.c_str()));
    obj->Set(String::NewSymbol("port"), Integer::New(s.port));

    obj->Set(String::NewSymbol("username"), String::New(s.username.c_str()));
    obj->Set(String::NewSymbol("password"), String::New(s.password.c_str()));

    obj->Set(String::NewSymbol("type"), Integer::New(s.type));

    obj->Set(String::NewSymbol("proxy_hostnames"), Integer::New(s.proxy_hostnames));
    obj->Set(String::NewSymbol("proxy_peer_connections"), Integer::New(s.proxy_peer_connections));

    return scope.Close(obj);
  };

  libtorrent::proxy_settings proxy_settings_from_object(Local<Object> obj) {
    libtorrent::proxy_settings s;

    if (obj->Has(String::NewSymbol("hostname"))) {
      Local<Object> hostname = obj->Get(String::NewSymbol("hostname"))->ToObject();
      s.hostname = std::string(*String::Utf8Value(hostname));
    }
    if (obj->Has(String::NewSymbol("port")))
      s.port = obj->Get(String::NewSymbol("port"))->IntegerValue();

    if (obj->Has(String::NewSymbol("username"))) {
      Local<Object> username = obj->Get(String::NewSymbol("username"))->ToObject();
      s.username = std::string(*String::Utf8Value(username));
    }
    if (obj->Has(String::NewSymbol("password"))) {
      Local<Object> password = obj->Get(String::NewSymbol("password"))->ToObject();
      s.password = std::string(*String::Utf8Value(password));
    }

    if (obj->Has(String::NewSymbol("type")))
      s.type = (libtorrent::proxy_settings::proxy_type) obj->Get(String::NewSymbol("type"))->IntegerValue();

    if (obj->Has(String::NewSymbol("proxy_hostnames")))
      s.proxy_hostnames = obj->Get(String::NewSymbol("proxy_hostnames"))->BooleanValue();
    if (obj->Has(String::NewSymbol("proxy_peer_connections")))
      s.proxy_peer_connections = obj->Get(String::NewSymbol("proxy_peer_connections"))->BooleanValue();

    return s;
  };

  Local<Object> session_settings_to_object(const libtorrent::session_settings& s) {
    HandleScope scope;
    Local<Object> obj = Object::New();

    obj->Set(String::NewSymbol("version"), Integer::New(s.version));
    obj->Set(String::NewSymbol("user_agent"), String::New(s.user_agent.c_str()));
    obj->Set(String::NewSymbol("tracker_completion_timeout"), Integer::New(s.tracker_completion_timeout));
    obj->Set(String::NewSymbol("tracker_receive_timeout"), Integer::New(s.tracker_receive_timeout));
    obj->Set(String::NewSymbol("stop_tracker_timeout"), Integer::New(s.stop_tracker_timeout));
    obj->Set(String::NewSymbol("tracker_maximum_response_length"), Integer::New(s.tracker_maximum_response_length));
    obj->Set(String::NewSymbol("piece_timeout"), Integer::New(s.piece_timeout));
    obj->Set(String::NewSymbol("request_timeout"), Integer::New(s.request_timeout));
    obj->Set(String::NewSymbol("request_queue_time"), Integer::New(s.request_queue_time));
    obj->Set(String::NewSymbol("max_allowed_in_request_queue"), Integer::New(s.max_allowed_in_request_queue));
    obj->Set(String::NewSymbol("max_out_request_queue"), Integer::New(s.max_out_request_queue));
    obj->Set(String::NewSymbol("whole_pieces_threshold"), Integer::New(s.whole_pieces_threshold));
    obj->Set(String::NewSymbol("peer_timeout"), Integer::New(s.peer_timeout));
    obj->Set(String::NewSymbol("urlseed_timeout"), Integer::New(s.urlseed_timeout));
    obj->Set(String::NewSymbol("urlseed_pipeline_size"), Integer::New(s.urlseed_pipeline_size));
    obj->Set(String::NewSymbol("urlseed_wait_retry"), Integer::New(s.urlseed_wait_retry));
    obj->Set(String::NewSymbol("file_pool_size"), Integer::New(s.file_pool_size));
    obj->Set(String::NewSymbol("allow_multiple_connections_per_ip"), Boolean::New(s.allow_multiple_connections_per_ip));
    obj->Set(String::NewSymbol("max_failcount"), Integer::New(s.max_failcount));
    obj->Set(String::NewSymbol("min_reconnect_time"), Integer::New(s.min_reconnect_time));
    obj->Set(String::NewSymbol("peer_connect_timeout"), Integer::New(s.peer_connect_timeout));
    obj->Set(String::NewSymbol("ignore_limits_on_local_network"), Boolean::New(s.ignore_limits_on_local_network));
    obj->Set(String::NewSymbol("connection_speed"), Integer::New(s.connection_speed));
    obj->Set(String::NewSymbol("send_redundant_have"), Boolean::New(s.send_redundant_have));
    obj->Set(String::NewSymbol("lazy_bitfields"), Boolean::New(s.lazy_bitfields));
    obj->Set(String::NewSymbol("inactivity_timeout"), Integer::New(s.inactivity_timeout));
    obj->Set(String::NewSymbol("unchoke_interval"), Integer::New(s.unchoke_interval));
    obj->Set(String::NewSymbol("optimistic_unchoke_interval"), Integer::New(s.optimistic_unchoke_interval));
    obj->Set(String::NewSymbol("announce_ip"), String::New(s.announce_ip.c_str()));
    obj->Set(String::NewSymbol("num_want"), Integer::New(s.num_want));
    obj->Set(String::NewSymbol("initial_picker_threshold"), Integer::New(s.initial_picker_threshold));
    obj->Set(String::NewSymbol("allowed_fast_set_size"), Integer::New(s.allowed_fast_set_size));
    obj->Set(String::NewSymbol("suggest_mode"), Integer::New(s.suggest_mode));
    obj->Set(String::NewSymbol("max_queued_disk_bytes"), Integer::New(s.max_queued_disk_bytes));
    obj->Set(String::NewSymbol("max_queued_disk_bytes_low_watermark"), Integer::New(s.max_queued_disk_bytes_low_watermark));
    obj->Set(String::NewSymbol("handshake_timeout"), Integer::New(s.handshake_timeout));
#ifndef TORRENT_DISABLE_DHT
    obj->Set(String::NewSymbol("use_dht_as_fallback"), Boolean::New(s.use_dht_as_fallback));
#endif
    obj->Set(String::NewSymbol("free_torrent_hashes"), Boolean::New(s.free_torrent_hashes));
    obj->Set(String::NewSymbol("upnp_ignore_nonrouters"), Boolean::New(s.upnp_ignore_nonrouters));
    obj->Set(String::NewSymbol("send_buffer_low_watermark"), Integer::New(s.send_buffer_low_watermark));
    obj->Set(String::NewSymbol("send_buffer_watermark"), Integer::New(s.send_buffer_watermark));
    obj->Set(String::NewSymbol("send_buffer_watermark_factor"), Integer::New(s.send_buffer_watermark_factor));
    obj->Set(String::NewSymbol("choking_algorithm"), Integer::New(s.choking_algorithm));
    obj->Set(String::NewSymbol("seed_choking_algorithm"), Integer::New(s.seed_choking_algorithm));
    obj->Set(String::NewSymbol("use_parole_mode"), Boolean::New(s.use_parole_mode));
    obj->Set(String::NewSymbol("cache_size"), Integer::New(s.cache_size));
    obj->Set(String::NewSymbol("cache_buffer_chunk_size"), Integer::New(s.cache_buffer_chunk_size));
    obj->Set(String::NewSymbol("cache_expiry"), Integer::New(s.cache_expiry));
    obj->Set(String::NewSymbol("use_read_cache"), Boolean::New(s.use_read_cache));
    obj->Set(String::NewSymbol("explicit_read_cache"), Boolean::New(s.explicit_read_cache));
    obj->Set(String::NewSymbol("explicit_cache_interval"), Integer::New(s.explicit_cache_interval));
    obj->Set(String::NewSymbol("disk_io_write_mode"), Integer::New(s.disk_io_write_mode));
    obj->Set(String::NewSymbol("disk_io_read_mode"), Integer::New(s.disk_io_read_mode));
    obj->Set(String::NewSymbol("coalesce_reads"), Boolean::New(s.coalesce_reads));
    obj->Set(String::NewSymbol("coalesce_writes"), Boolean::New(s.coalesce_writes));
    Local<Array> outgoing_ports = Array::New();
    outgoing_ports->Set(0, Integer::New(s.outgoing_ports.first));
    outgoing_ports->Set(1, Integer::New(s.outgoing_ports.second));
    obj->Set(String::NewSymbol("outgoing_ports"), outgoing_ports);
    obj->Set(String::NewSymbol("peer_tos"), String::New(&s.peer_tos));
    obj->Set(String::NewSymbol("active_downloads"), Integer::New(s.active_downloads));
    obj->Set(String::NewSymbol("active_seeds"), Integer::New(s.active_seeds));
    obj->Set(String::NewSymbol("active_dht_limit"), Integer::New(s.active_dht_limit));
    obj->Set(String::NewSymbol("active_tracker_limit"), Integer::New(s.active_tracker_limit));
    obj->Set(String::NewSymbol("active_lsd_limit"), Integer::New(s.active_lsd_limit));
    obj->Set(String::NewSymbol("active_limit"), Integer::New(s.active_limit));
    obj->Set(String::NewSymbol("auto_manage_prefer_seeds"), Boolean::New(s.auto_manage_prefer_seeds));
    obj->Set(String::NewSymbol("dont_count_slow_torrents"), Boolean::New(s.dont_count_slow_torrents));
    obj->Set(String::NewSymbol("auto_manage_interval"), Integer::New(s.auto_manage_interval));
    obj->Set(String::NewSymbol("share_ratio_limit"), Number::New(s.share_ratio_limit));
    obj->Set(String::NewSymbol("seed_time_ratio_limit"), Number::New(s.seed_time_ratio_limit));
    obj->Set(String::NewSymbol("seed_time_limit"), Integer::New(s.seed_time_limit));
    obj->Set(String::NewSymbol("peer_turnover_interval"), Integer::New(s.peer_turnover_interval));
    obj->Set(String::NewSymbol("peer_turnover"), Number::New(s.peer_turnover));
    obj->Set(String::NewSymbol("peer_turnover_cutoff"), Number::New(s.peer_turnover_cutoff));
    obj->Set(String::NewSymbol("close_redundant_connections"), Boolean::New(s.close_redundant_connections));
    obj->Set(String::NewSymbol("auto_scrape_interval"), Integer::New(s.auto_scrape_interval));
    obj->Set(String::NewSymbol("auto_scrape_min_interval"), Integer::New(s.auto_scrape_min_interval));
    obj->Set(String::NewSymbol("max_peerlist_size"), Integer::New(s.max_peerlist_size));
    obj->Set(String::NewSymbol("max_paused_peerlist_size"), Integer::New(s.max_paused_peerlist_size));
    obj->Set(String::NewSymbol("min_announce_interval"), Integer::New(s.min_announce_interval));
    obj->Set(String::NewSymbol("prioritize_partial_pieces"), Boolean::New(s.prioritize_partial_pieces));
    obj->Set(String::NewSymbol("auto_manage_startup"), Integer::New(s.auto_manage_startup));
    obj->Set(String::NewSymbol("rate_limit_ip_overhead"), Boolean::New(s.rate_limit_ip_overhead));
    obj->Set(String::NewSymbol("announce_to_all_trackers"), Boolean::New(s.announce_to_all_trackers));
    obj->Set(String::NewSymbol("announce_to_all_tiers"), Boolean::New(s.announce_to_all_tiers));
    obj->Set(String::NewSymbol("prefer_udp_trackers"), Boolean::New(s.prefer_udp_trackers));
    obj->Set(String::NewSymbol("strict_super_seeding"), Boolean::New(s.strict_super_seeding));
    obj->Set(String::NewSymbol("seeding_piece_quota"), Integer::New(s.seeding_piece_quota));
    obj->Set(String::NewSymbol("max_sparse_regions"), Integer::New(s.max_sparse_regions));
#ifndef TORRENT_DISABLE_MLOCK
    obj->Set(String::NewSymbol("lock_disk_cache"), Boolean::New(s.lock_disk_cache));
#endif
    obj->Set(String::NewSymbol("max_rejects"), Integer::New(s.max_rejects));
    obj->Set(String::NewSymbol("recv_socket_buffer_size"), Integer::New(s.recv_socket_buffer_size));
    obj->Set(String::NewSymbol("send_socket_buffer_size"), Integer::New(s.send_socket_buffer_size));
    obj->Set(String::NewSymbol("optimize_hashing_for_speed"), Boolean::New(s.optimize_hashing_for_speed));
    obj->Set(String::NewSymbol("file_checks_delay_per_block"), Integer::New(s.file_checks_delay_per_block));
    obj->Set(String::NewSymbol("disk_cache_algorithm"), Integer::New(s.disk_cache_algorithm));
    obj->Set(String::NewSymbol("read_cache_line_size"), Integer::New(s.read_cache_line_size));
    obj->Set(String::NewSymbol("write_cache_line_size"), Integer::New(s.write_cache_line_size));
    obj->Set(String::NewSymbol("optimistic_disk_retry"), Integer::New(s.optimistic_disk_retry));
    obj->Set(String::NewSymbol("disable_hash_checks"), Boolean::New(s.disable_hash_checks));
    obj->Set(String::NewSymbol("allow_reordered_disk_operations"), Boolean::New(s.allow_reordered_disk_operations));
    obj->Set(String::NewSymbol("allow_i2p_mixed"), Boolean::New(s.allow_i2p_mixed));
    obj->Set(String::NewSymbol("max_suggest_pieces"), Integer::New(s.max_suggest_pieces));
    obj->Set(String::NewSymbol("drop_skipped_requests"), Boolean::New(s.drop_skipped_requests));
    obj->Set(String::NewSymbol("low_prio_disk"), Boolean::New(s.low_prio_disk));
    obj->Set(String::NewSymbol("local_service_announce_interval"), Integer::New(s.local_service_announce_interval));
    obj->Set(String::NewSymbol("dht_announce_interval"), Integer::New(s.dht_announce_interval));
    obj->Set(String::NewSymbol("udp_tracker_token_expiry"), Integer::New(s.udp_tracker_token_expiry));
    obj->Set(String::NewSymbol("volatile_read_cache"), Boolean::New(s.volatile_read_cache));
    obj->Set(String::NewSymbol("guided_read_cache"), Boolean::New(s.guided_read_cache));
    obj->Set(String::NewSymbol("default_cache_min_age"), Integer::New(s.default_cache_min_age));
    obj->Set(String::NewSymbol("num_optimistic_unchoke_slots"), Integer::New(s.num_optimistic_unchoke_slots));
    obj->Set(String::NewSymbol("no_atime_storage"), Boolean::New(s.no_atime_storage));
    obj->Set(String::NewSymbol("default_est_reciprocation_rate"), Integer::New(s.default_est_reciprocation_rate));
    obj->Set(String::NewSymbol("increase_est_reciprocation_rate"), Integer::New(s.increase_est_reciprocation_rate));
    obj->Set(String::NewSymbol("decrease_est_reciprocation_rate"), Integer::New(s.decrease_est_reciprocation_rate));
    obj->Set(String::NewSymbol("incoming_starts_queued_torrents"), Boolean::New(s.incoming_starts_queued_torrents));
    obj->Set(String::NewSymbol("report_true_downloaded"), Boolean::New(s.report_true_downloaded));
    obj->Set(String::NewSymbol("strict_end_game_mode"), Boolean::New(s.strict_end_game_mode));
    obj->Set(String::NewSymbol("broadcast_lsd"), Boolean::New(s.broadcast_lsd));
    obj->Set(String::NewSymbol("enable_outgoing_utp"), Boolean::New(s.enable_outgoing_utp));
    obj->Set(String::NewSymbol("enable_incoming_utp"), Boolean::New(s.enable_incoming_utp));
    obj->Set(String::NewSymbol("enable_outgoing_tcp"), Boolean::New(s.enable_outgoing_tcp));
    obj->Set(String::NewSymbol("enable_incoming_tcp"), Boolean::New(s.enable_incoming_tcp));
    obj->Set(String::NewSymbol("max_pex_peers"), Integer::New(s.max_pex_peers));
    obj->Set(String::NewSymbol("ignore_resume_timestamps"), Boolean::New(s.ignore_resume_timestamps));
    obj->Set(String::NewSymbol("no_recheck_incomplete_resume"), Boolean::New(s.no_recheck_incomplete_resume));
    obj->Set(String::NewSymbol("anonymous_mode"), Boolean::New(s.anonymous_mode));
    obj->Set(String::NewSymbol("tick_interval"), Integer::New(s.tick_interval));
    obj->Set(String::NewSymbol("report_web_seed_downloads"), Boolean::New(s.report_web_seed_downloads));
    obj->Set(String::NewSymbol("share_mode_target"), Integer::New(s.share_mode_target));
    obj->Set(String::NewSymbol("upload_rate_limit"), Integer::New(s.upload_rate_limit));
    obj->Set(String::NewSymbol("download_rate_limit"), Integer::New(s.download_rate_limit));
    obj->Set(String::NewSymbol("local_upload_rate_limit"), Integer::New(s.local_upload_rate_limit));
    obj->Set(String::NewSymbol("local_download_rate_limit"), Integer::New(s.local_download_rate_limit));
    obj->Set(String::NewSymbol("dht_upload_rate_limit"), Integer::New(s.dht_upload_rate_limit));
    obj->Set(String::NewSymbol("unchoke_slots_limit"), Integer::New(s.unchoke_slots_limit));
    obj->Set(String::NewSymbol("half_open_limit"), Integer::New(s.half_open_limit));
    obj->Set(String::NewSymbol("connections_limit"), Integer::New(s.connections_limit));
    obj->Set(String::NewSymbol("utp_target_delay"), Integer::New(s.utp_target_delay));
    obj->Set(String::NewSymbol("utp_gain_factor"), Integer::New(s.utp_gain_factor));
    obj->Set(String::NewSymbol("utp_min_timeout"), Integer::New(s.utp_min_timeout));
    obj->Set(String::NewSymbol("utp_syn_resends"), Integer::New(s.utp_syn_resends));
    obj->Set(String::NewSymbol("utp_fin_resends"), Integer::New(s.utp_fin_resends));
    obj->Set(String::NewSymbol("utp_num_resends"), Integer::New(s.utp_num_resends));
    obj->Set(String::NewSymbol("utp_connect_timeout"), Integer::New(s.utp_connect_timeout));
    obj->Set(String::NewSymbol("utp_delayed_ack"), Integer::New(s.utp_delayed_ack));
    obj->Set(String::NewSymbol("utp_dynamic_sock_buf"), Boolean::New(s.utp_dynamic_sock_buf));
    obj->Set(String::NewSymbol("utp_loss_multiplier"), Integer::New(s.utp_loss_multiplier));
    obj->Set(String::NewSymbol("mixed_mode_algorithm"), Integer::New(s.mixed_mode_algorithm));
    obj->Set(String::NewSymbol("rate_limit_utp"), Boolean::New(s.rate_limit_utp));
    obj->Set(String::NewSymbol("listen_queue_size"), Integer::New(s.listen_queue_size));
    obj->Set(String::NewSymbol("announce_double_nat"), Boolean::New(s.announce_double_nat));
    obj->Set(String::NewSymbol("torrent_connect_boost"), Integer::New(s.torrent_connect_boost));
    obj->Set(String::NewSymbol("seeding_outgoing_connections"), Boolean::New(s.seeding_outgoing_connections));
    obj->Set(String::NewSymbol("no_connect_privileged_ports"), Boolean::New(s.no_connect_privileged_ports));
    obj->Set(String::NewSymbol("alert_queue_size"), Integer::New(s.alert_queue_size));
    obj->Set(String::NewSymbol("max_metadata_size"), Integer::New(s.max_metadata_size));
    obj->Set(String::NewSymbol("smooth_connects"), Boolean::New(s.smooth_connects));
    obj->Set(String::NewSymbol("always_send_user_agent"), Boolean::New(s.always_send_user_agent));
    obj->Set(String::NewSymbol("apply_ip_filter_to_trackers"), Boolean::New(s.apply_ip_filter_to_trackers));
    obj->Set(String::NewSymbol("read_job_every"), Integer::New(s.read_job_every));
    obj->Set(String::NewSymbol("use_disk_read_ahead"), Boolean::New(s.use_disk_read_ahead));
    obj->Set(String::NewSymbol("lock_files"), Boolean::New(s.lock_files));
    obj->Set(String::NewSymbol("ssl_listen"), Integer::New(s.ssl_listen));
    obj->Set(String::NewSymbol("tracker_backoff"), Integer::New(s.tracker_backoff));
    obj->Set(String::NewSymbol("ban_web_seeds"), Boolean::New(s.ban_web_seeds));

    return scope.Close(obj);
  };

  libtorrent::session_settings session_settings_from_object(Local<Object> obj) {
    libtorrent::session_settings s;

    if (obj->Has(String::NewSymbol("version")))
      s.version = obj->Get(String::NewSymbol("version"))->IntegerValue();
    if (obj->Has(String::NewSymbol("user_agent"))) {
      Local<Object> user_agent = obj->Get(String::NewSymbol("user_agent"))->ToObject();
      s.user_agent = std::string(*String::Utf8Value(user_agent));
    }
    if (obj->Has(String::NewSymbol("tracker_completion_timeout")))
      s.tracker_completion_timeout = obj->Get(String::NewSymbol("tracker_completion_timeout"))->IntegerValue();
    if (obj->Has(String::NewSymbol("tracker_receive_timeout")))
      s.tracker_receive_timeout = obj->Get(String::NewSymbol("tracker_receive_timeout"))->IntegerValue();
    if (obj->Has(String::NewSymbol("stop_tracker_timeout")))
      s.stop_tracker_timeout = obj->Get(String::NewSymbol("stop_tracker_timeout"))->IntegerValue();
    if (obj->Has(String::NewSymbol("tracker_maximum_response_length")))
      s.tracker_maximum_response_length = obj->Get(String::NewSymbol("tracker_maximum_response_length"))->IntegerValue();
    if (obj->Has(String::NewSymbol("piece_timeout")))
      s.piece_timeout = obj->Get(String::NewSymbol("piece_timeout"))->IntegerValue();
    if (obj->Has(String::NewSymbol("request_timeout")))
      s.request_timeout = obj->Get(String::NewSymbol("request_timeout"))->IntegerValue();
    if (obj->Has(String::NewSymbol("request_queue_time")))
      s.request_queue_time = obj->Get(String::NewSymbol("request_queue_time"))->IntegerValue();
    if (obj->Has(String::NewSymbol("max_allowed_in_request_queue")))
      s.max_allowed_in_request_queue = obj->Get(String::NewSymbol("max_allowed_in_request_queue"))->IntegerValue();
    if (obj->Has(String::NewSymbol("max_out_request_queue")))
      s.max_out_request_queue = obj->Get(String::NewSymbol("max_out_request_queue"))->IntegerValue();
    if (obj->Has(String::NewSymbol("whole_pieces_threshold")))
      s.whole_pieces_threshold = obj->Get(String::NewSymbol("whole_pieces_threshold"))->IntegerValue();
    if (obj->Has(String::NewSymbol("peer_timeout")))
      s.peer_timeout = obj->Get(String::NewSymbol("peer_timeout"))->IntegerValue();
    if (obj->Has(String::NewSymbol("urlseed_timeout")))
      s.urlseed_timeout = obj->Get(String::NewSymbol("urlseed_timeout"))->IntegerValue();
    if (obj->Has(String::NewSymbol("urlseed_pipeline_size")))
      s.urlseed_pipeline_size = obj->Get(String::NewSymbol("urlseed_pipeline_size"))->IntegerValue();
    if (obj->Has(String::NewSymbol("urlseed_wait_retry")))
      s.urlseed_wait_retry = obj->Get(String::NewSymbol("urlseed_wait_retry"))->IntegerValue();
    if (obj->Has(String::NewSymbol("file_pool_size")))
      s.file_pool_size = obj->Get(String::NewSymbol("file_pool_size"))->IntegerValue();
    if (obj->Has(String::NewSymbol("allow_multiple_connections_per_ip")))
      s.allow_multiple_connections_per_ip = obj->Get(String::NewSymbol("allow_multiple_connections_per_ip"))->BooleanValue();
    if (obj->Has(String::NewSymbol("max_failcount")))
      s.max_failcount = obj->Get(String::NewSymbol("max_failcount"))->IntegerValue();
    if (obj->Has(String::NewSymbol("min_reconnect_time")))
      s.min_reconnect_time = obj->Get(String::NewSymbol("min_reconnect_time"))->IntegerValue();
    if (obj->Has(String::NewSymbol("peer_connect_timeout")))
      s.peer_connect_timeout = obj->Get(String::NewSymbol("peer_connect_timeout"))->IntegerValue();
    if (obj->Has(String::NewSymbol("ignore_limits_on_local_network")))
      s.ignore_limits_on_local_network = obj->Get(String::NewSymbol("ignore_limits_on_local_network"))->BooleanValue();
    if (obj->Has(String::NewSymbol("connection_speed")))
      s.connection_speed = obj->Get(String::NewSymbol("connection_speed"))->IntegerValue();
    if (obj->Has(String::NewSymbol("send_redundant_have")))
      s.send_redundant_have = obj->Get(String::NewSymbol("send_redundant_have"))->BooleanValue();
    if (obj->Has(String::NewSymbol("lazy_bitfields")))
      s.lazy_bitfields = obj->Get(String::NewSymbol("lazy_bitfields"))->BooleanValue();
    if (obj->Has(String::NewSymbol("inactivity_timeout")))
      s.inactivity_timeout = obj->Get(String::NewSymbol("inactivity_timeout"))->IntegerValue();
    if (obj->Has(String::NewSymbol("unchoke_interval")))
      s.unchoke_interval = obj->Get(String::NewSymbol("unchoke_interval"))->IntegerValue();
    if (obj->Has(String::NewSymbol("optimistic_unchoke_interval")))
      s.optimistic_unchoke_interval = obj->Get(String::NewSymbol("optimistic_unchoke_interval"))->IntegerValue();
    if (obj->Has(String::NewSymbol("announce_ip"))) {
      Local<Object> announce_ip = obj->Get(String::NewSymbol("announce_ip"))->ToObject();
      s.announce_ip = std::string(*String::Utf8Value(announce_ip));
    }
    if (obj->Has(String::NewSymbol("num_want")))
      s.num_want = obj->Get(String::NewSymbol("num_want"))->IntegerValue();
    if (obj->Has(String::NewSymbol("initial_picker_threshold")))
      s.initial_picker_threshold = obj->Get(String::NewSymbol("initial_picker_threshold"))->IntegerValue();
    if (obj->Has(String::NewSymbol("allowed_fast_set_size")))
      s.allowed_fast_set_size = obj->Get(String::NewSymbol("allowed_fast_set_size"))->IntegerValue();
    if (obj->Has(String::NewSymbol("suggest_mode")))
      s.suggest_mode = obj->Get(String::NewSymbol("suggest_mode"))->IntegerValue();
    if (obj->Has(String::NewSymbol("max_queued_disk_bytes")))
      s.max_queued_disk_bytes = obj->Get(String::NewSymbol("max_queued_disk_bytes"))->IntegerValue();
    if (obj->Has(String::NewSymbol("max_queued_disk_bytes_low_watermark")))
      s.max_queued_disk_bytes_low_watermark = obj->Get(String::NewSymbol("max_queued_disk_bytes_low_watermark"))->IntegerValue();
    if (obj->Has(String::NewSymbol("handshake_timeout")))
      s.handshake_timeout = obj->Get(String::NewSymbol("handshake_timeout"))->IntegerValue();
#ifndef TORRENT_DISABLE_DHT
    if (obj->Has(String::NewSymbol("use_dht_as_fallback")))
      s.use_dht_as_fallback = obj->Get(String::NewSymbol("use_dht_as_fallback"))->BooleanValue();
#endif
    if (obj->Has(String::NewSymbol("free_torrent_hashes")))
      s.free_torrent_hashes = obj->Get(String::NewSymbol("free_torrent_hashes"))->BooleanValue();
    if (obj->Has(String::NewSymbol("upnp_ignore_nonrouters")))
      s.upnp_ignore_nonrouters = obj->Get(String::NewSymbol("upnp_ignore_nonrouters"))->BooleanValue();
    if (obj->Has(String::NewSymbol("send_buffer_low_watermark")))
      s.send_buffer_low_watermark = obj->Get(String::NewSymbol("send_buffer_low_watermark"))->IntegerValue();
    if (obj->Has(String::NewSymbol("send_buffer_watermark")))
      s.send_buffer_watermark = obj->Get(String::NewSymbol("send_buffer_watermark"))->IntegerValue();
    if (obj->Has(String::NewSymbol("send_buffer_watermark_factor")))
      s.send_buffer_watermark_factor = obj->Get(String::NewSymbol("send_buffer_watermark_factor"))->IntegerValue();
    if (obj->Has(String::NewSymbol("choking_algorithm")))
      s.choking_algorithm = obj->Get(String::NewSymbol("choking_algorithm"))->IntegerValue();
    if (obj->Has(String::NewSymbol("seed_choking_algorithm")))
      s.seed_choking_algorithm = obj->Get(String::NewSymbol("seed_choking_algorithm"))->IntegerValue();
    if (obj->Has(String::NewSymbol("use_parole_mode")))
      s.use_parole_mode = obj->Get(String::NewSymbol("use_parole_mode"))->BooleanValue();
    if (obj->Has(String::NewSymbol("cache_size")))
      s.cache_size = obj->Get(String::NewSymbol("cache_size"))->IntegerValue();
    if (obj->Has(String::NewSymbol("cache_buffer_chunk_size")))
      s.cache_buffer_chunk_size = obj->Get(String::NewSymbol("cache_buffer_chunk_size"))->IntegerValue();
    if (obj->Has(String::NewSymbol("cache_expiry")))
      s.cache_expiry = obj->Get(String::NewSymbol("cache_expiry"))->IntegerValue();
    if (obj->Has(String::NewSymbol("use_read_cache")))
      s.use_read_cache = obj->Get(String::NewSymbol("use_read_cache"))->BooleanValue();
    if (obj->Has(String::NewSymbol("explicit_read_cache")))
      s.explicit_read_cache = obj->Get(String::NewSymbol("explicit_read_cache"))->BooleanValue();
    if (obj->Has(String::NewSymbol("explicit_cache_interval")))
      s.explicit_cache_interval = obj->Get(String::NewSymbol("explicit_cache_interval"))->IntegerValue();
    if (obj->Has(String::NewSymbol("disk_io_write_mode")))
      s.disk_io_write_mode = obj->Get(String::NewSymbol("disk_io_write_mode"))->IntegerValue();
    if (obj->Has(String::NewSymbol("disk_io_read_mode")))
      s.disk_io_read_mode = obj->Get(String::NewSymbol("disk_io_read_mode"))->IntegerValue();
    if (obj->Has(String::NewSymbol("coalesce_reads")))
      s.coalesce_reads = obj->Get(String::NewSymbol("coalesce_reads"))->BooleanValue();
    if (obj->Has(String::NewSymbol("coalesce_writes")))
      s.coalesce_writes = obj->Get(String::NewSymbol("coalesce_writes"))->BooleanValue();
    if (obj->Has(String::NewSymbol("outgoing_ports"))) {
      Local<Object> outgoing_ports = obj->Get(String::NewSymbol("outgoing_ports"))->ToObject();
      s.outgoing_ports = std::make_pair(
        outgoing_ports->Get(0)->IntegerValue(), outgoing_ports->Get(1)->IntegerValue());
    }
    if (obj->Has(String::NewSymbol("peer_tos"))) {
      Local<Object> announce_ip = obj->Get(String::NewSymbol("peer_tos"))->ToObject();
      s.peer_tos = std::string(*String::Utf8Value(announce_ip)).c_str()[0];
    }
    if (obj->Has(String::NewSymbol("active_downloads")))
      s.active_downloads = obj->Get(String::NewSymbol("active_downloads"))->IntegerValue();
    if (obj->Has(String::NewSymbol("active_seeds")))
      s.active_seeds = obj->Get(String::NewSymbol("active_seeds"))->IntegerValue();
    if (obj->Has(String::NewSymbol("active_dht_limit")))
      s.active_dht_limit = obj->Get(String::NewSymbol("active_dht_limit"))->IntegerValue();
    if (obj->Has(String::NewSymbol("active_tracker_limit")))
      s.active_tracker_limit = obj->Get(String::NewSymbol("active_tracker_limit"))->IntegerValue();
    if (obj->Has(String::NewSymbol("active_lsd_limit")))
      s.active_lsd_limit = obj->Get(String::NewSymbol("active_lsd_limit"))->IntegerValue();
    if (obj->Has(String::NewSymbol("active_limit")))
      s.active_limit = obj->Get(String::NewSymbol("active_limit"))->IntegerValue();
    if (obj->Has(String::NewSymbol("auto_manage_prefer_seeds")))
      s.auto_manage_prefer_seeds = obj->Get(String::NewSymbol("auto_manage_prefer_seeds"))->BooleanValue();
    if (obj->Has(String::NewSymbol("dont_count_slow_torrents")))
      s.dont_count_slow_torrents = obj->Get(String::NewSymbol("dont_count_slow_torrents"))->BooleanValue();
    if (obj->Has(String::NewSymbol("auto_manage_interval")))
      s.auto_manage_interval = obj->Get(String::NewSymbol("auto_manage_interval"))->IntegerValue();
    if (obj->Has(String::NewSymbol("share_ratio_limit")))
      s.share_ratio_limit = obj->Get(String::NewSymbol("share_ratio_limit"))->NumberValue();
    if (obj->Has(String::NewSymbol("seed_time_ratio_limit")))
      s.seed_time_ratio_limit = obj->Get(String::NewSymbol("seed_time_ratio_limit"))->NumberValue();
    if (obj->Has(String::NewSymbol("seed_time_limit")))
      s.seed_time_limit = obj->Get(String::NewSymbol("seed_time_limit"))->IntegerValue();
    if (obj->Has(String::NewSymbol("peer_turnover_interval")))
      s.peer_turnover_interval = obj->Get(String::NewSymbol("peer_turnover_interval"))->IntegerValue();
    if (obj->Has(String::NewSymbol("peer_turnover")))
      s.peer_turnover = obj->Get(String::NewSymbol("peer_turnover"))->NumberValue();
    if (obj->Has(String::NewSymbol("peer_turnover_cutoff")))
      s.peer_turnover_cutoff = obj->Get(String::NewSymbol("peer_turnover_cutoff"))->NumberValue();
    if (obj->Has(String::NewSymbol("close_redundant_connections")))
      s.close_redundant_connections = obj->Get(String::NewSymbol("close_redundant_connections"))->BooleanValue();
    if (obj->Has(String::NewSymbol("auto_scrape_interval")))
      s.auto_scrape_interval = obj->Get(String::NewSymbol("auto_scrape_interval"))->IntegerValue();
    if (obj->Has(String::NewSymbol("auto_scrape_min_interval")))
      s.auto_scrape_min_interval = obj->Get(String::NewSymbol("auto_scrape_min_interval"))->IntegerValue();
    if (obj->Has(String::NewSymbol("max_peerlist_size")))
      s.max_peerlist_size = obj->Get(String::NewSymbol("max_peerlist_size"))->IntegerValue();
    if (obj->Has(String::NewSymbol("max_paused_peerlist_size")))
      s.max_paused_peerlist_size = obj->Get(String::NewSymbol("max_paused_peerlist_size"))->IntegerValue();
    if (obj->Has(String::NewSymbol("min_announce_interval")))
      s.min_announce_interval = obj->Get(String::NewSymbol("min_announce_interval"))->IntegerValue();
    if (obj->Has(String::NewSymbol("prioritize_partial_pieces")))
      s.prioritize_partial_pieces = obj->Get(String::NewSymbol("prioritize_partial_pieces"))->BooleanValue();
    if (obj->Has(String::NewSymbol("auto_manage_startup")))
      s.auto_manage_startup = obj->Get(String::NewSymbol("auto_manage_startup"))->IntegerValue();
    if (obj->Has(String::NewSymbol("rate_limit_ip_overhead")))
      s.rate_limit_ip_overhead = obj->Get(String::NewSymbol("rate_limit_ip_overhead"))->BooleanValue();
    if (obj->Has(String::NewSymbol("announce_to_all_trackers")))
      s.announce_to_all_trackers = obj->Get(String::NewSymbol("announce_to_all_trackers"))->BooleanValue();
    if (obj->Has(String::NewSymbol("announce_to_all_tiers")))
      s.announce_to_all_tiers = obj->Get(String::NewSymbol("announce_to_all_tiers"))->BooleanValue();
    if (obj->Has(String::NewSymbol("prefer_udp_trackers")))
      s.prefer_udp_trackers = obj->Get(String::NewSymbol("prefer_udp_trackers"))->BooleanValue();
    if (obj->Has(String::NewSymbol("strict_super_seeding")))
      s.strict_super_seeding = obj->Get(String::NewSymbol("strict_super_seeding"))->BooleanValue();
    if (obj->Has(String::NewSymbol("seeding_piece_quota")))
      s.seeding_piece_quota = obj->Get(String::NewSymbol("seeding_piece_quota"))->IntegerValue();
    if (obj->Has(String::NewSymbol("max_sparse_regions")))
      s.max_sparse_regions = obj->Get(String::NewSymbol("max_sparse_regions"))->IntegerValue();
#ifndef TORRENT_DISABLE_MLOCK
    if (obj->Has(String::NewSymbol("lock_disk_cache")))
      s.lock_disk_cache = obj->Get(String::NewSymbol("lock_disk_cache"))->BooleanValue();
#endif
    if (obj->Has(String::NewSymbol("max_rejects")))
      s.max_rejects = obj->Get(String::NewSymbol("max_rejects"))->IntegerValue();
    if (obj->Has(String::NewSymbol("recv_socket_buffer_size")))
      s.recv_socket_buffer_size = obj->Get(String::NewSymbol("recv_socket_buffer_size"))->IntegerValue();
    if (obj->Has(String::NewSymbol("send_socket_buffer_size")))
      s.send_socket_buffer_size = obj->Get(String::NewSymbol("send_socket_buffer_size"))->IntegerValue();
    if (obj->Has(String::NewSymbol("optimize_hashing_for_speed")))
      s.optimize_hashing_for_speed = obj->Get(String::NewSymbol("optimize_hashing_for_speed"))->BooleanValue();
    if (obj->Has(String::NewSymbol("file_checks_delay_per_block")))
      s.file_checks_delay_per_block = obj->Get(String::NewSymbol("file_checks_delay_per_block"))->IntegerValue();
    if (obj->Has(String::NewSymbol("disk_cache_algorithm")))
      s.disk_cache_algorithm = (libtorrent::session_settings::disk_cache_algo_t) obj->Get(String::NewSymbol("disk_cache_algorithm"))->IntegerValue();
    if (obj->Has(String::NewSymbol("read_cache_line_size")))
      s.read_cache_line_size = obj->Get(String::NewSymbol("read_cache_line_size"))->IntegerValue();
    if (obj->Has(String::NewSymbol("write_cache_line_size")))
      s.write_cache_line_size = obj->Get(String::NewSymbol("write_cache_line_size"))->IntegerValue();
    if (obj->Has(String::NewSymbol("optimistic_disk_retry")))
      s.optimistic_disk_retry = obj->Get(String::NewSymbol("optimistic_disk_retry"))->IntegerValue();
    if (obj->Has(String::NewSymbol("disable_hash_checks")))
      s.disable_hash_checks = obj->Get(String::NewSymbol("disable_hash_checks"))->BooleanValue();
    if (obj->Has(String::NewSymbol("allow_reordered_disk_operations")))
      s.allow_reordered_disk_operations = obj->Get(String::NewSymbol("allow_reordered_disk_operations"))->BooleanValue();
    if (obj->Has(String::NewSymbol("allow_i2p_mixed")))
      s.allow_i2p_mixed = obj->Get(String::NewSymbol("allow_i2p_mixed"))->BooleanValue();
    if (obj->Has(String::NewSymbol("max_suggest_pieces")))
      s.max_suggest_pieces = obj->Get(String::NewSymbol("max_suggest_pieces"))->IntegerValue();
    if (obj->Has(String::NewSymbol("drop_skipped_requests")))
      s.drop_skipped_requests = obj->Get(String::NewSymbol("drop_skipped_requests"))->BooleanValue();
    if (obj->Has(String::NewSymbol("low_prio_disk")))
      s.low_prio_disk = obj->Get(String::NewSymbol("low_prio_disk"))->BooleanValue();
    if (obj->Has(String::NewSymbol("local_service_announce_interval")))
      s.local_service_announce_interval = obj->Get(String::NewSymbol("local_service_announce_interval"))->IntegerValue();
    if (obj->Has(String::NewSymbol("dht_announce_interval")))
      s.dht_announce_interval = obj->Get(String::NewSymbol("dht_announce_interval"))->IntegerValue();
    if (obj->Has(String::NewSymbol("udp_tracker_token_expiry")))
      s.udp_tracker_token_expiry = obj->Get(String::NewSymbol("udp_tracker_token_expiry"))->IntegerValue();
    if (obj->Has(String::NewSymbol("volatile_read_cache")))
      s.volatile_read_cache = obj->Get(String::NewSymbol("volatile_read_cache"))->BooleanValue();
    if (obj->Has(String::NewSymbol("guided_read_cache")))
      s.guided_read_cache = obj->Get(String::NewSymbol("guided_read_cache"))->BooleanValue();
    if (obj->Has(String::NewSymbol("default_cache_min_age")))
      s.default_cache_min_age = obj->Get(String::NewSymbol("default_cache_min_age"))->IntegerValue();
    if (obj->Has(String::NewSymbol("num_optimistic_unchoke_slots")))
      s.num_optimistic_unchoke_slots = obj->Get(String::NewSymbol("num_optimistic_unchoke_slots"))->IntegerValue();
    if (obj->Has(String::NewSymbol("no_atime_storage")))
      s.no_atime_storage = obj->Get(String::NewSymbol("no_atime_storage"))->BooleanValue();
    if (obj->Has(String::NewSymbol("default_est_reciprocation_rate")))
      s.default_est_reciprocation_rate = obj->Get(String::NewSymbol("default_est_reciprocation_rate"))->IntegerValue();
    if (obj->Has(String::NewSymbol("increase_est_reciprocation_rate")))
      s.increase_est_reciprocation_rate = obj->Get(String::NewSymbol("increase_est_reciprocation_rate"))->IntegerValue();
    if (obj->Has(String::NewSymbol("decrease_est_reciprocation_rate")))
      s.decrease_est_reciprocation_rate = obj->Get(String::NewSymbol("decrease_est_reciprocation_rate"))->IntegerValue();
    if (obj->Has(String::NewSymbol("incoming_starts_queued_torrents")))
      s.incoming_starts_queued_torrents = obj->Get(String::NewSymbol("incoming_starts_queued_torrents"))->BooleanValue();
    if (obj->Has(String::NewSymbol("report_true_downloaded")))
      s.report_true_downloaded = obj->Get(String::NewSymbol("report_true_downloaded"))->BooleanValue();
    if (obj->Has(String::NewSymbol("strict_end_game_mode")))
      s.strict_end_game_mode = obj->Get(String::NewSymbol("strict_end_game_mode"))->BooleanValue();
    if (obj->Has(String::NewSymbol("broadcast_lsd")))
      s.broadcast_lsd = obj->Get(String::NewSymbol("broadcast_lsd"))->BooleanValue();
    if (obj->Has(String::NewSymbol("enable_outgoing_utp")))
      s.enable_outgoing_utp = obj->Get(String::NewSymbol("enable_outgoing_utp"))->BooleanValue();
    if (obj->Has(String::NewSymbol("enable_incoming_utp")))
      s.enable_incoming_utp = obj->Get(String::NewSymbol("enable_incoming_utp"))->BooleanValue();
    if (obj->Has(String::NewSymbol("enable_outgoing_tcp")))
      s.enable_outgoing_tcp = obj->Get(String::NewSymbol("enable_outgoing_tcp"))->BooleanValue();
    if (obj->Has(String::NewSymbol("enable_incoming_tcp")))
      s.enable_incoming_tcp = obj->Get(String::NewSymbol("enable_incoming_tcp"))->BooleanValue();
    if (obj->Has(String::NewSymbol("max_pex_peers")))
      s.max_pex_peers = obj->Get(String::NewSymbol("max_pex_peers"))->IntegerValue();
    if (obj->Has(String::NewSymbol("ignore_resume_timestamps")))
      s.ignore_resume_timestamps = obj->Get(String::NewSymbol("ignore_resume_timestamps"))->BooleanValue();
    if (obj->Has(String::NewSymbol("no_recheck_incomplete_resume")))
      s.no_recheck_incomplete_resume = obj->Get(String::NewSymbol("no_recheck_incomplete_resume"))->BooleanValue();
    if (obj->Has(String::NewSymbol("anonymous_mode")))
      s.anonymous_mode = obj->Get(String::NewSymbol("anonymous_mode"))->BooleanValue();
    if (obj->Has(String::NewSymbol("tick_interval")))
      s.tick_interval = obj->Get(String::NewSymbol("tick_interval"))->IntegerValue();
    if (obj->Has(String::NewSymbol("report_web_seed_downloads")))
      s.report_web_seed_downloads = obj->Get(String::NewSymbol("report_web_seed_downloads"))->BooleanValue();
    if (obj->Has(String::NewSymbol("share_mode_target")))
      s.share_mode_target = obj->Get(String::NewSymbol("share_mode_target"))->IntegerValue();
    if (obj->Has(String::NewSymbol("upload_rate_limit")))
      s.upload_rate_limit = obj->Get(String::NewSymbol("upload_rate_limit"))->IntegerValue();
    if (obj->Has(String::NewSymbol("download_rate_limit")))
      s.download_rate_limit = obj->Get(String::NewSymbol("download_rate_limit"))->IntegerValue();
    if (obj->Has(String::NewSymbol("local_upload_rate_limit")))
      s.local_upload_rate_limit = obj->Get(String::NewSymbol("local_upload_rate_limit"))->IntegerValue();
    if (obj->Has(String::NewSymbol("local_download_rate_limit")))
      s.local_download_rate_limit = obj->Get(String::NewSymbol("local_download_rate_limit"))->IntegerValue();
    if (obj->Has(String::NewSymbol("dht_upload_rate_limit")))
      s.dht_upload_rate_limit = obj->Get(String::NewSymbol("dht_upload_rate_limit"))->IntegerValue();
    if (obj->Has(String::NewSymbol("unchoke_slots_limit")))
      s.unchoke_slots_limit = obj->Get(String::NewSymbol("unchoke_slots_limit"))->IntegerValue();
    if (obj->Has(String::NewSymbol("half_open_limit")))
      s.half_open_limit = obj->Get(String::NewSymbol("half_open_limit"))->IntegerValue();
    if (obj->Has(String::NewSymbol("connections_limit")))
      s.connections_limit = obj->Get(String::NewSymbol("connections_limit"))->IntegerValue();
    if (obj->Has(String::NewSymbol("utp_target_delay")))
      s.utp_target_delay = obj->Get(String::NewSymbol("utp_target_delay"))->IntegerValue();
    if (obj->Has(String::NewSymbol("utp_gain_factor")))
      s.utp_gain_factor = obj->Get(String::NewSymbol("utp_gain_factor"))->IntegerValue();
    if (obj->Has(String::NewSymbol("utp_min_timeout")))
      s.utp_min_timeout = obj->Get(String::NewSymbol("utp_min_timeout"))->IntegerValue();
    if (obj->Has(String::NewSymbol("utp_syn_resends")))
      s.utp_syn_resends = obj->Get(String::NewSymbol("utp_syn_resends"))->IntegerValue();
    if (obj->Has(String::NewSymbol("utp_fin_resends")))
      s.utp_fin_resends = obj->Get(String::NewSymbol("utp_fin_resends"))->IntegerValue();
    if (obj->Has(String::NewSymbol("utp_num_resends")))
      s.utp_num_resends = obj->Get(String::NewSymbol("utp_num_resends"))->IntegerValue();
    if (obj->Has(String::NewSymbol("utp_connect_timeout")))
      s.utp_connect_timeout = obj->Get(String::NewSymbol("utp_connect_timeout"))->IntegerValue();
    if (obj->Has(String::NewSymbol("utp_delayed_ack")))
      s.utp_delayed_ack = obj->Get(String::NewSymbol("utp_delayed_ack"))->IntegerValue();
    if (obj->Has(String::NewSymbol("utp_dynamic_sock_buf")))
      s.utp_dynamic_sock_buf = obj->Get(String::NewSymbol("utp_dynamic_sock_buf"))->BooleanValue();
    if (obj->Has(String::NewSymbol("utp_loss_multiplier")))
      s.utp_loss_multiplier = obj->Get(String::NewSymbol("utp_loss_multiplier"))->IntegerValue();
    if (obj->Has(String::NewSymbol("mixed_mode_algorithm")))
      s.mixed_mode_algorithm = obj->Get(String::NewSymbol("mixed_mode_algorithm"))->IntegerValue();
    if (obj->Has(String::NewSymbol("rate_limit_utp")))
      s.rate_limit_utp = obj->Get(String::NewSymbol("rate_limit_utp"))->BooleanValue();
    if (obj->Has(String::NewSymbol("listen_queue_size")))
      s.listen_queue_size = obj->Get(String::NewSymbol("listen_queue_size"))->IntegerValue();
    if (obj->Has(String::NewSymbol("announce_double_nat")))
      s.announce_double_nat = obj->Get(String::NewSymbol("announce_double_nat"))->BooleanValue();
    if (obj->Has(String::NewSymbol("torrent_connect_boost")))
      s.torrent_connect_boost = obj->Get(String::NewSymbol("torrent_connect_boost"))->IntegerValue();
    if (obj->Has(String::NewSymbol("seeding_outgoing_connections")))
      s.seeding_outgoing_connections = obj->Get(String::NewSymbol("seeding_outgoing_connections"))->BooleanValue();
    if (obj->Has(String::NewSymbol("no_connect_privileged_ports")))
      s.no_connect_privileged_ports = obj->Get(String::NewSymbol("no_connect_privileged_ports"))->BooleanValue();
    if (obj->Has(String::NewSymbol("alert_queue_size")))
      s.alert_queue_size = obj->Get(String::NewSymbol("alert_queue_size"))->IntegerValue();
    if (obj->Has(String::NewSymbol("max_metadata_size")))
      s.max_metadata_size = obj->Get(String::NewSymbol("max_metadata_size"))->IntegerValue();
    if (obj->Has(String::NewSymbol("smooth_connects")))
      s.smooth_connects = obj->Get(String::NewSymbol("smooth_connects"))->BooleanValue();
    if (obj->Has(String::NewSymbol("always_send_user_agent")))
      s.always_send_user_agent = obj->Get(String::NewSymbol("always_send_user_agent"))->BooleanValue();
    if (obj->Has(String::NewSymbol("apply_ip_filter_to_trackers")))
      s.apply_ip_filter_to_trackers = obj->Get(String::NewSymbol("apply_ip_filter_to_trackers"))->BooleanValue();
    if (obj->Has(String::NewSymbol("read_job_every")))
      s.read_job_every = obj->Get(String::NewSymbol("read_job_every"))->IntegerValue();
    if (obj->Has(String::NewSymbol("use_disk_read_ahead")))
      s.use_disk_read_ahead = obj->Get(String::NewSymbol("use_disk_read_ahead"))->BooleanValue();
    if (obj->Has(String::NewSymbol("lock_files")))
      s.lock_files = obj->Get(String::NewSymbol("lock_files"))->BooleanValue();
    if (obj->Has(String::NewSymbol("ssl_listen")))
      s.ssl_listen = obj->Get(String::NewSymbol("ssl_listen"))->IntegerValue();
    if (obj->Has(String::NewSymbol("tracker_backoff")))
      s.tracker_backoff = obj->Get(String::NewSymbol("tracker_backoff"))->IntegerValue();
    if (obj->Has(String::NewSymbol("ban_web_seeds")))
      s.ban_web_seeds = obj->Get(String::NewSymbol("ban_web_seeds"))->BooleanValue();

    return s;
  };


  void bind_session_settings(Handle<Object> target) {
    // set libtorrent::session_settings::choking_algorithm_t
    Local<Object> choking_algorithm_t = Object::New();
    choking_algorithm_t->Set(String::NewSymbol("fixed_slots_choker"),
      Integer::New(libtorrent::session_settings::fixed_slots_choker));
    choking_algorithm_t->Set(String::NewSymbol("auto_expand_choker"),
      Integer::New(libtorrent::session_settings::auto_expand_choker));
    choking_algorithm_t->Set(String::NewSymbol("rate_based_choker"),
      Integer::New(libtorrent::session_settings::rate_based_choker));
    choking_algorithm_t->Set(String::NewSymbol("bittyrant_choker"),
      Integer::New(libtorrent::session_settings::bittyrant_choker));
    target->Set(String::NewSymbol("choking_algorithm_t"), choking_algorithm_t);

    // set libtorrent::session_settings::seed_choking_algorithm_t
    Local<Object> seed_choking_algorithm_t = Object::New();
    seed_choking_algorithm_t->Set(String::NewSymbol("round_robin"),
      Integer::New(libtorrent::session_settings::round_robin));
    seed_choking_algorithm_t->Set(String::NewSymbol("fastest_upload"),
      Integer::New(libtorrent::session_settings::fastest_upload));
    seed_choking_algorithm_t->Set(String::NewSymbol("anti_leech"),
      Integer::New(libtorrent::session_settings::anti_leech));
    target->Set(String::NewSymbol("seed_choking_algorithm_t"), seed_choking_algorithm_t);

    // set libtorrent::session_settings::io_buffer_mode_t
    Local<Object> io_buffer_mode_t = Object::New();
    io_buffer_mode_t->Set(String::NewSymbol("enable_os_cache"),
      Integer::New(libtorrent::session_settings::enable_os_cache));
    io_buffer_mode_t->Set(String::NewSymbol("disable_os_cache_for_aligned_files"),
      Integer::New(libtorrent::session_settings::disable_os_cache_for_aligned_files));
    io_buffer_mode_t->Set(String::NewSymbol("disable_os_cache"),
      Integer::New(libtorrent::session_settings::disable_os_cache));
    target->Set(String::NewSymbol("io_buffer_mode_t"), io_buffer_mode_t);

    // set libtorrent::session_settings::disk_cache_algo_t
    Local<Object> disk_cache_algo_t = Object::New();
    disk_cache_algo_t->Set(String::NewSymbol("lru"),
      Integer::New(libtorrent::session_settings::lru));
    disk_cache_algo_t->Set(String::NewSymbol("largest_contiguous"),
      Integer::New(libtorrent::session_settings::largest_contiguous));
    disk_cache_algo_t->Set(String::NewSymbol("avoid_readback"),
      Integer::New(libtorrent::session_settings::avoid_readback));
    target->Set(String::NewSymbol("disk_cache_algo_t"), disk_cache_algo_t);

    // set libtorrent::session_settings::suggest_mode_t
    Local<Object> suggest_mode_t = Object::New();
    suggest_mode_t->Set(String::NewSymbol("no_piece_suggestions"),
      Integer::New(libtorrent::session_settings::no_piece_suggestions));
    suggest_mode_t->Set(String::NewSymbol("suggest_read_cache"),
      Integer::New(libtorrent::session_settings::suggest_read_cache));
    target->Set(String::NewSymbol("suggest_mode_t"), suggest_mode_t);

    // set libtorrent::session_settings::suggest_mode_t
    Local<Object> bandwidth_mixed_algo_t = Object::New();
    bandwidth_mixed_algo_t->Set(String::NewSymbol("prefer_tcp"),
      Integer::New(libtorrent::session_settings::prefer_tcp));
    bandwidth_mixed_algo_t->Set(String::NewSymbol("peer_proportional"),
      Integer::New(libtorrent::session_settings::peer_proportional));
    target->Set(String::NewSymbol("bandwidth_mixed_algo_t"), bandwidth_mixed_algo_t);

    // set libtorrent::proxy_settings::proxy_type
    Local<Object> proxy_type = Object::New();
    proxy_type->Set(String::NewSymbol("none"),
      Integer::New(libtorrent::proxy_settings::none));
    proxy_type->Set(String::NewSymbol("socks4"),
      Integer::New(libtorrent::proxy_settings::socks4));
    proxy_type->Set(String::NewSymbol("socks5"),
      Integer::New(libtorrent::proxy_settings::socks5));
    proxy_type->Set(String::NewSymbol("socks5_pw"),
      Integer::New(libtorrent::proxy_settings::socks5_pw));
    proxy_type->Set(String::NewSymbol("http"),
      Integer::New(libtorrent::proxy_settings::http));
    proxy_type->Set(String::NewSymbol("http_pw"),
      Integer::New(libtorrent::proxy_settings::http_pw));
    proxy_type->Set(String::NewSymbol("i2p_proxy"),
      Integer::New(libtorrent::proxy_settings::i2p_proxy));
    target->Set(String::NewSymbol("proxy_type"), proxy_type);
  };
};
