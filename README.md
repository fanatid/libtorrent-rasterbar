# node-libtorrent-mt

node-libtorrent provides native bindings to [libtorrent rastebar](http://www.rasterbar.com/products/libtorrent/) as a [Node.js addon](http://nodejs.org/docs/latest/api/addons.html).

this is a for of https://github.com/fanatid/node-libtorrent

# Getting started
Execute in command line:
```
$ npm install node-libtorrent-mt
```
or copy repository and build bindings manually
```
$ git clone git://github.com/martintrojer/node-libtorrent.git
$ cd node-libtorrent
$ npm install -g node-gyp
$ node-gyp configure
$ node-gyp build
```

# Examples
#### Simple client
```coffeescript
lt = require "../build/Release/libtorrent"

s = new lt.session()
s.listen_on([6881, 6889])
ti = new lt.torrent_info "./test.torrent"
th = s.add_torrent
  ti: ti
  save_path: "./test_torrent"
main = ->
  st = th.status()
  console.log "#{st.progress*100} complete \
(down: #{st.download_rate / 1000} kb/s | up: #{st.upload_rate / 1000} kB/s | \
peers: #{st.num_peers})"
  setTimeout main, 2500
main()
```

#### Create torrent
```coffeescript
lt = require "../build/Release/libtorrent"

fs = new lt.file_storage()
lt.add_files fs, "./src"
ct = new lt.create_torrent(fs)
lt.set_piece_hashes ct, "."
t = lt.bencode ct.generate()
console.log t
```
