defmodule Float80Test do
  use ExUnit.Case
  doctest Float80

  test "zero" do
    zero = Float80.zero()
    assert zero == <<0, 0, 0, 0, 0, 0, 0, 0, 0, 0>>
  end

  test "from" do
    value = Float80.from(0.0)
    zero = Float80.zero()
    assert value == zero
  end

  test "add" do
    a = Float80.from(1.0)
    b = Float80.from(2.0)
    result80 = Float80.add(a, b)
    result = Float80.to_float(result80)
    assert result == 3.0
  end

  test "subtract" do
    a = Float80.from(2.0)
    b = Float80.from(1.0)
    result80 = Float80.subtract(a, b)
    result = Float80.to_float(result80)
    assert result == 1.0
  end

  test "multiply" do
    a = Float80.from(2.0)
    b = Float80.from(3.0)
    result80 = Float80.multiply(a, b)
    result = Float80.to_float(result80)
    assert result == 6.0
  end

  test "divide" do
    a = Float80.from(6.0)
    b = Float80.from(3.0)
    result80 = Float80.divide(a, b)
    result = Float80.to_float(result80)
    assert result == 2.0
  end

  test "pi" do
    result80 = Float80.pi()
    result = Float80.to_float(result80)
    assert result == :math.pi()
  end

  test "cos" do
    a = Float80.from(0.0)
    result80 = Float80.cos(a)
    result = Float80.to_float(result80)
    assert result == :math.cos(0.0)
  end

end
