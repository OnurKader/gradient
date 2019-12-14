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

By default it will have a pinkish and a cyanish color as the initial values.

You can give your own colors: `bin/main "#xxxxxx" "#xxxxxx"` where `#xxxxxx`
is a six digit hexadecimal number corresponding to the RGB value you want.

`#FF00FF` would be **Magenta**.

_You can edit the Makefile to change the installation location and the
binary name._
