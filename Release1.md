# Minimal Requirements for Release 1.0 #

## Minimal set of platforms ##
  * Windows API
  * NCurses
  * Xlib

## Minimal set of correctly supported widgets ##
  * Windows
  * Buttons
  * Labels

## Minimal set of widget properties ##
  * Text
  * Visibility

## Minimal set of correctly supported events ##

### Mouse ###
  * Left, Right and Middle buttons
  * Button Down (press), Up (Release) and Click (one after another on the same component)

### Keyboard ###
  * Type event (no seperation between press and release)
  * Left/Right/Up/Down arrow
  * Spacebar
  * Backspace
  * Enter (Return)
  * Printable Non-Space basic ascii characters (33-126). See [the ascii table](http://www.asciitable.com/).

## Minimal Demo Programs ##
  * Standard Calculator