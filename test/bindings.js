'use strict'
const bindings = require('bindings')

module.exports = function (name) {
  const keys = Object.keys(require.cache)
  const pkg = bindings({ bindings: name, module_root: __dirname })
  for (let key of Object.keys(require.cache)) {
    if (keys.indexOf(key) !== -1) delete require.cache[key]
  }

  return pkg
}
