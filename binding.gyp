{
  "targets": [
    {
      "target_name": "libtorrent",
      "product_name": "libtorrent",
      "sources": [
      	"src/module.cpp",

        "src/add_torrent_params.cpp",
        "src/alert.cpp",
        "src/bencode.cpp",
        "src/create_torrent.cpp",
        "src/entry.cpp",
        "src/file_storage.cpp",
        "src/fingerprint.cpp",
        "src/ip_filter.cpp",
        "src/peer_info.cpp",
        "src/rss.cpp",
        "src/session.cpp",
        "src/session_settings.cpp",
        "src/session_status.cpp",
        "src/storage.cpp",
        "src/torrent_handle.cpp",
        "src/torrent_info.cpp",
        "src/torrent_status.cpp"
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
        }],
        ["OS=='mac'", {
          "xcode_settings" : {
            "MACOSX_DEPLOYMENT_TARGET": "10.7",
            "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
            "OTHER_CFLAGS": [
              "-mmacosx-version-min=10.7", "-std=c++11", "-stdlib=libc++", "-O3", "-D__STDC_CONSTANT_MACROS", "-D_FILE_OFFSET_BITS=64", 
              "-D_LARGEFILE_SOURCE", "-fPIC", 
              "`pkg-config --cflags libtorrent-rasterbar`"
            ],
            "OTHER_CPLUSPLUSFLAGS": [
              "-mmacosx-version-min=10.7", "-std=c++11", "-stdlib=libc++", "-O3", "-D__STDC_CONSTANT_MACROS", "-D_FILE_OFFSET_BITS=64", 
              "-D_LARGEFILE_SOURCE", "-fPIC", 
              "`pkg-config --cflags libtorrent-rasterbar`"
            ]
          },
        }]
      ]
    }
  ]
}
