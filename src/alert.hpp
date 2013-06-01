#ifndef NODE_LIBTORRENT_ALERT_HPP_INCLUDED
#define NODE_LIBTORRENT_ALERT_HPP_INCLUDED

#include <v8.h>
#include <node.h>

#include <libtorrent/alert.hpp>


namespace nodelt {
  v8::Local<v8::Object> alert_to_object(const libtorrent::alert& alert);
};

#endif // NODE_LIBTORRENT_ALERT_HPP_INCLUDED
