# ledwall

This is just code sketches for experimenting with driving LPD8806 display 
with LPC1768 and not finished code.  However I put it here for convenience
and in case it would be useful for someone else.

# Installing build toolchain on OSX

In order to use this you need to install the GCC compiler for the ARM
targets.  Assuming that you have [Homebrew](http://brew.sh/) installed
you can run the following commands:

    brew tap PX4/homebrew-px4
    brew update
    brew install gcc-arm-none-eabi-49
	brew link gcc-arm-none-eabi-49

This uses the Homebrew formulae of the
[PX4 Pro Drone Autopilot](https://github.com/PX4) GitHub
organization.  *If there is a better tap for these Homebrew formulae
please send me a pull request.*
