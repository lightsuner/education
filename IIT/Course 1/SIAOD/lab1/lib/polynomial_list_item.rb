class PolynomialListItem < ListItemSimple
  attr_reader :multiplier, :power

  def initialize(multiplier, power)
    @multiplier = multiplier
    @power = power
  end

  def to_s
    @multiplier.to_s + 'x^' + @power.to_s
  end

  def ==(other_object)
    (@multiplier == other_object.multiplier) && (@power == other_object.power)
  end

  def ===(other_object)
    this_object = self

    loop do
      break false if (this_object != other_object)
      break true if (this_object.next.nil? && other_object.next.nil?)
      break false if (this_object.next.nil? || other_object.next.nil?)

      this_object = this_object.next
      other_object = other_object.next
    end
  end

  def add_next(multiplier, power)
    self.next = self.class.new(multiplier, power)
  end

  def calculate(x)
    @multiplier*(x**@power)
  end

  def full_string
    result = to_s

    o = self.dup

    while o.next do
      o = o.next
      sign = '+' if o.multiplier >= 0
      result << "#{sign}" << o.to_s
    end

    result
  end

end