#ifndef __Ngtk_Events_MouseEvent_h__
#define __Ngtk_Events_MouseEvent_h__

namespace Ngtk
{
  namespace Events
  {

    enum MouseClickType
    {
      LEFT_CLICK,
      RIGHT_CLICK,
      MIDDLE_CLICK,
      SCROLL_UP,
      SCROLL_DOWN
    };

    struct MouseEvent
    {
    public:
      const MouseClickType mct;

      MouseEvent (MouseClickType mct);
    };
  }
}

#endif

