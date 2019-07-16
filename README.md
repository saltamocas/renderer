# renderer
A simple renderer to be compiled with mapnik libraries.

```
alf@alf-xps-13-9360:~/eclipse-workspace/mapmake$ ./render
Mapnik 3.0.22
XML mapnik renderer

render <options>

Options:
-s <style.xml>      XML style file
-r srs              proj4 projection, defaults to '+init=epsg:3763'
-o <output.png>     Output file. Must include extension png, jpg or tif. Defaults to out.png
-w <width>          Width of output image in pixels (defaults to 400)
-h <height>         Height of output image in pixels (defaults to 400)
-x <coordinate>     top x coordinate of area
-y <coordinate>     top y coordinate of area
-X <coordinate>     bottom x coordinate of area
-Y <coordinate>     bottom y coordinate of area
```
plugins directory are hardcoded to _/usr/local/lib/mapnik/input_
