{
  'target_defaults': {
    'include_dirs': [
      '<!(node -e "require(\'nan\')")',
    ],
    'cflags': [
      '-Wall',
      '-Wno-maybe-uninitialized',
      '-Wno-uninitialized',
      '-Wno-unused-function',
      '-Wextra',
      '-fPIC'
    ],
    'cflags_cc!': [
      '-fno-rtti'
    ],
    'conditions': [
      ['OS=="win"', {
      }, {
        'cflags': [
          '<!(pkg-config --cflags libtorrent-rasterbar)'
        ],
        'libraries': [
          '<!(pkg-config --libs libtorrent-rasterbar)'
        ]
      }]
    ]
  }
}
