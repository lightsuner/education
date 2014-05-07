require 'spec_helper'
require 'polynomial_manager'
require 'list_item_simple'
require 'polynomial_list_item'
require 'formula_parser'

describe PolynomialManager, "#formula_to_list" do

  it "returns chain of ListItems" do
    manager = PolynomialManager.new(FormulaParser.new)

    formula = '3x^4+5x^2+x-5'

    list_item = PolynomialListItem.new(3,4)
    list_item.add_next(5,2).add_next(1,1).add_next(-5,0)

    manager.formula_to_list(formula).should === list_item

  end

  it "calculate formula (Meaning)" do
    manager = PolynomialManager.new(FormulaParser.new)

    formula = '3x^4-5x^2+x-5'

    x = 6

    expected_result = 3*x**4-5*x**2+x-5

    item_list = manager.formula_to_list(formula)

    manager.meaning(item_list, x).should == expected_result

  end

  it "Polynomials should be equal" do
    manager = PolynomialManager.new(FormulaParser.new)

    formula1 = '3x^4-5x^2+x-5'
    formula2 = formula1.dump
    formula3 = '3x^4-5x^2+x-4'

    item_list1 = manager.formula_to_list(formula1)
    item_list2 = manager.formula_to_list(formula2)
    item_list3 = manager.formula_to_list(formula3)


    manager.equality(item_list1, item_list2).should == true
    manager.equality(item_list1, item_list3).should == false

  end


  it "Polynomials calculation" do
    manager = PolynomialManager.new(FormulaParser.new)

    formula1 = '-8x^7-5x^4+x+6'
    formula2 = '3x^4+5x^2+x-5'

    item_list1 = manager.formula_to_list(formula1)
    item_list2 = manager.formula_to_list(formula2)

    expected_result = '-8x^7-2x^4+5x^2+2x^1+1x^0'

    result_item = manager.add(item_list1, item_list2)

    result_item.full_string.should == expected_result

  end

end