'use strict'
const DEFAULT_FILENAMES = [
  'session_add_extension_plugin',
  'session_pop_alerts',
  'settings_pack'
]

const filenames = process.env.FILENAMES && process.env.FILENAMES.split(',') || DEFAULT_FILENAMES
for (let filename of filenames) require(`./${filename}`)
