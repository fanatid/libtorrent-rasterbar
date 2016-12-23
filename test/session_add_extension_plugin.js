'use strict'
const test = require('tape')

test('Pass Plugin to Session#addExtension', (t) => {
  t.doesNotThrow(() => {
    const libtorrent = require('../')
    const addon = require('./bindings')('session_add_extension_plugin')

    const s = new libtorrent.Session()
    const ext = addon.create(libtorrent.extensions.Plugin)

    s.addExtension(ext)
  })

  t.end()
})
