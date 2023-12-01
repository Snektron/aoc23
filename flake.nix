{
  description = "AOC23 flake";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-23.11";
  };

  outputs = { self, nixpkgs }:
  let
    system = "x86_64-linux";
    pkgs = nixpkgs.legacyPackages.${system};
  in rec {
    packages.${system}.algol68g = pkgs.algol68g.overrideAttrs (old: {
      # gsl-config is needed on the path
      nativeBuildInputs = old.nativeBuildInputs ++ [ pkgs.gsl ];
    });

    devShells.${system}.default = pkgs.mkShell {
      name = "aoc23";

      nativeBuildInputs = with pkgs; [
        packages.${system}.algol68g
        gdb
        postgresql_15
        plotutils
        gsl
        gmp
        mpfr
        ncurses
      ];
    };
  };
}
