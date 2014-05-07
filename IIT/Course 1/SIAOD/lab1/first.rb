require './lib/formula_parser'
require './lib/list_item_simple'
require './lib/polynomial_list_item'
require './lib/polynomial_manager'

manager = PolynomialManager.new(FormulaParser.new)

x = 10

x_meaning = 3*10**4-5*10**2+10-5


formula_one = '3x^4-5x^2+x-5'
formula_two = '3x^4-5x^2+x-5'
formula_three = '-8x^7-5x^4+x+6'

list_item_one = manager.formula_to_list formula_one
list_item_two = manager.formula_to_list formula_two
list_item_three = manager.formula_to_list formula_three

puts

puts "Equality test: "
puts "#{list_item_one.full_string} should be equal #{list_item_two.full_string}, got:"  << manager.equality(list_item_one, list_item_two).to_s
puts "#{list_item_one.full_string} should not be equal #{list_item_three.full_string}, got:"  << manager.equality(list_item_one, list_item_three).to_s

puts

puts "Meaning test:"
puts "X is #{x}"
puts "#{list_item_one.full_string} should be equal #{x_meaning}, got:"  << manager.meaning(list_item_one, x).to_s

puts

puts "Add test: "
puts "#{list_item_one.full_string} plus #{list_item_three.full_string} is: "  << manager.add(list_item_one, list_item_three).full_string

puts




