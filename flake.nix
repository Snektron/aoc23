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
    packages.${system} = {
      algol68g = pkgs.algol68g.overrideAttrs (old: {
        # gsl-config is needed on the path
        nativeBuildInputs = old.nativeBuildInputs ++ [ pkgs.gsl ];
      });

      a68toc = pkgs.callPackage ({
        stdenv,
        fetchFromGitHub,
        which
      }: stdenv.mkDerivation {
        name = "a68toc";
        version = "1.15";

        src = fetchFromGitHub {
          owner = "coolbikerdad";
          repo = "Algol-68RS-Source";
          rev = "ef25e71aa7d45f602ad464dd28059be3834db173";
          hash = "sha256-81RcAoPqYZjQv5ODgf9uNahbbCUJ0qANnsP0Yt7DcEA=";
        };

        nativeBuildInputs = [ which ];

        A68_NAMESEED = "nameseed";

        installPhase = ''
          mkdir -p $out
          make \
            PKGDIR=$out/share/algol68toc \
            DOCDIR=$out/share/doc/algol68toc \
            BINDIR=$out/bin \
            LIBDIR=$out/lib \
            INFODIR=$out/share/info \
            MANDIR=$out/share/man/man1 \
            INCDIR=$out/include/algol68 \
            APPDIR=$out/share/applications \
            DESTDIR=$out \
            INSTALL=install \
            install

            substituteInPlace $out/bin/ca \
              --replace "/usr/bin/a68toc" "$out/bin/a68toc" \
              --replace "/usr/share/algol68toc" "$out/share/algol68toc" \
              --replace "/usr/include/algol68" "$out/include/algol68" \
              --replace "/usr/include" "$out/include"
        '';
      }) {};
    };

    devShells.${system}.default = pkgs.mkShell {
      name = "aoc23";

      nativeBuildInputs = with pkgs; [
        packages.${system}.algol68g
        packages.${system}.a68toc
        gdb
        postgresql_15
        plotutils
        gsl
        gmp
        mpfr
        ncurses
        hyperfine
        linuxPackages_latest.perf
        python310
      ];
    };
  };
}
