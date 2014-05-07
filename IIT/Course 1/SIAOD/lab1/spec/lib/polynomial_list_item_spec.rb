require 'spec_helper'
require 'list_item_simple'
require 'polynomial_list_item'

describe PolynomialListItem, "#equality" do

  it "returns true" do


    list_item1 = PolynomialListItem.new(3, 4)
    list_item1.add_next(5, 2).add_next(5, 2).add_next(-5, 0)

    list_item2 = PolynomialListItem.new(3, 4)
    list_item2.add_next(5, 2).add_next(5, 2).add_next(-5, 0)

    list_item3 = PolynomialListItem.new(3, 4)
    list_item3.add_next(5, 2).add_next(5, 2).add_next(-5, 0).add_next(-1, 1)

    list_item1.should === list_item2
    list_item1.should_not === list_item3

  end
end

describe PolynomialListItem, "#calculation" do

  it "returns true" do


    list_item1 = PolynomialListItem.new(3, 4)

    x = 3

    expected_result = 243

    list_item1.calculate(x).should == expected_result

  end
end