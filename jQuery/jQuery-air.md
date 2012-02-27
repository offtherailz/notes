# Notes on jQuery Air First Flight

## Level 3: CSS

### The css function

jQuery provides a `.css` function for all jQuery objects:

    $('p').css('font-size');  // returns value of the font-size value
    $('p').css('font-size', '24px')  // sets value
    var original = parseInt($('p').css('font-size'));
    $('p').css('font-size', original + 8 + 'px'); // a relative update

    $('p').css('font-size', '24px').css('line-height', '32px'); // ugh
    $('p').({'font-size': '24px', 'line-height': '32px'});  // better

### But what about separation of concerns?

Instead of directly manipulating CSS via the `css` function, you should
change class and id attributes in the HTML. That way, the CSS stays in CSS
files, and separation of concerns is maintained.


    $('p:first').addClass('bigger');  // 'bigger' is handled in CSS
    $('p:first').removeClass('bigger'); // remove a specific class
    $('p:first').removeClass(); // remove ALL classes
    $('p:first').toggleClass('bigger'); // add or remove as appropriate

### Shh, we're hiding!

jQuery has built-in support for hiding elements.

    $('p:first').hide();  // set display: none
    $('p:first').show();  // unset display:none
    $('p:first').toggle();  // set or unset display:none as needed

### Timing is everything

We can't execute these sorts of DOM updates before we have a complete DOM.
So we need to use some kind of `$(document).ready()` function.

## Level 4: Manipulating Content

### Querying content

    $('p#time span.label').text();  // query text in that element
    $('p#time span.label').text('Departs At:'); // update text there

You can't pass HTML directly into the text function. Instead, you use the
`html` function rather than `text`.

    $('p#time').html(); // query HTML
    $('p#time').html('<b>Departs At</b>: 8:43AM');  // updates the HTML

### Prepending text

    $('span.label').prepend('Departure ');

### Appending text

    $('p#time').append(' from the gate');

### Creating HTML siblings

    $('p#time').before('<h3>Departure Details</h3>');
    $('h1').after('<h3>Departure Details</h3>');

### Removing nodes from the DOM

    $('span.label').remove();

### Moving elements within the DOM

+ Remove an item; store it in a variable
+ Find where to put it; use `before` or `after`

## Level 5: Events and Interaction

### Functions and events

Since events happen at any time, not when the Javascript is read, we need
to package up our desired behaviors as functions. These functions are
callbacks, and it's a good place to use anonymous functions since we won't
ever want to call these functions manually. (We let the event handler
invoke the function when it's appropriate.)

### Click handlers

jQuery makes it easy to write click handlers:

    $(document).ready(function (){
        $('p').click(function () {
          alert('Got it!');
        })
    })

### Click to hide

You need `this` in order to do certain things, like click to hide:

    $(document).ready(function (){
        $('p').click(function () {
          $(this).hide();
        });
    });

### Hover

When handling hover events, jQuery's `hover` function accepts *two*
functions. The first is triggered when the hover event begins. The second
triggers when the user moves his or her mouse away. This way, things you do
when a user hovers are *undone* when he or she moves elsewhere.

    $(document).ready(function (){
        $('p').hover(
          function () {$(this).addClass('highlight');},
          function () {$(this).removeClass('highlight');}
        );
    });

But we can simplify this. Actually, jQuery will respond in a DWIM fashion
if you give a `hover` function only one callback. It will invoke the
callback once when the hover starts and again when it ends. You can use
this to pass a `toggle` event as a callback.

    $(document).ready(function (){
        $('p').hover(function () {
          $(this).toggleClass('highlight');
        });
    });

### Keyboard events

You can respond to three kinds of key events:

+ `keydown` fires once when a key is depressed
+ `keypress` fires one or more time when a key is held down
+ `keyup` fires once when the key is released

    $(document).ready(function (){
        $('body').keypress(function () {
          alert('Fantastic!');
        });
    });

This is too broad. We need to be able to consider the event in a little
more detail.

    $(document).ready(function (){
        $('body').keypress(function (event) {
          if (event.which === 102) {
            alert('Fantastic!');
          }
        });
    });

You can use `event.preventDefault` to stop the default action (say
following a link). You can also use `event.stopPropagation` to prevent
event bubbling.

### Fake Ajax

You can do simple animations directly in jQuery.

    $('p#time').hide('slow'); // do an animated hide
                              // the extra param can be 'slow', 'fast' or
                              // an integer
                              // also .fadeOut, .fadeIn, .fadeToggle

### True Ajax

Real Ajax requires sending or receiving content via XMLHttpRequest. You can
use the `load` function to get HTML from the server.
