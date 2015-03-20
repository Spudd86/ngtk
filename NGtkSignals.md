Unless otherwise stated, all events generated in an interface are also passed to the parent object (with the `NGtkObject` as the source).

| **Name** | **Source** | **Reason** | **Value** (3rd listener parameter) |
|:---------|:-----------|:-----------|:-----------------------------------|
| `"event::mouse"` | `NGtkComponentI` | Called after a user mouse event | `NGtkMouseEvent*` ||e|
| `"event::keyboard"` | `NGtkComponentI` | Called after a user keyboard event | `NGtkKeyboardEvent*` |
| `"event::resize"` | `NGtkContainer` (root window) | Called after a user resized the window | `const NGtkRectangle*` (the new area) |
| `"structure::child-add"` | `NGtkContainerI` | Called right after a child was added | The child (`NGtkComponent*`) |
| `"structure::child-rem"` | `NGtkContainerI` | Called right before a child is removed | The child (`NGtkComponent*`) |
| `"backend::create-lab"` | `NGtkBackendI` | Called right after creating a label | `NGtkComponent*` (the label) |
| `"backend::create-but"` | `NGtkBackendI` | Called right after creating a button | `NGtkComponent*` (the button) |
| `"backend::create-te"` | `NGtkBackendI` | Called right after creating a text entry | `NGtkComponent*` (the text entry) |
| `"backend::create-wnd"` | `NGtkBackendI` | Called right after creating the root window | `NGtkContainer*` (the root window) |