'use strict'
const test = require('tape')

test('Session#addExtension', (t) => {
  t.test('pass Plugin', (t) => {
    const libtorrent = require('../')
    const addon = require('./bindings')('session_add_extension')

    const s = new libtorrent.Session()
    const ext = addon.createEmptyPlugin(libtorrent.extensions.Plugin)

    s.addExtension(ext)

    t.end()
  })

  t.end()
})
