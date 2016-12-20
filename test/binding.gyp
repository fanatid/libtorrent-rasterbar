{
  'includes': [
    '../common.gypi'
  ],
  'target_defaults': {
    'include_dirs': [
      '<!(node -e "require(\'../include_dirs\')")'
    ],
  },
  'targets': [{
    'target_name': 'session_add_extension_plugin',
    'sources': [
      './session_add_extension_plugin.cc'
    ]
  }]
}
