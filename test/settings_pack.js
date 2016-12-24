'use strict'
const test = require('tape')

test('SettingsPack', (t) => {
  const libtorrent = require('../')

  const fixtures = [{
    type: 'string',
    name: 0x0000,
    value: 'Hello world!'
  }, {
    type: 'int',
    name: 0x4000,
    value: 42
  }, {
    type: 'bool',
    name: 0x8000,
    value: true
  }]

  for (let fixture of fixtures) {
    t.test(`has/set/has/get/clear/has (type: ${fixture.type}, name: ${fixture.name})`, (t) => {
      const pack = new libtorrent.settings.SettingsPack()
      t.false(pack.has(fixture.name))
      pack.set(fixture.name, fixture.value)
      t.true(pack.has(fixture.name))
      t.equal(pack.get(fixture.name), fixture.value)
      pack.clear()
      t.false(pack.has(fixture.name))
      t.end()
    })
  }

  t.end()
})
