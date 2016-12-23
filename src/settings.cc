#include <libtorrent-rasterbar/settings_pack.h>
#include <libtorrent-rasterbar/macros.h>

namespace libtorrent_rasterbar {

NAN_METHOD(SettingByName) {
  REQUIRE_ARGUMENT_STRING(0, name);
  info.GetReturnValue().Set(Nan::New(libtorrent::setting_by_name(std::string(*name))));
}

NAN_METHOD(NameForSetting) {
  REQUIRE_ARGUMENT_NUMBER(0, s);
  info.GetReturnValue().Set(Nan::New(libtorrent::name_for_setting(s)).ToLocalChecked());
}

} // namespace libtorrent_rasterbar
