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
        "src/version.cpp"
      ],
      "conditions": [
        ["OS=='linux'", {
          "cflags": [
            "-fPIC",
            "`pkg-config --cflags libtorrent-rasterbar`"
          ],
          "ldflags": [],
          "libraries": [
            "`pkg-config --libs libtorrent-rasterbar`"
          ]
        }]
      ]
    }
  ]
}