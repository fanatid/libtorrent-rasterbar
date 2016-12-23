#ifndef LIBTORRENT_RASTERBAR_SETTINGS_H_
#define LIBTORRENT_RASTERBAR_SETTINGS_H_

#include <nan.h>
#include <libtorrent/settings_pack.hpp>

namespace libtorrent_rasterbar {

NAN_METHOD(SettingByName);
NAN_METHOD(NameForSetting);

} // namespace libtorrent_rasterbar

#endif // LIBTORRENT_RASTERBAR_SETTINGS_H_
