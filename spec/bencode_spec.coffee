describe "bencode.cpp", ->
  lt = undefined

  beforeEach ->
    lt = require "../build/Release/libtorrent"

  it "bencode function", ->
    expect(lt.bencode).toBeDefined()
