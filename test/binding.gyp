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
    'target_name': 'addon_test',
    'product_name': 'addon_test',
    'sources': [
      './addon_test.cc'
    ]
  }]
}
