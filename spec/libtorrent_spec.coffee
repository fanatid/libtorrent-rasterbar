describe "must be defined", ->
  lt = undefined

  beforeEach ->
    lt = require "../build/Release/libtorrent"

  describe "bencode.cpp", ->
    it "bencode", ->
      expect(lt.bencode).toBeDefined()

  describe "create_torrent.cpp", ->
    it "addFiles", ->
      expect(lt.addFiles).toBeDefined()

    it "setPieceHashes", ->
      expect(lt.setPieceHashes).toBeDefined()

    it "CreateTorrent", ->
      expect(lt.CreateTorrent).toBeDefined()

  describe "file_storage.cpp", ->
    it "FileStorage", ->
      expect(lt.FileStorage).toBeDefined()

  it "version", ->
    expect(lt.version).toBeDefined()
