'use strict'
const DEFAULT_FILENAMES = [
  'session',
  'session_add_extension',
  'session_pop_alerts',
  'settings',
  'settings_pack'
]

const filenames = process.env.FILENAMES && process.env.FILENAMES.split(',') || DEFAULT_FILENAMES
for (let filename of filenames) require(`./${filename}`)
