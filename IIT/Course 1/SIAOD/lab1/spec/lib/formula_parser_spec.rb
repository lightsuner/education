require 'spec_helper'
require 'formula_parser'

describe FormulaParser, "#parse_fragment" do

  it "returns hash" do
    parser = FormulaParser.new

    variable = 'x'

    parser.parse_fragment('-8x^7', variable).should eq({
      multiplier: -8,
      power: 7
    })

    parser.parse_fragment('-x^7', variable).should eq({
      multiplier: -1,
      power: 7
    })

    parser.parse_fragment('7', variable).should eq({
      multiplier: 7,
      power: 0
    })

    parser.parse_fragment('x', variable).should eq({
      multiplier: 1,
      power: 1
    })

  end
end

describe FormulaParser, "#parse" do

  it "returns array of hashes" do
    parser = FormulaParser.new

    formula = "-8x^7-5x^4+x+6"

    result = parser.parse formula

    result.should eq([
      {
        multiplier: -8,
        power: 7
      },
      {
        multiplier: -5,
        power: 4
      },
      {
        multiplier: 1,
        power: 1
      },
      {
        multiplier: 6,
        power: 0
      }
    ])
  end
end