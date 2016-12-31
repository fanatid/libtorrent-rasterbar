'use strict'
const test = require('tape')

test('Session#popAlerts', (t) => {
  const libtorrent = require('../')
  const addon = require('./bindings')('session_popalerts')
  const Session = libtorrent.Session

  t.test('should return empty array', (t) => {
    const s = new Session()
    t.deepEqual(s.popAlerts(), [])

    t.end()
  })

  t.test('custom alert', (t) => {
    t.plan(4)

    const s = new Session()
    s.asyncAddTorrent({
      url: '?',
      savePath: './tmp'
    })

    setTimeout(() => {
      const TorrentAlert = libtorrent.alerts.alerts[libtorrent.alerts.types.TORRENT_ALERT]
      const TorrentAddedAlert = libtorrent.alerts.alerts[libtorrent.alerts.types.TORRENT_ADDED_ALERT]
      const TorrentErrorAlert = addon.createTorrentErrorAlert(TorrentAlert)
      const alertsMap = Object.assign({}, libtorrent.alerts.alerts)
      alertsMap[libtorrent.alerts.types.TORRENT_ERROR_ALERT] = TorrentErrorAlert

      const alerts = s.popAlerts(alertsMap)
      for (let alert of alerts) {
        switch (alert.type()) {
          case libtorrent.alerts.types.TORRENT_ADDED_ALERT:
            t.true(alert instanceof TorrentAddedAlert)
            break

          case libtorrent.alerts.types.TORRENT_ERROR_ALERT:
            t.true(alert instanceof TorrentErrorAlert)
            t.equal(alert.error, 'unsupported URL protocol')
            t.notEqual(alert.torrentName, undefined)
            break
        }
      }

      t.end()
    }, 100)
  })

  t.end()
})
