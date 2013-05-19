describe "version", ->
  lt = undefined

  beforeEach ->
    lt = require "../build/Release/libtorrent"

  it "version must be defined", ->
    expect(lt.version).toBeDefined()

  it "version has 4 numbers separated by dots", ->
    expect(/\d+\.\d+\.\d+\.\d+/.test lt.version).toBe true
