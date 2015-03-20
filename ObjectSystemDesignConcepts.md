# The Object System #

## Introduction ##

The term "inherits" is used in a very "liberal" way in this object
system. The inheritance mechanisem can sometimes be used as a
delegation method for code reuse. Although not exactly correct in terms
of OOP, it is very handy and prevents the need for additional syntax.
Each object is actually a combination of implementations (full or
partial) for different interfaces. These can be connected and
disconnected from the object at runtime.

This object system is not designed for learning OOP. It allows making
as many sins as one wants, to make it a powerful tool in the hands of
a skilled programmer. It allows getting rid of most annoyances and
limitations of inheritance in languages such as C++ (that was the
original reason of it's creation) but it forces the programmer to
keep track of what he is doing.

This object system has nearly no static type checking, but lots of things
are checked dynamically through the usage of predefined macros of the
object system. This has some runtime penalty and therefore should not
be used on high preformance code without propper caching of macro
results. It does operate very very fast for each type checking/casting
operation, but these are done on the fly in many places. So these must
be cached in order to acheive high preformance.

In general, this object system is meant for systems where either the
work done outside of the object logic is much more computationally
expensive (such as drawing, and intense mathematical computations) or
for people that are willing to work with their objects in a very low
level.

## Multiple Non-Duplicate Inheritance Chains ##

NGtk has a simple object system implemented in C. In that system, each
object may implement zero or more interfaces. Each interface may be
implemented by a chain of implementations, where each implementation
implements a part (or whole) of the interface. Each implementation may
also call functions of it's base (super) implementations. Note that
when we say a chain, we mean a series of implementations where each
one is derived from the previous implementation.

Each object may implemented many interfaces, each with a different
implementation chain. Dynamically, an implementation may check if
the object it's a part of also implements another itnerface, and if so
call the functions of that interface.

Type checking is only done dynamically. Although this may sound bad at
first, it allows attaching implementations of more interfaces to
objects at runtime.

## Custom instance data with a custom destructor ##

Each object, regardless of it's class and type, may be associated with
some custom data and a function to call on that data to free it a moment
before the object is destroyed. The free function will be called on the
data only if the data is not NULL (and the free function is not NULL).

## Construction & Destruction ##

The construction order of an object is user controlled. He first
creates an empty object, and then each time creates an interface
implementation and attaches it to the object. This custom control
allows using implementations that depend on other interfaces for
their construction.

Destruction of the object is done by calling a list of destructor functions, one after the other. At any moment, one can "push" a destructor to the "destructor stack" of the object. This means prepending a destructor to the begining of the destructor list (LIFO). This allows simulating traditional destruction of objects - subclasses (subimplementations), that were created when their parent classes (implementations) were already constructed, add destructors that will be executed before the destructors of the parents.

Every object that implements an interface `In`, must explicitly call the interface detachment function before it's destruction ends. If the detachment function for all the implemented interfaces isn't called, a runtime exception is thrown to indicate that. This is a meachnisem to make sure that no memory is leaked because a call to some destructor was missed. Usually, the base implementation of each interface will call the interface detachment function at the end of it's own destructor. (Reminder, interfaces are attached to objects at runtime - an object is created initially with no interfaces/implementations).

## Signals ##
Each object may generate "signals" - this means that a "listener" can register itself as interested in events of the object. When an "interesting" event happens, the object can "signal" to all the listeners that that event happened.

Now, for the more detailed view:
  * A signal may be sent from either the object, or from one of it's interfaces (or more correctly, from one of the implementation levels of an interfaace).
  * When a signal is generated from an interface, it is passed only to those who explicitly asked to listen to that interface of the object. It's not passed to listeners who attached to the object itself, unless explicitly specified when generating the signal.
  * When an object generates a signal, none of the listeners who registered to listen for it's interfaces are notified. A signal from an interface may be passed to the object, but not the other way around! This is since listeners to itnerfaces are generally very target specific, while object listeners are more general since an object may generate many signals from many interfaces.
  * Each signal handler may ask to be notified on all signals or just a subgroup of them, it may register custom data to be passed to it (in addition to the signal specific data) and a function to free that data when the object/interface is freed.

## Advantages ##

  * With smart construction of objects, one can avoid the dreaded diamond problem which occures in C++ (and other system of multiple inheritance).

  * Virtual functions are easily created - a derived implementation of some interface simply assigns it's own function pointer into the struct containing the function pointers of the interface

  * Mixin' style inheritance (can be found in Scala) are very natural in this system. For example, if we have an `ArrayList` and a `LinkedList` both implementing the `List` interface, and also a `ListBasedStack` implementing the stack interface and depending on the fact that the object is also a list, then we can create at runtime a stack based on any of these lists by simply telling it to use a simple implementation. This is somehow similar to the effect that can be acheieved by delegation, but it's much easier to write.

  * Signals allow registering listeners for events, before the object can even genrate those events. And even if the object won't be able to generate these events in the future, no error will happen.

## Why not other object systems? ##

I needed an object system in C that was flexible, easy to use, and
wihout needing to write a lot of code to define objects. This kit has
just 2 short C files, with code that is easily understandable. It has
no external dependancies (Like GObject which depends on GLib) and it's
very easy to use. Finally, since it's a bit low-level, you won't reach a state where you don't know what is executed when - only things that you explicitly write will happen.