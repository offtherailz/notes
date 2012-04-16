# Peepcode Backbone.js Basics

## Intro

More powerful browsers lead to more powerful apps written for them.
Backbone helps to keep more complex apps more manageable, clean and
testable.

Backbone itself is less than 700 lines of code. Easy to read in an hour or
so. It has limited functionality: no UI widgets, template agnostic. You use
basic HTML and CSS.

jQuery alone is a problem. Data and presentation are mixed, and everything
requires DOM manipulation. With Backbone, user actions modify data and
views update themselves. Backbone starts with data models. The views are
connected to these, and they react to data being loaded, changed, or
deleted. The router interprets URLs and calls parts of your code. This
allows you to create single-page, but URL-aware applications.

This screencast will discuss basics: the model, view, collections and the
router. The second will discuss UI interaction, data manipulation and
object design. The last will cover networking: how to save and load data,
form interaction and alternate data stores.

## A Simple Model

The model is the most basic data structure in Backbone. Models work with
data separate from any user interface. Models don't have to store data
permanently, but they do update other objects when they are accessed or
change.

Here's his list of things models do in Backbone:

+ Store data
+ Provide get/set accessors
+ Fire events when changed
+ Optionally make REST calls to a server for persistence

To create a model, you simply extend `Backbone.Model`:

    Album = Backbone.Model.extend({});

The simplest model needs no more code than that. Models are upcased by
convention to mark them as abstract entities.

If you want the model to be available to views and for testing, assign it
to the global `window` object:

    window.Album = Backbone.Model.extend({});

When you create an instance, it automatically has certain common model
methods:

    album = new Album({title: 'Abbey Road', artist: 'The Beatles'});
    album.get('title');
    album.set({key: value});
    album.isNew(); // Returns true or false, depending on persistence
    album.toJSON(); // Returns keys and values for serialization

## A Simple View

The view is the second fundamental Backbone class. Views render data
through templates, they react to model changes, act on user input and add
content to current document.

A Backbone view does a lot of the work you might expect the controller to
do in Ruby on Rails or another server-side framework. Views in Backbone are
smarter (more fully featured) than in Rails since they can react
immediately to client-side changes or actions.

To create a basic view, we do the following:

    window.AlbumView = Backbone.View.extend({
      initialize: function () {
        this.template = _.template($('#album-template').html());
      },
      render: function () {
        var renderedContent = this.template(this.model.toJSON());
        $(this.el).html(renderedContent);
        return this;
      }
    });

This creates a basic view for your album, gives it an initialize function
and a simple render function.

Then in the JavaScript console:

    album = new Album({title: 'Abbey Road', artist: 'The Beatles',
      tracks: [{title: 'Track A'}]});
    albumView = new AlbumView({model: album});
    $('#container').append(albumView.render().el);

This simply gives you a small test case to see data in the browser.

## Data Binding

Backbone views come with many defaults, but you can override them. By
default, the view item will be a `div`, but you can choose something else.

    window.AlbumView = Backbone.View.extend({
      tagName: 'li',
      className: 'album',
      initialize: function () {
        this.template = _.template($('#album-template').html());
      },
      render: function () {
        var renderedContent = this.template(this.model.toJSON());
        $(this.el).html(renderedContent);
        return this;
      }
    });

In this case, we've overriden the `tagName` and added a default `class` as
well.

A big part of how Backbone works is through change events. When you call
`set` on a model, two events are triggered. Views can re-render themselves
based on these events.

To get these change events, you need to do a few things. First, observe.
The view asks the relevant model to notify it when a change event happens.
It registers a callback method. Second, react. The view's callback is
notified when the model's attributes are changed.

To make sure that methods are bound to the proper object for callback
functions, you need to bind them. In `initialize` for the view, you will
add something like this:

    _.bindAll(this, 'render'); // Add all methods you want to bind here

You also need to register what changes you want to track. In this case, we
can track all changes rather bluntly, but you can also do this at a more
specific level (looking for specific changes or only rendering part of the
page in response):

    this.model.bind('change', this.render);

## Summary

Models store data, which can be persistent or temporary. Views render model
data, using templates or directly. Models trigger change events. These are
handled by the framework when you call `set`. Views watch for changes and
re-render. The UI is updated immediately. (There is no round trip to the
server.)

## Jasmine

Jasmine is a BDD test framework for JavaScript. You set it up by having
a runner in an HTML file. That file should require all necessary
third-party libraries, plus your custom code. Then you have a small script
function that invokes Jasmine itself:

    <script type="text/javascript">
      jasmine.getEnv().addReporter(new jasmine.TrivialReporter());
      jasmine.getEnv().execute();
    </script>

Now you can run your tests simply by opening that HTML file in a browser.

## Collections

Collections manage groups of models. They fetch model data, add to the
existing set, remove from the set and (allow for? create? implement?)
custom query code (?). You should expect to need a collection for each
model you create.

You create a collection by extending `Backbone.Collection`. You must
specify what model this collection manages. Backbone doesn't do any
introspection or guessing based on names.

    window.Albums = Backbone.Collection.extend({
      model: Album,
      url: '/albums'
    });

You can also specify the URL where your app will expect to connect with
this collection. A reasonable default is `url: '/albums'`. That is, use the
plural of the model name, just as for the collection itself. Then you can
use '/things' for the index/show page and '/thing/123' for a specific
look-up, just as in Rails.

If you're using Underscore with Backbone, then all the Underscore helper
methods are available to use on the collection object. Collections also
fire events when things are added, removed or reset. This allows them to
play with views as well.

## Collections and Views

Views in Backbone -- or client-side apps in general -- are different from
those in server-side frameworks like Rails. Instead of building up a final,
single view from multiple pieces and then delivering it to the client,
Backbone views can have other views inside them. Individual subviews can
update their content at any time without touching the others.
