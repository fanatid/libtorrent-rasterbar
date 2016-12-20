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
      '-fPIC',
      '<!(pkg-config --cflags libtorrent-rasterbar)'
    ],
    'libraries': [
      '<!(pkg-config --libs libtorrent-rasterbar)'
    ]
  }
}
