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

## Lesson 5

### Protecting your layout

Don't apply margin only to one element (that may disappear). Apply margins
to all elements, so that even if an element moves or disappears, your
overall layout will remain the same. Note: Don't forget margin collapsing.
Top and bottom margins are not additive; they collapse. However, margins do
not collapse when one or more block elements has padding, border, relative
or absolute positioning or a left or right float.

### Specificity problems

If you have a set of styles defined for something like `.sidebar ul li`,
you have to remember various problems that may occur. First, those styles
won't apply to a list in another class. You don't want to copy-paste and
violate DRY. So you might try `ul li`, but then it hits every unordered
list. So, you can abstract and apply some class to both lists. Fine, but
now you have to keep in mind default settings for other lists.

### Resets and normalization

You should try to have sensible defaults and setting for everything.
Consider using a reset or normalization CSS file (presumably before you add
CSS of your own).

## Level 6

### Images: content or layout

If an image is content, they belong in your HTML. If the image is
decorative, it belongs in your CSS. That was easy enough.

### Image cropping

Don't simply set a fixed height and width for disparately sized images. It
distorts some of them. Instead, use the `overflow: hidden` property to
a crop class. But this also sucks: the cropping is random and not optimized
per image. A better way to do it is to set height or width to a fixed
number, but then the other to `auto`, depending on whether the image is
portrait or landscape layout. But if you have a mixture of sizes, this is
going to break one or the other. So the best solution is to resize all your
images to a square which is less than the height and width of all images.

When setting height and width, you put the absolute height and width on the
parent element first. You also set overflow to hidden there. Then you can
use auto on the image itself to scale more proportionally. Example:

    .store li {
      height: 150px;
      width: 150px;
      overflow: hidden;
    }

    .store li img {
      height: 150px;
      width: auto;
    }

## Level 7

### Image replacement

Don't use an empty element with a background link for a logo. Instead put
the text in, and then use `text-indent: -9999;` to move the image off
screen forever.

### Sprites

If you have multi-state images, you have a few problems. First, the default
technique causes more round trips to the server to get resources. Second,
when the images swap, you get a flash effect when one isn't loaded or
cached yet.

Sprites fix this by combining multiple images into one file. Then when you
want to swap the images, you simply use the background-position property to
move as needed. For example:

    .logo {
      background: url(logo.png);
      display: block;
      height: 100px;
      width: 200px;
      text-indent: -9999px;
    }
    .logo:hove, .logo:focus {
      background-position: 0 -100px;
    }

Notice that you don't need to set the background position for the initial
logo, since the default of 0 0 is correct. (With background-position, the
first number is x-axis and the second is y-axis.) You can do much more
fancy things with multi-image, multi-state sprites as well.

### Base64 encoding

You can pipe your image directly into your code using Base64, but it isn't
supported by IE below 8. No real discussion of this option.
