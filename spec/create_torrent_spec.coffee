describe "create_torrent.cpp", ->
  lt = undefined

  beforeEach ->
    lt = require "../build/Release/libtorrent"

  it "add_files function", ->
    expect(lt.add_files).toBeDefined()

  it "set_piece_hashes function", ->
    expect(lt.set_piece_hashes).toBeDefined()

  describe "create_torrent class", ->
    fs = undefined
    ct = undefined

    beforeEach ->
      fs = new lt.file_storage()
      lt.add_files(fs, "./resources")
      ct = new lt.create_torrent(fs)

    it "constructor", ->
      expect(lt.create_torrent).toBeDefined()

    it "generate method", ->
      expect(ct.generate).toBeDefined()
