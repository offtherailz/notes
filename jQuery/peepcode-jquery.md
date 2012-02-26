# Notes on Peepcode's jQuery screencast

GG was a sceptic when he started this screencast. Now he's a convert.

## Uniformity of methods

Pretty much all built-in jQuery methods work on DOM selectors without any
consideration for whether the selector finds one or one hundred elements.
They work on arrays or single elements.

    // Doesn't matter if the selector finds one link, twenty or a thousand
    $('body #container a').fadeOut()

## Lots of plugins and lots of support for plugins

jQuery is composable. The core itself is a relatively small item, and you
can add, mix and match more functionality via plugins.

## Things to do with jQuery

+ Show or hide elements
+ Change CSS to modify presentation
+ Dynamically create elements
+ Change text or attributes of an element
+ Store data
+ Trigger or respond to events

## Setup

We're going to make a pomodoro technique website. Twenty-five minutes, then
a five minute break. Do that four times, then do a 15 minute break. Start
by getting a copy of jQuery from their site. During development use the
readable version. Later, you can use a minified version from a CDN. In
addition, he's going to use the jQuery UI. He warns that the UI plugin are
not quite as fully compatible across browsers. He also recommends Firebug
or Safari's developer tools.

Two kinds of jQuery site: unobtrusive or 100% Javascript. The first works
without Javascript, is progressively enhanced, accessible and server based.
The 100% Javascript application, however, is more application than website.
As such, it doesn't degrade nicely since it's all or nothing.

He recommends putting Javascript requires at the bottom of your body, with
your specific application code at the end. That only makes sense: first
require the base libraries, then require the code that builds on top of
them.

## Methods and the almighty $

The base function in jQuery is `jQuery` or its alias `$`. If called alone,
it returns the entire HTML document.

But it does so much more:

+ $('selector') - returns the element or elements with that selector
+ $('selector', doc) - search another document by selector
+ $(element) - wrap existing element with jQuery methods
+ $('<a href="/">Home Page</a>') - create an element
+ $(callback) - execute function when DOM is ready

A simple example: change the page's title.

    $('title').text()         // getter - return value of the text node
    $('title').text('value')  // setter - change the node's value

The documentation for jQuery's core is very good. Read it. Also read
jQuery's selectors API documentation.

## Tasks

A simple jQuery start:

    jQuery(function () {

    // everything else happens here
        $('#add').click(function (e) {
          var taskItem = $('#tasks ul li: first').clone();
          taskItem.find('input[type="text"]').val("");
          $('#taks ul').append(taskItem);
          taskItem.find('input[type="text"]:first').focus();
          return false;
        });

        // Set up two more links and focus on the top one
        $('#add').click().click();
        $('#tasks ul').sortable({handle:".handle"}).disableSelection();
        $('input[type="text"]:first').focus();

    });

## A plugin

First, toggle. Woah.

    $('.completion a').toggle(
      function(e) { $(this).compltedX(); },
      function(e) { $(this).compltedApostrophe(); },
      function(e) { $(this).completedDash(); },
      function(e) { $(this).completedEmpty(); }
    );

But `toggle` only works for elements that exist initally in the DOM. This is
true for `click` or any derivative of `bind` as well. So for this you can
use `live`.

    $('.completion a').live("click", function(e) {
      $(this).toggleTaskState();
      return false;
    });

The function `toggleTaskState` doesn't exist yet. He's going to make
a plugin for it. He does this with `jQuery.extend`. Well, actually he uses
`jQuery.fn.extend`. The difference is that the first method adds functions
to jQuery which you call in general - not on a particular element. The
second method adds functions that work on jQuery objects.
