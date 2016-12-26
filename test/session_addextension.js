'use strict'
const test = require('tape')

test('Session#addTorrent', (t) => {
  const libtorrent = require('../')
  const Session = libtorrent.Session

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
