class PolynomialManager

  def initialize(formula_parser)
    @formula_parser = formula_parser
  end

  def equality(p, q)
    p === q
  end

  def meaning(p, x)
    result = p.calculate x

    while p.next do
      p = p.next
      result += p.calculate x
    end

    result
  end

  def add(q,r)
    result = nil
    last_result_item = nil
    q_dump = q.dup
    r_dump = r.dup
    until q_dump.nil? && r_dump.nil?

      if q_dump.nil? || r_dump.nil?
        compare = q_dump.nil? <=> r_dump.nil?
      else
        compare = q_dump.power <=> r_dump.power
      end

      case compare
        when -1
          power, multiplier = r_dump.power, r_dump.multiplier
          r_dump = r_dump.next
        when 0
          power, multiplier = r_dump.power, r_dump.multiplier + q_dump.multiplier
          q_dump = q_dump.next
          r_dump = r_dump.next
        else #1
          power, multiplier = q_dump.power, q_dump.multiplier
          q_dump = q_dump.next
      end

      if multiplier.zero?
        next
      end

      if result.nil?
        result = last_result_item = PolynomialListItem.new(multiplier, power)
      else
        last_result_item = last_result_item.add_next(multiplier, power)
      end

    end

    result
  end

  def formula_to_list(str, variable = 'x')
    first_item = nil

    @formula_parser.parse(str, variable).inject(first_item) do |last_polymer_item, item|
      polymer_item = PolynomialListItem.new(item[:multiplier], item[:power])
      if last_polymer_item.nil?
        first_item = polymer_item
      else
        last_polymer_item.next = polymer_item
      end
    end

    first_item
  end

end