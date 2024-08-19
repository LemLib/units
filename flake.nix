{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
    utils.url = "github:numtide/flake-utils";
    #pros-cli-nix.url = "/home/battlechicken/Projects/pros-cli-nix";
    pros-cli-nix.url = "github:BattleCh1cken/pros-cli-nix";
  };

  outputs =
    { self
    , nixpkgs
    , utils
    , pros-cli-nix
    }:
    utils.lib.eachDefaultSystem (system:
    let
      pkgs = import nixpkgs { inherit system; };
    in
    {
      devShell = pkgs.mkShell {
        packages = with pkgs; [
          pros-cli-nix.packages.${system}.default
          clang-tools
          gcc-arm-embedded-10

          doxygen

          python312
          python312Packages.pip
          python312Packages.breathe
          python312Packages.furo
          python312Packages.myst-parser
          python312Packages.sphinx-copybutton
          python312Packages.linkify-it-py

          sphinx-autobuild
          sphinx
        ];
      };
    });
}
