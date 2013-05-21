# node-libtorrent

node-libtorrent provides native bindings to [libtorrent rastebar](http://www.rasterbar.com/products/libtorrent/) as a [Node.js addon](http://nodejs.org/docs/latest/api/addons.html).

# Getting started
From your project diretctory, run:
```
$ git clone git://github.com/fanatid/node-libtorrent.git
$ cd node-libtorrent
$ npm install -g node-gyp
$ node-gyp configure
$ node-gyp build
```

# Examples
#### Create torrent
```coffeescript
lt = require "./build/Release/libtorrent"

fs = new lt.FileStorage()
lt.addFiles(fs, "./spec")
ct = new lt.CreateTorrent(fs)
lt.setPieceHashes ct, "."
t = lt.bencode ct.generate()
console.log t
```
