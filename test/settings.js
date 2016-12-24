'use strict'
const test = require('tape')

test('settings', (t) => {
  const libtorrent = require('../')

  t.test('nameForSetting/settingByName', (t) => {
    function extract (start, count) {
      const settings = {}
      for (let i = start; i !== start + count; ++i) {
        settings[libtorrent.settings.nameForSetting(i)] = i
      }
      return settings
    }

    const settings = Object.assign(
      extract(0x0000, libtorrent.settings.SettingsPack.numStringSettings),
      extract(0x4000, libtorrent.settings.SettingsPack.numNumberSettings),
      extract(0x8000, libtorrent.settings.SettingsPack.numBooleanSettings))

    const byName = Object.keys(settings).reduce((obj, name) => {
      return Object.assign(obj, { [name]: libtorrent.settings.settingByName(name) })
    }, {})

    t.deepEqual(settings, byName)
    t.end()
  })

  t.end()
})
