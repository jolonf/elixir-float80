defmodule Mix.Tasks.Compile.Float80Nifs do
  def run(_args) do
    {result, _errcode} = System.cmd("make", [])
    IO.binwrite(result)
  end
end

defmodule Float80.MixProject do
  use Mix.Project

  def project do
    [
      app: :float80,
      compilers: [:float80_nifs] ++ Mix.compilers,
      version: "0.1.0",
      elixir: "~> 1.12",
      start_permanent: Mix.env() == :prod,
      deps: deps()
    ]
  end

  # Run "mix help compile.app" to learn about applications.
  def application do
    [
      extra_applications: [:logger]
    ]
  end

  # Run "mix help deps" to learn about dependencies.
  defp deps do
    [
      # {:dep_from_hexpm, "~> 0.3.0"},
      # {:dep_from_git, git: "https://github.com/elixir-lang/my_dep.git", tag: "0.1.0"}
    ]
  end
end
