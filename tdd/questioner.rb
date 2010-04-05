require 'minitest/unit'
require 'minitest/spec'

MiniTest::Unit.autorun

class Questioner
	def initialize(inp=STDIN, out=STDOUT)
		@input = inp
		@output = out
	end

	def ask(question)
		@output.puts question
		response = @input.gets.chomp
		case(response)
		when /^y(es)?$/i
			true
		when /^no?$/i
			false
		else
			@output.puts "I don't understand your response."
			ask(question)
		end
	end

	def inquire_about_happiness
		ask("Are you happy?") ? "Good I'm glad." : "That's too bad."
	end
end

class QuestionerTest < MiniTest::Unit::TestCase
	describe 'Trying to stub a method' do
		before do
			@q = Questioner.new
		end
		it 'fuck if I know yes' do
			def @q.ask(question); true; end
			@q.inquire_about_happiness.must_equal "Good I'm glad."
		end
		it 'fuck if I know no' do
			def @q.ask(question); false; end
			@q.inquire_about_happiness.must_equal "That's too bad."
		end
	end
end
