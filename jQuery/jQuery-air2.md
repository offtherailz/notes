# Notes on jQuery Air Captain's Log

## Level 1 - Events

### HTML5 data attributes

The HTML `data` tag can be used to store and label data:

    <a href="#2012-0927" data-flights="6"Sep 27</a>

    $('#tabs ul li:first a').text();  // Sep 27
    $('#tabs ul li:first a').attr('href');  // #2012-09-27
    $('#tabs ul li:first a').data('flights'); // 6

### Namespacing jQuery's `$`

You can call jQuery like this if you want to make sure you keep `$`
specific and local to jQuery. (This way you won't interfere with Prototype
or whatever else.)

    jQuery(function ($) {
      // $ is ready for use here
    })

### The `eq` selector

    $('#tabls li:eq(2) a').click();

This pseudo-selector allows you to pick a specific item from a group. The
indexing is zero based, so `eq(2)` will select the third item.

### Using `bind` to collect a number of events on one element

We now have three events all for one element:

    function showNumberOfFlights(e) {
      var num_flights = $(this).data('flights');
      $(this).append("<span class='tooltip'>" + num_flights
                                              + " flights</span>");
    }

    function hideNumberOfFlights(e) {
      $('#tabs span.tooltip').remove();
    }

    $('#tabs li a').click(changeTab);
    $('#tabs li a').mouseenter(showNumberOfFlights);
    $('#tabs li a').mouseleave(hideNumberOfFlights);

One way to refactor that is `bind`:

    $('#tabs li a').bind({
      click: changeTab,
      mouseeneter: showNumberOfFlights,
      mouseleave: hideNumberOfFlights
    });

### Using `unbind`

Once we are on an active tab, we don't want to allow repeated clicks on
that same tab to send AJAX calls to the server. We can fix this by
unbinding the `click` event from the active tab (temporarily):

    function changeTab(e) {
      e.preventDefault();
      $('#tabs li a.active').removeClass('active').click(changeTab);
      $(this).addClass('active').unbind('click', changeTab);
      // ...
    }

Adding `.click(changeTab)` is equivalent to `.bind('click', changeTab)`.
That rebinds the `click` event to a tab which was just switched from active
to non-active. On the other hand, we directly remove the `click` event from
the tab that has just become active in the next line, using `unbind`.

### Namespacing events

You can place event handlers under namespaces by simply adding a property
to the event. You can do this one at a time or all at once:

    .bind('click.flightSchedule', changeTab);
    .unbind('click.flightSchedule');

    $('#tabs li a').bind({
      'click.flightSchedule': changeTab,
      'mouseeneter.flightSchedule': showNumberOfFlights,
      'mouseleave.flightSchedule': hideNumberOfFlights
    });

This allows you to rapidly remove all those events at once:

    $('#tabs li a').unbind('.flightSchedule');

### Bind versus live

So far we've been using `bind` to connect handlers to events. But `bind`
only works on items that are loaded into the DOM via HTML. If we use AJAX
to load parts of the page, we can't use `bind` on the elements inside that
page fragment. Instead, we need to use `live`.

    $('#flights a').live('click', selectFlight);

### Live versus delegate

But `live` itself is not the best way to do this. Instead, `delegate` is
better.

    $('#flights a').live('click', selectFlight);
    // is the same as
    $(document).delegate('#flights a', 'click', selectFlight);

Rather than search the whole document every time we get a click, we can
limit the part of the page explicitly, using `delegate` directly.

    $('#tabs div').delegate('#flights a', 'click', selectFlight);

Delegate has two main benefits:

+ It can be method chained (`live` cannot?)
+ It's more performant

## Level 2 - AJAX

### Basic AJAX

    $.ajax('/flights', {
      data: { date: activeDiv },
      cache: false,
      timeout: 8000, 
      beforeSend: function (result) { 
        $('#error').hide();
        $('#loading').show();
      },
      success: function (result) { 
        $(activeDiv).html(result);
        $(activeDiv).show();
      },
      complete: function () { 
        $('#loading').hide();
      },
      error: function (result) { 
        $('#error').show();
      }
    });

### Abort incomplete AJAX requests

+ Create a state variable and set it to null
+ When the button is hit, check the variable.
  + If there's something in it, abort that something.
  + Adjust the error callback not to show an error if the call was
    aborted.
+ Assign the AJAX call's result to the state variable when you call it.

### Fetching Data using JSON

    $.ajax('/flights/' + flight, {
      data: { 'class': flightClass },
      dataType: 'json',
      success: showTotal
    });

    function showTotal(json) {
      $('#price').text(json.price);
      $('#price').text(json.fees);
      $('#price').text(json.total);
      $('#confirm').slideDown();
    }

### JSONP

JSONP is fetching JSON data from a different domain. Simply switch the
`dataType` property to use 'jsonp'.

### AJAXifying a login form

    function login(event) {
      event.preventDefault();
      $('#login h4').slideUp();

      var form = $(this).serialize();

      $.ajax('/login', { 
        data: form,
        dataType: 'script',
        type: 'post'
      });
    }
