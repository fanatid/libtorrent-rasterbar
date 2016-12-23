'use strict'
const test = require('tape')

test('Session#popAlerts', (t) => {
  const libtorrent = require('../')

  const s = new libtorrent.Session()
  console.log(s.popAlerts(1))

  t.end()
})
