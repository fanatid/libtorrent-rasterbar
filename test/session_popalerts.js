'use strict'
const test = require('tape')

test('Session#popAlerts', (t) => {
  const libtorrent = require('../')
  const Session = libtorrent.Session

  t.test('should return empty array', (t) => {
    const s = new Session()
    t.deepEqual(s.popAlerts(), [])

    t.end()
  })

  t.end()
})
