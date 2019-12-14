# Gradient in Terminal

A **C** program which prints an animated linear gradient
___

## Usage

Run `make` in the `src/` directory to build the program,
then either run `make run` to execute it or run `make install` to
copy the binary to `/usr/local/bin/`.

It currently runs at 60FPS, if your terminal cannot handle it you might want to
use __*[Alacritty](https://github.com/jwilm/alacritty)*__.

I will add an **FPS** option in the future.
___
By default it will have a pinkish and a cyanish color as the initial values.

You can give your own colors: `bin/main "#xxxxxx" "#xxxxxx"` where `#xxxxxx`
is a six digit hexadecimal number corresponding to the RGB value you want.

`#FF00FF` would be **Magenta**.

Or a weirder syntax with `rgb(R, G, B)` where all three RGB values
are in the range __[0, 255]__

_You can edit the Makefile to change the installation location and the
binary name._

## Short Clip of the Default Program



