% Notes on HTML Mastery (Paul Haine), Chapter 1
% Peter Aronoff
% 2010-04-13

# Getting started

## Some key definitions and distinctions

+ element: An opening tag and its (optional) attributes, some content and (usually) a closing tag. An element can contain other elements with their tags, attributes and content.
+ tag: Starts and (usually) ends an element. The opening tag can contain attributes; the closing tag must have nothing but itself.
+ empty element, self-closing element, replaced element: One of the elements without closing tags. E.g., `<img>`, `<br>`. In XHMTL, empty elements must look like this `<br />`. The space and faux closing frontslash are required.
+ attributes: Give additional information about elements. They appear within opening tags. E.g., `<p class="example">`. One attribute can contain multiple, space-separated values. Some attributes (like class) are generic, but some can only appear with specific element types.
+ div: A div ('division') marks out a block of content.
+ span: A span is a kind of inline div. It marks out some content within a block, rather than creating a new block.
+ block-level: A block-level element begins rendering on a new line and forces the next element to start on a further new line below that. You can't place two block-level items side by side without CSS.
+ inline: An inline element does not force line breaks. Inline items run horizontally rather than vertically. You can't stack two inline elements on top of each other without CSS.
+ id attribute: An id uniquely characterizes some element.
+ class attribute: A class brings together a number of related elements.

Note that _one_ element can have both an id and a class. Also, you should avoid naming ids or classes for stylistic features. Use semantic values instead. So, an item might be `<span class="warning">` rather than `<span class="red">`.

## XHTML versus HTML

+ XHTML requires `<html>`, `<head`, and `<body` elements.
+ XHTML requires an xmlns attribute inside the `<head>` element.
+ All elements must be closed in XHTML.
+ All XHTML tags must be lowercase.
+ All attribute values must be quoted (single or double quotes are fine) in XHTML.
+ All attributes in XHTML must have values.
+ Any ampersangs in XHTML must be encoded (wherever they appear).
