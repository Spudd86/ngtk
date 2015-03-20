# Event Generation #

## Minimal Event Generation Conditions ##

A component may generate events due to user interaction, only if it satisfies both of the following conditions:

  * The component is visible
  * The component is enabled

Since the functions to fire an event programmatically should be exactly like as if the user did an event himself, then invoking them will do nothing if the component is in a state where it may not generate events.

An exception to that rule is **the root window which can always generate events as long as it's visible** (otherwise, a program may lock itself without the ability to receive events).

## Keyboard Focus ##

In addition to the above conditions, a component that wishes to be able to receive keyboard focus (to generate keyboard events), must have it's `focusable` property set to `TRUE`. **The `focusable` property is set upon object creation and can not be changed at runtime!** In a similar fashion to regular event generation, **the root window is also always focusable**!

## Focus transferal ##

  * Keyboard focus begins on the root window.
  * Pressing `Tab` transfers the focus to the next focusable component, `Shift + Tab` to transfer it to the previous focusable component.
  * Inside a container, the first to receive the focus is the container itself, then it's children by the order they were added, then then it's the sibling of the container (like children in the parent container). Of course that if any of these is not focusable, focus will skip it.
  * If a component that held the focus becomes non focusable, the focus goes to it's parent. If the parent is also not focusable, it goes to it's parent, and so on.

# Component Properties #

  * Components are created hidden (`visible = FALSE`)
  * Components are created enabled (`enabled = TRUE`)

# Widget Behaviour #

## Implemented Interfaces/Signals ##

| **Widget** | **`NGtkComponent`** | **`event::*`** | **`NGtkContainer`** |
|:-----------|:--------------------|:---------------|:--------------------|
| **Label** | V | X | X |
| **Button** | V | V | X |
| **Text-Entry** | V | V | X |
| **Window** | V | V | V |

## Redrawing ##

The functions to **redraw** widgets **must _not_ do any of the following:**

  * Change the property of any widget directly or indirectly
    * This means it may not change the keyboard focus to another widget, because focus-holding is a property of a widget, even if not a direct one
    * This means it nust not generate any signal (because signal handlers may change other widgets)
  * Call the redraw method of any other widget

These limitations are made to simplify the process of manually redrawing. Most properties do have some visual feedback and therefore changing them would cause a bad redrawing.

## Size Limitations ##

If a widget should have one of it's dimensions set to `0`, it's the backend's responsibility to handle this. Several graphical backends do not allow widgets of size `0` in any dimension, so to handle this they must be responsible to hide the widget (or destroy it's internal representation) and to show (or recreate) it again when the size allows.

## Overlapping Widgets (Don't!) ##

Widgets should not overlap, period. Any layout which causes widget to overlap, may cause undefined drawing behaviour in certain backends and/or corruption of event handling. **It's the responsibility of the layout manager to handle this!** It may do so by setting the dimensions of widgets to `0` if it's "too crowded" to put the widget under the current size limitations.

The only exception to this rule is of course the case of container widgets. All the children of a container are visible only in parts that overlap the container.

# Main-Loop #

## Start ##
Whenever the main loop is started, the root window will become visible. If no root window was created, the behaviour of starting the main loop is undefined.

## While in progress ##

Any attempt to set the root window invisible/disabled while the main loop is running, will cause undefined behaviour (most probably, an exception that will lead to quitting the main loop). Hiding the window would make it impossible to receive events, and so the main loop would get stuck. And since we don't allow multithreading with NGtk (where one thread can hide the window and the other would restore) then it's a situation that the NGtk user simply has no reason to reach anyway.

## Quit ##
If the main loop is exitted since the window is closed by the user, then it's destroyed with all of the child widgets. The same goes for the case where the main loop is exitted through a programmatic call to `ngtk_quit_main_loop ()`.