# Testing in Rails

## Why?

+ Rails makes it easy to tests.
+ You can refactor with more confidence
+ Rails adds support for simulating browser requests as well, so you can test the full round trip of request and response.

## Support for tests is baked into Rails

Rails provides three separate environments for applications: production, development and testing. The testing environment has built-in database support, separate from anything else. You can simulate significant changes without fear of damaging anything real.

When you generate a model, you get a stub test file and fixtures automagically. The stub of the tests goes into test/unit/<model>\_test.rb. The fixture is created at test/fixtures/<model>.yml. The initial test file is almost entirely mocked out; the fixtures file is ready to fill with sample data. You can also use ERB inside the fixture files (which are themselves YAML or CSV - YAML is the norm).

The data from the fixture is available in a few ways. First, the fixtures are loaded as hashes. You can get at individual fixture examples by picking out their hash, using the name of the model as a method. So for example if you have a User model, with a fixture named 'foo', you can get it via `users(:foo)`. You can also get at the underlying object directly via `users(:foo).find`.

## Unit Testing

Unit testing in Rails is for models. When you generate a new model, you will automatically get a fixture and stubbed test file. The test class subclasses `ActiveSupport::TestCase`, and test methods should start with `test_`. Sort of like shoulda or Rspec, Rails provides a little magic behind the scenes whereby you can write this:

    test "the foo" do
      # test code
    end

And that method is automagically turned into `test_the_foo`. Before doing tests the first time, you need to migrate your database and load the schema into your test db with `rake db:migrate && rake db:test:load`. Later, you should run `rake db:test:prepare` as  you go to check for pending migrations. If you run tests via `rake`, then you get this for free (though `rake` makes tests start more slowly overall).

As a guideline of *what* to test, the Rails Guide suggests one test (at least) for every validation and each method in your models.

## Available assertions

All of `test/unit`'s default assertions are available, and Rails adds some of its very own:

+ Default
  + `assert(boolean, [msg])`
  + `assert_equal(expected, actual, [msg])`
  + `assert_not_equal( expected, actual, [msg])`
  + `assert_same(expected, actual, [msg])`
  + `assert_not_same(expected, actual, [msg])`
  + `assert_nil(obj, [msg])`
  + `assert_not_nil(obj, [msg])`
  + `assert_match(regexp, string, [msg])`
  + `assert_no_match(regexp, string, [msg])`
  + `assert_in_delta(expected, actual, delta, [msg])`
  + `assert_throws(symbol, [msg]) { block }`
  + `assert_raise(exception1, exception2, ...) { block }`
  + `assert_nothing_raised(exception1, exception2, ...) { block }`
  + `assert_instance_of(class, obj, [msg])`
  + `assert_kind_of(class, obj, [msg])`
  + `assert_respond_to(obj, symbol, [msg])`
  + `assert_operator(obj1, operator, obj2, [msg])`
  + `assert_send(array, [msg])` `array[0] is an obj, array[1] is a method and array[1..n] are params`
+ Additional assertions from Rails
  + `assert_valid(record)`
  + `assert_difference(expressions, difference = 1, [msg]) { block }`
  + `assert_no_difference(expressions, [msg]) { block }`
  + `assert_recognizes(expected_options, path, extras = {}, [msg])`
  + `assert_generates(expected_path, options, defaults = {}, extras = {}, [msg])`
  + `assert_response(type, [msg])`
  + `assert_redirected_to(options = {}, [msg])`
  + `assert_template(expected = nil, [msg])`

## Functional Tests for Controllers

In addition to testing models, you should test controllers as well. Tests that check the functionality of one controller are known as functional tests. (Tests for multiple controllers are integration tests.) Within functional tests, you should test the following:

+ Were web requests successful?
+ Do redirects work as expected?
+ Is authentication working?
+ Are the right objects provided to templates?
+ Do the right messages show up in the flash?

An example of such testing might look like this:

    test 'GET index' do
      get :index
      assert_response :success
      assert_not_nil assigns(:posts)
    end

The `get` method is one of five HTTP verbs that you can use to check requests:

+ `get`
+ `post`
+ `put`
+ `head`
+ `delete`

Along with the request, you can pass four parameters:

+ The action of the controller you're requesting, as a string or symbol
+ An optional hash of request parameters to pass along with the request to the action
+ An optional hash of session variables to pass with the request
+ An optional hash of flash values

Ex: `get(:show, {'id' => '12'}, {'user_id' => 5}, {'message' => 'boom!'})`

After the request has been made, you will have four hashes ready to check:

+ `assigns` - Anything stored as instance variables for views
+ `cookies` - Any cookies that are set
+ `flash` - Anything in the flash
+ `session` - Anything in a session variable

You can access all of these by string or symbol *except* `assigns`, which you can only do with a string or a workaround symbol lookup:

    assigns['something'] # works
    assigns(:something)  # works
    assigns[:someting]   # does not work

After the request, you also get access to three instance variables

+ `@controller` - The controller that processes the request
+ `@request` - The request itself
+ `@response` - The response

Another, larger functional test example:

    test 'should create post' do
      assert_difference('Post.count') do
        post :create, :post => { :title => 'Test post', :body => 'First post' }
      end
      assert_redirected_to post_path(assigns(:post))
      assert_equal 'Post was successfully created', flash[:notice]
    end

## Testing views

You can also test the content of the responses you get (i.e., test your views). Rails provides another special assertion for this: `assert_select`. This assertion comes in two forms:

+ `assert_select(selector, [equality], [msg])`
+ `assert_select(element, selector, [equality], [msg])`

The first form might look like this: `assert_select 'title', 'Welcome to Our Site'`

The `equality` portion of either form can be a string, a boolean, a regular expression, an integer or a range. So you might also do `assert_select 'li', 5`.

## Integration tests

Integration tests check the interaction among controllers. This is a way of testing larger flow within the app. Rails won't automatically create integration tests, but there is a generator: `rails generate integration_test user_flows`, for example. Within an integration test, you must manually call all fixtures. On the other hand, integration tests provide additional helper assertions:

+ `https?`
+ `https!`
+ `host!`
+ `redirect?`
+ `follow_redirect!`
+ `request_via_redirect(http_method, path, [params], [headers])`
+ `post_via_redirect(path, [params], [headers])`
+ `get_via_redirect(path, [params], [headers])`
+ `put_via_redirect(path, [params], [headers])`
+ `delete_via_redirect(path, [params], [headers])`
+ `open_session`

An example chunk of integration testing:

    require 'test_helper'

    class UserFlowsTest < ActionController::IntegrationTest
      fixtures :users

      test "login and browse site" do
        # login via https
        https!
        get "/login"
        assert_response :success

        post_via_redirect "/login", :username => users(:avs).username,
                                    :password => users(:avs).password
        assert_equal '/welcome', path
        assert_equal 'Welcome avs!', flash[:notice]

        https!(false)
        get "/posts/all"
        assert_response :success
        assert assigns(:products)
      end
    end
