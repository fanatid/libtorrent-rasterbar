'use strict'
const test = require('tape')

test('settings', (t) => {
  const libtorrent = require('../')

  t.test('nameForSetting/settingByName', (t) => {
    function extract (data) {
      const settings = {}
      for (let i = data.offset; i !== data.offset + data.count; ++i) {
        settings[libtorrent.settings.nameForSetting(i)] = i
      }
      return settings
    }

    const settings = Object.assign(
      extract(libtorrent.settings.STRING),
      extract(libtorrent.settings.NUMBER),
      extract(libtorrent.settings.BOOLEAN))

    const byName = Object.keys(settings).reduce((obj, name) => {
      return Object.assign(obj, { [name]: libtorrent.settings.settingByName(name) })
    }, {})

    t.deepEqual(settings, byName)
    t.end()
  })

  t.end()
})
