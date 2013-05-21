lt = require "../build/Release/libtorrent"

fs = new lt.FileStorage()
lt.addFiles(fs, "./spec")
ct = new lt.CreateTorrent(fs)
lt.setPieceHashes ct, "."
t = lt.bencode ct.generate()
console.log t
