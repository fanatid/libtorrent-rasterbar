'use strict'
const test = require('tape')

test('Session', (t) => {
  const libtorrent = require('../')
  const Session = libtorrent.session.Session

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
      const flags = Session.flags.addDefaultPlugins | Session.flags.startDefaultfeatures
      t.true(new Session(pack, flags) instanceof Session)

      t.end()
    })

    t.end()
  })

  t.test('#addExtension', (t) => {
    t.test('pass UTMetadata', (t) => {
      const session = new Session()
      session.addExtension(libtorrent.extensions.UTMetadata)

      t.end()
    })

    t.test('pass Plugin', (t) => {
      const addon = require('./addon_test')
      const ext = addon.createEmptyPlugin(libtorrent.extensions.Plugin)

      const session = new Session()
      session.addExtension(ext)

      t.end()
    })

    t.end()
  })

  t.test('#popAlerts', (t) => {
    t.test('pop 1 alert', (t) => {
      const s = new Session()
      t.deepEqual(s.popAlerts(1), [])

      t.end()
    })

    t.end()
  })

  t.end()
})
