#ifndef NODE_LIBTORRENT_SESSION_STATUS_HPP_INCLUDED
#define NODE_LIBTORRENT_SESSION_STATUS_HPP_INCLUDED

#include <v8.h>

#include <libtorrent/session_status.hpp>


namespace nodelt {
  v8::Local<v8::Object> session_status_to_object(const libtorrent::session_status& st);
};

#endif // NODE_LIBTORRENT_SESSION_STATUS_HPP_INCLUDED
