'use strict'
const test = require('tape')

test('settings', (t) => {
  const libtorrent = require('../')

  test('nameForSetting/settingByName', (t) => {
    function extract (start, count) {
      const settings = {}
      for (let i = start; i !== start + count; ++i) {
        settings[libtorrent.settings.nameForSetting(i)] = i
      }
      return settings
    }

    const settings = Object.assign(
      extract(0x0000, libtorrent.settings.SettingsPack.numStringSettings),
      extract(0x4000, libtorrent.settings.SettingsPack.numIntSettings),
      extract(0x8000, libtorrent.settings.SettingsPack.numBoolSettings))

    for (let name of Object.keys(settings)) {
      t.equal(libtorrent.settings.settingByName(name), settings[name])
    }

    t.end()
  })

  t.end()
})
