defmodule Float80 do
  @moduledoc """
  Documentation for `Float80`.

  The Float80 module allows 80 bit precision floating point numbers to be
  represented as 10 byte binary values (`<<_::80>>`). NIFs are used to convert Elixir integers 
  and floats to and from Float80 and also perform math functions returning the result
  as a Float80.

  Note that since Elixir doesn't support Float80 numbers you will need to convert
  Float80 numbers back to float before passing them to other Elixir functions.

  The standard arithmetic operators are not supported (`+`, `-`, `*`, `/`) instead use
  the functions: `Float80.add/2`, `Float80.subtract/2`, `Float80.multiple/2`, `Float80.divide/2`.

  ## Examples
      iex> a = Float80.from(1.0)
      <<0, 0, 0, 0, 0, 0, 0, 128, 255, 63>>
      iex> b = Float80.from(2.0)
      <<0, 0, 0, 0, 0, 0, 0, 128, 0, 64>>
      iex> result80 = Float80.add(a, b)
      <<0, 0, 0, 0, 0, 0, 0, 192, 0, 64>>
      iex> result = Float80.to_float(result80)
      3.0

  """

  @typedoc """
  80-bit floating point number.
  """
  @type float80 :: <<_::80>>

  @on_load :load_nifs

  app = Mix.Project.config[:app]

  def load_nifs do
    path = :filename.join(:code.priv_dir(unquote(app)), 'float80')
    :ok = :erlang.load_nif(path, 0)
  end

  @doc """
  Returns a Float80 with the value 0.
  """
  @spec zero() :: float80
  def zero do 
    <<0::80>>
  end

  @spec from(number) :: float80
  def from(value) when is_number(value) do
    cond do
      is_integer(value) ->
        from_integer(value)
      is_float(value) ->
        from_float(value)
    end
  end

  @spec from_float(float) :: float80
  defp from_float(_) do
    exit(:nif_library_not_loaded)
  end

  @spec from_integer(integer) :: float80
  defp from_integer(_) do
    exit(:nif_library_not_loaded)
  end

  @spec to_float(float80) :: float
  def to_float(_) do
    exit(:nif_library_not_loaded)
  end

  @spec add(float80, float80) :: float80
  def add(_, _) do
    exit(:nif_library_not_loaded)
  end

  @spec subtract(float80, float80) :: float80
  def subtract(_, _) do
    exit(:nif_library_not_loaded)
  end

  @spec multiply(float80, float80) :: float80
  def multiply(_, _) do
    exit(:nif_library_not_loaded)
  end

  @spec divide(float80, float80) :: float80
  def divide(_, _) do
    exit(:nif_library_not_loaded)
  end

  @spec abs(float80) :: float80
  def abs(_) do
    exit(:nif_library_not_loaded)
  end

  @spec pi() :: float80
  def pi() do
    exit(:nif_library_not_loaded)
  end

  @spec acos(float80) :: float80
  def acos(_) do
    exit(:nif_library_not_loaded)
  end

  @spec asin(float80) :: float80
  def asin(_) do
    exit(:nif_library_not_loaded)
  end

  @spec atan(float80) :: float80
  def atan(_) do
    exit(:nif_library_not_loaded)
  end

  @spec cos(float80) :: float80
  def cos(_) do
    exit(:nif_library_not_loaded)
  end

  @spec sin(float80) :: float80
  def sin(_) do
    exit(:nif_library_not_loaded)
  end

  @spec tan(float80) :: float80
  def tan(_) do
    exit(:nif_library_not_loaded)
  end

  @spec exp(float80) :: float80
  def exp(_) do
    exit(:nif_library_not_loaded)
  end

  @spec log(float80) :: float80
  def log(_) do
    exit(:nif_library_not_loaded)
  end

  @spec log10(float80) :: float80
  def log10(_) do
    exit(:nif_library_not_loaded)
  end

  @spec log2(float80) :: float80
  def log2(_) do
    exit(:nif_library_not_loaded)
  end

  @spec pow(float80, float80) :: float80
  def pow(_, _) do
    exit(:nif_library_not_loaded)
  end

  @spec sqrt(float80) :: float80
  def sqrt(_) do
    exit(:nif_library_not_loaded)
  end

  @spec ceil(float80) :: float80
  def ceil(_) do
    exit(:nif_library_not_loaded)
  end

  @spec floor(float80) :: float80
  def floor(_) do
    exit(:nif_library_not_loaded)
  end

  @spec round(float80) :: float80
  def round(_) do
    exit(:nif_library_not_loaded)
  end

end
