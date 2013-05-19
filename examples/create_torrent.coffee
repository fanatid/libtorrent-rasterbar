lt = require "../build/Release/libtorrent"

fs = new lt.file_storage()
lt.add_files(fs, "./spec")
ct = new lt.create_torrent(fs)
lt.set_piece_hashes ct, "."
t = lt.bencode ct.generate()
console.log t
