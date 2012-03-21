# CSS Cross Country (Code School)

## Level 1

### Adding CSS to HTML

How can you add CSS to HTML? Easy:

+ Inline selectors --- but they're bad; don't do it.
+ In the document's head --- also not a great idea; don't do it.
+ External stylesheet with a link in the head. Do it. Good.

### Selectors

They will primarily work with element, class and id selectors. Cool.

### Cascade order

CSS has two notions of cascade. First, where style declarations are found
in your application. Second, where properties are declared in your style
sheet.

The first, in increasing order of priority:

+ External (link)
+ In the head
+ Inline
+ Using !important (a bad idea, generally)

The second simply says that styles declared later in one sheet override
styles set earlier.

Wherever styles don't conflict, they combine.

### Floats

We all use them, but what do floats really do? Floating an element removes
that object from the normal document flow and moves it to a specified edge
of the document. Any other content inside the parent element will wrap
around the float.

Floated elements will stack up along the parent edge until they no longer
fit. At that point, new elements will move down to the next available edge.
Note that if you have floated items of different sizes, things get a bit
wonky. If the first floated element is higher than the rest, then overflow
items will stack up against the first element's edge rather than moving all
the way to the parent element's edge. If you float two items in opposite
directions and their container box becomes too small, the second one will
move down below.

## Level 2

### Clearfix

When is clearing necessary? First, non-floated content in the container
element may be smaller than the floated element. In that case, you can get
ugly underflow problems. Also, if all the content in a container is
floating (say li items in a ul), then you need to clear the container.

How can you clear?

+ Clear by adding the clear property to a subsequent element. Downsides: it
  breaks if you move elements around, and it doesn't handle borders and
  backgrounds from the container of the floated element when the floated
  element in larger than the container.
+ A manual clear adds a sibling empty element inside the container of the
  floated item. It does handle borders and backgrounds, but it also has
  downsides. It requires an empty element, and those extra HTML elements
  may become unnecessary later.
+ Finally, there's the clearfix. This is the best choice, though it
  involves some fancier CSS. You add a group class to any container which
  has floated elements inside it.

    .group:before, .group:after { 
      content: "";
      display: table;
    }
    .group:after { 
      clear: both;
    }
    .group { 
      zoom: 1; // IE6 and IE7
    }

### Inheritance and specificity

Nested elements automatically inherit parent styles. You can override
parent properties with a nested selector.

In addition, we have to worry about the specificity of selectors. For
example, if a class selector and an id selector both try to set something,
the id selector will win out. Why? The answer is specificity.

To determine the specificity of a selector, you can calculate its priority
along four measures.

    0, 0, 0, 0

The last digit measures the number of element selectors. The third counts
the total number of class selectors. The second counts id selectors, and
the first considers whether or not there are inline styles. (An important
value in a declaration can override all of this anyhow.)

## Level 3

### The box model

Every element on the page is outlined by a box - with sub-boxes for the
content area, padding, border and margin. The width is calculated as
follows: content width + padding width + border width.

What happens when content overflows its box? The overflow property controls
this. It can be set to visible, auto, hidden or scroll. Visible simply
breaks the boundaries of the box. Auto will add scrollbars as needed if
there's overflow. Hidden will never add scroll or break any boundary. It
hides extra content. Scroll will always add scrollbars, even if there's no
overflow.

We can also control positioning with the position property. The choices for
position are static, relative, absolute and fixed. (The default is static.)
If you use any value other than static, the object is considered
a positioned element. Such positioned elements can use top, left, bottom or
right properties for placement.

As an example, here's how you might do a superscript (with a `<sup>`
element):

    sup {
      position: relative;
      top: -0.5em;
    }

So what do the non-static options do?

+ relative: renders in the normal flow, then shifted with positioning
  properties (top, left, bottom and right)
+ absolute: renders outside the normal flow for manual positioning
+ fixed: fixes an element to a specific place in the window, regardless of
  scrolling

When dealing with absolute positioning, there's a danger. Unless the
surrounding element is a positioned one, the absolute element will stay
with the page only if the window and the surrounding element stay the same
size. If the window is expanded, then the absolute element will move along
with it. A solution is to make sure that the surrounding element is
positioned with `position: relative` (and no placement properties).

When multiple items are positioned, you can get overlap. the z-index
property controls overlap manually. If therer's no z-index set or they are
equal, then overlap is determined by DOM order (second overlaps first).
Otherwise, the higher z-index wins. Only positioned elements allow z-index
to take effect.

## Level 4

### Be DRY

DRY applies to CSS as well as to code. Rather than, for example, setting
font-family over and over, you might pull it into the body element or
a parent container. Or you can use a combined selector. Finally, you can
use selector abstraction. Find things that have significant overlap and
make one class out of them (say a single button class). Even if they are
only 80% the same, pull all the similarities into one class, and use
a second class later for the bits that differ.

Always remember to use shorthand properties where you can to avoid a lot of
extra declarations for left, right, etc. Important shorthand properties:

+ font - size/line-height weight, style, family
+ background - color, image, repeat, x-pos, y-pos
+ list-style - style, position, image
+ margin - top, right, bottom, left
+ padding - top, right, bottom, left
+ border - width, style, color

### Display types

Important display types:

+ none
+ block
+ inline
+ inline-block

Block elements stretch the full width of their container, behave as though
there is a line break before and after them and allow you to manipulate the
full box model.

Inline elements, on the other hand, typically fall within block-level
elements, do not take up the full width of their container and don't
generate a line break before or after.

Inline-block elements don't take up the full width of their container or
add new lines before or after, but you can manipulate the full box model
for them.

So to create a button, for example, you can set the display type to block
in order to have the item take up the full width of its container and have
a newline before and after it.

### Horizontal centering

Centering a block-level element is best done by declaring a width and then
setting left and right margins to auto.

For inline and inline-block elements, just use `text-align: center`.
