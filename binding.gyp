{
  'includes': [
    './common.gypi'
  ],
  'target_defaults': {
    'include_dirs': [
      '<!(node -e "require(\'./include_dirs\')")'
    ],
  },
  'targets': [{
    'type': 'loadable_module',
    'target_name': 'libtorrent-rasterbar',
    'product_name': 'libtorrent-rasterbar',
    'sources': [
      './src/addon.cc',

      './src/alert.cc',
      './src/extensions.cc',
      './src/session.cc',
      './src/settings_pack.cc'
    ]
  }]
}
