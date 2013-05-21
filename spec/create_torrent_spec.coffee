describe "create_torrent.cpp", ->
  lt = undefined

  beforeEach ->
    lt = require "../build/Release/libtorrent"

  describe "CreateTorrent", ->
    fs = undefined
    ct = undefined

    beforeEach ->
      fs = new lt.FileStorage()
      lt.addFiles(fs, "./resources")
      ct = new lt.CreateTorrent(fs)

    it "generate", ->
      expect(ct.generate).toBeDefined()
