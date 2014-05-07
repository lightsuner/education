class FormulaParser

  def parse(formula_string, variable = 'x')
    result = []
    formula_string.scan(/(?:[-]?\d*x?(?:\^\d)?)/).reject { |c| c.empty? }.each do |fragment|
      result << parse_fragment(fragment, variable)
    end
    result
  end

  def parse_fragment(fragment, variable)
    if fragment.include? variable
      multiplier, power = fragment.split(variable)
      if power and power.include? '^'
        power = power.gsub(/[^-\d]/, '').to_i
      else
        power = 1
      end
      unless multiplier
        multiplier = '1'
      end
      if multiplier == '-'
        multiplier = '-1'
      end
    else
      multiplier = fragment
      power = 0
    end

    multiplier = multiplier.gsub(/[^-\d]/, '').to_i

    {
      multiplier: multiplier,
      power: power,
    }
  end

end