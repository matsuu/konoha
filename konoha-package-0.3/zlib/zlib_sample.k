#!/usr/local/bin/konoha

using zlib.*

Zlib z = new Zlib()
String s = "hello world"

x = z.compress(s);
y = z.decompress(x);

OUT << "original:" << s <<EOL;
OUT << "compressed:" << x << EOL;
OUT << "decompressed:" << y << EOL;

if (s == y) {
  OUT << "zlib working correctly." << EOL;
} else {
  OUT << "zlib working wrong." << EOL;
}
