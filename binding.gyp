{
  "targets": [
    {
      "target_name": "libtorrent",
      "product_name": "libtorrent",
      "sources": [
      	"src/libtorrent.cpp",

        "src/bencode.cpp",
        "src/create_torrent.cpp",
        "src/entry.cpp",
        "src/file_storage.cpp",
        "src/session.cpp"
      ],
      "cflags_cc": [
        "-fPIC",
        "`pkg-config --cflags libtorrent-rasterbar`"
      ],
      "cflags_cc!": [
        "-fno-exceptions"
      ],
      "ldflags": [],
      "libraries": [
        "`pkg-config --libs libtorrent-rasterbar`"
      ],
      "conditions": [
        ["OS=='linux'", {  
        }]
      ]
    }
  ]
}