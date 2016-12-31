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
    'type': 'loadable_module',
    'target_name': 'session_addextension',
    'product_name': 'session_addextension',
    'sources': [
      './session_addextension.cc'
    ]
  }]
}
