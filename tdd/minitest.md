% Notes on MiniTest
% Peter Aronoff
% 2010-02-16

# My notes on MiniTest & company

## Basic basics

You begin by `require`-ing 'minitest/unit'. To get automatic runs of all tests, you have two options. You can add this `require`: `require 'minitest/autorun'`, or you can stick this line at the top of a helper (or file): `MiniTest::Unit.autorun`.

Speaking of which, it makes sense to place all tests in a separate test directory within your code. And if you do so, it makes sense to use a simple helper.rb file to organize certain things. Mine looks like this:

	require 'minitest/autorun'
	# require 'minitest/spec' or 'minitest/mock' optionally

	$LOAD_PATH.unshift(File.dirname(__FILE__))
	$LOAD_PATH.unshift(File.join(File.dirname(__FILE__), '..', 'lib'))

	# require whatever I'm working on here, e.g. require 'updateWP/options'

	class MiniTest::Unit::TestCase
	end

	puts "Testing {name o' thing here} on Ruby #{RUBY_VERSION}"
	now = Time.new
	puts now.strftime("%Y-%m-%d %I:%M%p\n")

Each test file you have in the test directory should begin be named in the pattern test-something.rb. That way you can use a simple Rake task to find and run all tests. More on that later.

## Creating a test block

Within each test file, you first `require` the helper file. Then the real work begins.

Individual tests go into larger test cases. A test case is a group of testing methods organized into a class which subclasses `MiniTest::Unit::TestCase`. It looks a little something like this:

	class TestMyTestUp < MiniTest::Unit::TestCase
		def test_something
			assert_equal(1, Something.new(1).count)
		end
	end

Within the standard MiniTest suite, there is a good variety of pre-made tests to choose from:

+ `def flunk([ msg ])`
+ `def pass([ msg ])`
+ `def skip([ msg ], bt=caller)`

+ `assert(test, [ msg ])`
+ `assert_block([ msg ]) { block }`
+ `assert_empty(collection, [ msg ])`
+ `assert_equal(expected, actual, [ msg ])`
+ `assert_in_delta(expected, actual delta=0.001, [ msg ])`
+ `assert_in_epsilon(a, b, epsilon=0.001, [ msg ])`
+ `assert_includes(collection, obj, [ msg ])`
+ `assert_instance_of(klass, obj, [ msg ])`
+ `assert_kind_of(klass, obj, [ msg ])`
+ `assert_match(regexp, str, [ msg ])`
+ `assert_nil(obj, [ msg ])`
+ `assert_operator(o1, op, o2, [ msg ])`
+ `assert_raises(Exception) { block }`
+ `assert_respond_to(obj, method (a symbol), [ msg ])`
+ `assert_same(expected, actual [ msg ])`
+ `assert_send(send_ary, [ msg ])`
+ `assert_throws(expected_symbol, [ msg ]) { block }`

+ `refute(test, [ msg ])`
+ `refute_empty(obj, [ msg ])`
+ `refute_equal(expected, actual [ msg ])`
+ `refute_in_delta(expected, actual delta=0.001, [ msg ])`
+ `refute_in_epsilon(a, b, epsilon=0.001, [ msg ])`
+ `refute_includes(collection, obj, [ msg ])`
+ `refute_instance_of(klass, obj, [ msg ])`
+ `refute_kind_of(klass, obj, [ msg ])`
+ `refute_match(expected, actual [ msg ])`
+ `refute_nil(obj, [ msg ])`
+ `refute_operator(o1, op, o2, [ msg ])`
+ `refute_respond_to(obj, meth, [ msg ])`
+ `refute_same(expected, actual [ msg ])`


## Organizing and running tests

Once you've written a file full of tests, you can run the whole thing at once, or you can run only selected tests. To get selected tests, use the `-n` flag, like so: `ruby test_file.rb -n test_foo`. That would run only the `test_foo` test. You can also specify a regular expression as the argument to `-n`, like so: `ruby test_file.rb -n /foo/`. This is good to know, but I suspect I will generally run the whole test suite at once.

In addition to normal test methods, each test case (the class) can contain a setup and teardown method. These two methods are special. The setup method will run before _every_ individual test case, and the teardown method _after_ each test case.

Beyond tests (individual test methods) and test cases (classes which contain bundles of tests), you can also have test suites. A test suite is a file that loads up a group of related test case files. So, to borrow Dave Thomas's example, you might have a test suite for database-related tests (_Programming Ruby 1.9_, 194):

	# file ts_dbaccess.rb
	require 'test/unit'
	require 'test_connect'
	require 'test_query'
	require 'test_update'
	require 'test_delete'

You can also have a suite that requires sub-suites. All in all, you have a lot of control and a number of options for how to run tests. Again, quoting Dave Thomas (_Programming Ruby 1.9_, 193-194):

+ You can run individual tests by name.
+ You can run all the tests in a file by running that file.
+ You can group a number of files into a test suite and run them as a unit.
+ You can group test suites into other test suites.
