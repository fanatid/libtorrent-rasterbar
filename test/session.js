'use strict'
const test = require('tape')

test('session', (t) => {
  const libtorrent = require('../')

  t.test('constructor', (t) => {
    t.test('without arguments', (t) => {
      t.true(new libtorrent.Session() instanceof libtorrent.Session)

      t.end()
    })

    t.test('pass SettingsPack', (t) => {
      const pack = new libtorrent.settings.SettingsPack()
      t.true(new libtorrent.Session(pack) instanceof libtorrent.Session)

      t.end()
    })

    t.test('pass SettingsPack and flags', (t) => {
      const pack = new libtorrent.settings.SettingsPack()
      const flags = libtorrent.Session.flags.addDefaultPlugins | libtorrent.Session.flags.startDefaultfeatures
      t.true(new libtorrent.Session(pack, flags) instanceof libtorrent.Session)

      t.end()
    })

    t.end()
  })

  t.end()
})
