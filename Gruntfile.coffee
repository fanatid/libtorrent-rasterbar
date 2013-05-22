module.exports = (grunt) ->
	grunt.initConfig
    pkg: grunt.file.readJSON 'package.json'

  run_node_gyp = (task) ->
    ->
      child = grunt.util.spawn {
        cmd: './node_modules/node-gyp/bin/node-gyp.js'
        args: [task]
      }, @async()
      child.stdout.pipe process.stdout
      child.stderr.pipe process.stderr

  for task in ['build', 'clean', 'configure', 'rebuild', 'install', 'list', 'remove']
    grunt.registerTask task, "run node-gyp #{task}", run_node_gyp(task)

  grunt.registerTask 'docs', 'generate docs', ->
    # /*!modele::function
    #  * interface
    #  * docs...
    #  * link to libtorrent docs
    #  */
    #
    _    = require 'underscore'
    fs   = require 'fs'
    path = require 'path'

    config =
      source: 'src/'
      output: 'docs/'
      template: 'docs/node-libtorrent.jst'

    functions = {}
    objects = {}
    for name in fs.readdirSync(config.source)
      name = path.join(config.source, name)
      unless fs.statSync(name).isFile()
        continue
      lines = fs.readFileSync(name).toString().split '\n'
      title = undefined
      format = (line) ->
        loop
          repl = '<a href="$2">$1</a>'
          if line.indexOf('libtorrent documentation') != -1
            repl = '<a href="$2" target="_blank">$1</a>'
          new_line = line.replace /\[(.*?)\]\((.*?)\)/, repl
          break if new_line == line
          line = new_line
        new_line
      for line in lines
        if title?
          if line.indexOf('*/') == -1
            body.push format(line.slice(line.indexOf('* ')+2, line.length))
            continue
          if title.indexOf('::') == -1
            functions[title] = body
          else
            names = title.split('::')
            if names[0] not in _.keys(objects)
              objects[names[0]] = {}
            objects[names[0]][names[1]] = body
          title = undefined
        if line.indexOf('/*!') != -1
          title = line.slice line.indexOf('/*!')+3, line.length
          body  = []
    functions = _.sortBy(_.pairs(functions), (pair) -> pair[0])
    objects   = _.sortBy(_.pairs(objects), (f) -> f[0])
    objects = _.map objects, (object) ->
      [object[0], _.sortBy(_.pairs(object[1]), (pair) -> pair[0])]
    data = _.template fs.readFileSync(config.template).toString(),
      functions: functions,
      objects:   objects,
    fs.writeFileSync path.join(config.output, 'node-libtorrent.html'), data

  undefined
