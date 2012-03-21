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
