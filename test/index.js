'use strict'
const spawnSync = require('child_process').spawnSync
const DEFAULT_FILENAMES = [
  'session',
  'session_addextension',
  'session_addtorrent',
  'session_popalerts',
  'settings',
  'settings_pack',
  'torrent_info'
]

let exitCode = 0

const filenames = process.env.FILENAMES && process.env.FILENAMES.split(',') || DEFAULT_FILENAMES
for (let filename of filenames) {
  const child = spawnSync('tape', [`${filename}.js`], { stdio: 'inherit' })
  if (exitCode === 0 && child.status !== 0) exitCode = child.status
}

process.exit(exitCode)
