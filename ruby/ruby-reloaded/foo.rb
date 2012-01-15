require 'ripper'
require 'ap'

ap Ripper.sexp("puts {}.class.name")
