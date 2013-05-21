describe "file_storage.cpp", ->
  lt = undefined

  beforeEach ->
    lt = require "../build/Release/libtorrent"

  describe "FileStorage", ->
    fs = undefined

    beforeEach ->
      fs = new lt.FileStorage()

    it "isValid", ->
      expect(fs.isValid).toBeDefined()

    it "numFiles", ->
      expect(fs.numFiles).toBeDefined()

    it "totalSize", ->
      expect(fs.totalSize).toBeDefined()

    it "setNumPieces", ->
      expect(fs.setNumPieces).toBeDefined()

    it "numPieces", ->
      expect(fs.numPieces).toBeDefined()
