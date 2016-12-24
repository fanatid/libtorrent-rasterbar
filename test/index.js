'use strict'
const DEFAULT_FILENAMES = [
  'session',
  'settings',
  'settings_pack',
  'torrent_info'
]

const filenames = process.env.FILENAMES && process.env.FILENAMES.split(',') || DEFAULT_FILENAMES
for (let filename of filenames) require(`./${filename}`)
