describe "must be defined", ->
  lt = undefined

  beforeEach ->
    lt = require "../build/Release/libtorrent"
