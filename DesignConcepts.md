# NGtk Design Concepts #

## Root Window ##

There will be ONE Root Window, which will be created INVISIBLE upon
request. When closed, the main event loop will exit and the window will
no longer be valid. A new window can be created when the previous one
was destroyed.

Windows are also event generators like regular widgets and they can
also receive the keyboard focus (detailed later). They are created
ENABLED by default.

## Widgets ##

A widget can be created only in reference to it's parent container (for
now, the only container is the root window). The widget will not be
valid outside of the container - removing it from the container will
free all the resources allocated with it (and vice versa - freeing it
will remove it from it's container). Moving widgets between two
containers will not be possible - the widget will have to be duplicated
manually by the user.

Widgets are created ENABLED and INVISIBLE by default.

## Memory Management ##

When a container is destroyed, it will destroy and free all of it's
child widgets. Since every widget is associated with exactly one
container (not more, not less) at each moment, then there is no need to
free a widget explicitly - since it will be freed with it's parent or
upon removal from it's parent.

## Layout ##

Each container (just the root window for now) may have a layout object.
A layout is an abstract object which is associated with one or more
containers, and knows how to position the child widgets of each of it's
associated containers. Whenever a component is resized, if it has a
layout object then the "pack" method of that layout object will be
called with the new size of the widget, to lay-out its children.

## Event Handling ##

Each widget may generate Mouse and Keyboard events as long as it's
ENABLED. Events are passed to listener functions which are registered
with the widget (if any listeners were in fact registered). Each
listener may be associated with some pointer to some data, and a
function to free that data when the listener is removed. Note that the
free function will only be called on the data if the data is not NULL.

Currently, listeners can only be removed from widgets when the widget
is destroyed (and then their data will be freed if both a non NULL
free function and a non NULL data was specified).