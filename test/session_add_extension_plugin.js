'use strict'
const test = require('tape')

test('Pass boost::shared_ptr<libtorrent::plugin> to Session::addExtension', (t) => {
  t.doesNotThrow(() => {
    const libtorrent = require('../')
    const addon = require('./bindings')('session_add_extension_plugin')

    const s = new libtorrent.Session()
    const ext = addon.create(libtorrent.extensions.PluginStorage)

    s.addExtension(ext)
  })

  t.end()
})
