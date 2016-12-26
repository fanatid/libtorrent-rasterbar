'use strict'
const test = require('tape')

test('SettingsPack', (t) => {
  const libtorrent = require('../')

  const fixtures = [{
    type: 'string',
    name: libtorrent.settings.STRING.offset,
    value: 'Hello world!'
  }, {
    type: 'int',
    name: libtorrent.settings.NUMBER.offset,
    value: 42
  }, {
    type: 'bool',
    name: libtorrent.settings.BOOLEAN.offset,
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
