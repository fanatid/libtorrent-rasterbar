'use strict'
const test = require('tape')

test('Session#addTorrent', (t) => {
  const libtorrent = require('../')
  const Session = libtorrent.session.Session

  t.test('without arguments', (t) => {
    const s = new Session()
    const th = s.addTorrent()
    t.equal(th.constructor.name, 'TorrentHandle')

    t.end()
  })

  t.end()
})
