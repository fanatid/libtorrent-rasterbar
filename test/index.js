'use strict'
const filenames = [
  // tests with other node module
  'session_add_extension_plugin'
]

for (let filename of filenames) require(`./${filename}`)
