'use strict'
const test = require('tape')
const path = require('path')
const fs = require('fs')

test('TorrentInfo', (t) => {
  const libtorrent = require('../')
  const TorrentInfo = libtorrent.torrent.TorrentInfo

  t.test('constructor', (t) => {
    const filename = path.join(__dirname, 'files', 'Fedora-Workstation-Live-x86_64-25.torrent')
    const buffer = fs.readFileSync(filename)

    t.test('without arguments', (t) => {
      t.throws(() => new TorrentInfo())
      t.end()
    })

    t.test('pass filename', (t) => {
      t.doesNotThrow(() => new TorrentInfo(filename))
      t.end()
    })

    t.test('pass buffer & size', (t) => {
      t.doesNotThrow(() => new TorrentInfo(buffer, buffer.length))
      t.end()
    })

    t.end()
  })

  t.end()
})
