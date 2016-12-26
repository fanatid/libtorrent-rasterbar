'use strict'
const test = require('tape')

test('Session', (t) => {
  const libtorrent = require('../')
  const Session = libtorrent.Session

  t.test('constructor', (t) => {
    t.test('without arguments', (t) => {
      t.true(new Session() instanceof Session)

      t.end()
    })

    t.test('pass SettingsPack', (t) => {
      const pack = new libtorrent.settings.SettingsPack()
      t.true(new Session(pack) instanceof Session)

      t.end()
    })

    t.test('pass SettingsPack and flags', (t) => {
      const pack = new libtorrent.settings.SettingsPack()
      const flags = Session.flags.ADD_DEFAULT_PLUGINS | Session.flags.START_DEFAULT_FEATURES
      t.true(new Session(pack, flags) instanceof Session)

      t.end()
    })

    t.end()
  })

  t.end()
})
