'use strict'
const bindings = require('bindings')

module.exports = function (name) {
  return bindings({ bindings: name, module_root: __dirname })
}
