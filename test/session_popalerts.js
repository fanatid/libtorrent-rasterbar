'use strict'
const test = require('tape')

test('Session#popAlerts', (t) => {
  const libtorrent = require('../')
  const Session = libtorrent.session.Session

  t.test('pop 1 alert', (t) => {
    const s = new Session()
    t.deepEqual(s.popAlerts(1), [])

    t.end()
  })

  t.end()
})
