describe "file_storage.cpp", ->
  lt = undefined

  beforeEach ->
    lt = require "../build/Release/libtorrent"

  describe "file_storage class", ->
    fs = undefined

    beforeEach ->
      fs = new lt.file_storage()

    it "constructor", ->
      expect(lt.file_storage).toBeDefined()

    it "is_valid method", ->
      expect(fs.is_valid).toBeDefined()

    it "num_files method", ->
      expect(fs.num_files).toBeDefined()

    it "total_size method", ->
      expect(fs.total_size).toBeDefined()

    it "set_num_pieces method", ->
      expect(fs.set_num_pieces).toBeDefined()

    it "num_pieces method", ->
      expect(fs.num_pieces).toBeDefined()
