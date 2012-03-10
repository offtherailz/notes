# Peepcode Meet Rails 3 - Part 1

## Short Introduction

Rails is a framework that helps to eliminate boilerplate, allowing you to
focus more on the custom parts of your application. It handles the
database, routing and rendering for you.

Rails is an MVC framework - model, view, controller. The data lives in the
model, and the view presents it. The controller sits between the model and
the view and helps the two to communicate.

## Why Rails?

+ Ideology - it's opinionated
+ Organization - Rails eliminates thousands of decisions by convention over
  configuration
+ Style - Rails has made many excellent choices that make for well-written
  applications.
+ Tools - Rails has a ton of supporting tools to jumpstart things.
+ Community - A great and large community supports Rails

## Rails 3.0

Almost two years in development, Rails 3.0 is a huge step forward. It has
a new ORM engine, updated controller internals and a lot of inspiration
from Merb.

Rails 3 has increased the learning curve associated with Rails. There are
many new tools (e.g. Bundler) and new ways of doing things (REST - in
routes?).

## Default Files and Layout

The 'app' folder contains the majority of application code. Each element in
MVC has a sub-folder, as well as 'helpers' and 'mailers'.

The 'config' folder has the essential 'database.yml' file. In addition,
'routes.rb' lives in 'config'.

Rails has three default environments: development, production and testing.
Each of these environments has a settings file in 'config/environments'.

Some various useful directories or files follow. 'db/seeds.rb' is useful
for setting seed data. 'Gemfile' is used by bundler. 'lib/tasks' is a good
place to put helpful rake tasks. The 'public' folder contains stylesheets,
static HTML pages and javascript files.

## Generators

Rails ships with a ton of generators to help simplify starting various
tasks. Note that the generators are one-time, passive generators. Also, the
popular scaffold generators are mostly not useful for more experienced
developers, though they can make things very fast.

## Views

THe view code lives in 'app/views/sub-directory' where 'sub-directory' is
named for the particular model/controller.

Within ERB `<%= %>` dynamically injects content into the rendered template.
For control-flow or logic code, use `<% %>`.

Inside 'views/layouts' lives 'application.html.erb'. This file provides the
base HTML for all pages. If you want a base layout for a specific
controller, simply place it in 'views/layouts' and name it for the
controller.

For all views, if you visit '/view/any-value', then you are asking to 'show'
the record for the 'any-value' id. Rails will hit 'view/show.html.erb'
rather than 'index.html.erb'.

## Controllers

To intercept an action in a controller, you write a method in the
appropriate controller file. Instance variables are available from within
views.

What controllers do:

+ Handle actions: implement index, show, etc.
+ Assign variables: prepare data for views or serialization
+ Before and after filters: for every action or just some
+ Respond with object: new in Rails 3

Various notes:

+ `redirect_to(URL, options)`
+ `before_filter` or `after_filter` can take an `:only` limitation:
    before_filter :authenticate, :only => [:show, :destroy]
+ It's common to see `whatever_url` in controllers and `whatever_path` in
  views. Keep that convention in mind.

## Flash Messages

When you use `redirect_to` in your controllers, you can pass a flash
message as well.

    redirect_to URL, :notice => 'Message'

Then in your view, you have a div ready to show such messages. One way to
handle this is to put this div in 'layouts/application.html.erb' rather
than in the layout for a specific action.

## Plural versus singular in Rails

Rails uses the plural versus the singular in various ways to distinguish
actions or links. We distinguish between `people_path` and `person_path(#)`
for example.

For controllers and URLs, the plural refers to collection actions that work
on a group of records. The singular refers to a member action that works on
only one record. Some examples of each:

Collection:

+ index, new, create
+ `people_url`
+ '/people'

Member:

+ show, update, destroy
+ `person_url(#)`
+ '/people/id'

## Models

The model is where your data and your business logic lives. You use the
singular to create new models:

    rails generate model Person

What you write is a singular name, and almost all of your code in the model
will work on this singular. But the name of the database itself will be
plural. Rails is smart about handling common irregular nouns in English.

You can also create database fields when you generate a new model. Common
field types include the following: `:primary_key`, `:string`, `:text`,
`:integer`, `:float`, `:decimal`, `:datetime`, `:timestamp`, `:date`,
`:binary`, `:boolean`. The field names that you create are up to you. Rails
will automatically create an `:id` field as well as a `:created_at` and
`:updated_at` field.

When you generate a model, Rails creates a migration. Inside the migration
you will find code that will run when you run the migration `self.up` or
roll it back `self.down`.

One nice thing about migrations is that you can use them at any time to
update your database structure. Simply generate a migration, add (or
remove?) columns as needed and then run the migration.

Rails puts validations in Ruby code rather than in database code by
default. However, you can also add data purity to your migrations in order
to make sure that your database also maintains integrity. Here are some
options you can pass to enforce various things about a data field:

+ `:limit => #`
+ `:default => 'Whatever'`
+ `:null => false`
+ `:precision => 5, :scale => 2` Significant digits and digits after
  decimal point. Only on decimal columns, usually given together.

Rails also provides `rails dbconsole` instead of the more general `rails
console` to check database-specific information. You can also check
'db/seeds.rb'

You can find records in various ways:

+ `Person.find(id#)`
+ `Person.where(:first_name => 'Value')`
+ `Person.all`

Rails provides many helper methods to do more advanced queries: `where`,
`having`, `select`, `group`, `order`, `limit`, `offset`, `joins`, `includes`,
`lock`, `readonly`, `from`, `first`, `last`, `all` and `find_each`.

A best practice tip: Write _all_ your query code in your models and none in
controllers or views. Use `scope`, `default_scope` and custom class methods
to build queries that can be called in one line from any controller than
needs them. See ActiveRecord::NamedScope::ClassMethods.

Queries - except for `find` and `all` - are lazy. They won't execute until
they must.

Validations should be in the model code - even if you put them into the
database.

    validates :field, :options

Options include `:presence`, `:length` (a number or a hash with `:minimum`,
`maximum` or both), `:acceptance`, `:confirmation`, `:exclusion` or
`:inclusion` (with an array), `:format` (with a regular expression),
`:numericality` and `:uniqueness`.

The model allows you to create custom methods (say to present `name` as
opposed to combining first and last name fields directly from the database
in your controller or view). In addition, Rails provides a slew of callback
methods for the model (as with the controller).

+ `before_validation`
+ `after_validation`
+ `before_save`
+ `before_create`
+ `after_create`
+ `after_save`
+ `after_commit`
+ `after_rollback`
+ `before_destroy`

In a callback method, you can use `self` in simple shortcuts:

    before_save :cleanup

    private

    def cleanup
      self[:first_name] = self[:first_name].capitalize
    end

To keep query code out of your controllers, you can use scopes.

    scope :query_name, query_code_or_lambda
    scope :siths, where(:first_name = 'Darth')
    scope :child_of_vader, where('first_name IN (?)', ['Luke', 'Leia'])
    scope :rebels, where(:affiliation => 'rebel')
    scope :dozen_rebels, rebels.limit(12)
    scope :n_rebels, lambda { |n| rebels.limit(n) }

## Partials

Shared partials normally live in 'app/views/shared'. The name of partials,
as files, must begin with `_`, but when you refer to a partial in a view,
you don't use the `_`. He suggests Jammit for including Javascript asssets,
rather than the Rails built-in `:defaults` include.

Stopped at video2-24:23
