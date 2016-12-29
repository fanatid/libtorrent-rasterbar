'use strict'
const test = require('tape')
const path = require('path')
const fs = require('fs')

test('bencoding', (t) => {
  const libtorrent = require('../')

  test('bdecode/bencode simple data', (t) => {
    // {
    //   string: 'Hello World',
    //   integer: 12345,
    //   dict: {
    //     key: 'This is a string within a dictionary'
    //   },
    //   list: [ 1, 2, 3, 4, 'string', 5, {} ]
    // }
    const fixture = 'd4:dictd3:key36:This is a string within a dictionarye7:integeri12345e4:listli1ei2ei3ei4e6:stringi5edee6:string11:Hello Worlde'

    const data = libtorrent.bencoding.decode(Buffer.from(fixture))
    const buffer = libtorrent.bencoding.encode(data)
    t.equal(buffer.toString(), fixture)

    t.end()
  })

  test('bdecode/bencode torrent file', (t) => {
    const filename = path.join(__dirname, 'files', 'Fedora-Workstation-Live-x86_64-25.torrent')
    const torrent = fs.readFileSync(filename)

    const data = libtorrent.bencoding.decode(torrent)
    const buffer = libtorrent.bencoding.encode(data)
    t.true(torrent.equals(buffer))

    t.end()
  })

  t.end()
})
