'use strict'
const bindings = require('bindings')

module.exports = (name) => bindings({ bindings: name, module_root: __dirname })
