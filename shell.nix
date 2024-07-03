{ pkgs ? import <nixpkgs> {}, lib ? pkgs.lib }:
let
  run = with pkgs; [
    libxkbcommon
    shaderc
    vulkan-extension-layer
    vulkan-loader
    vulkan-tools
    vulkan-tools-lunarg
    vulkan-validation-layers
    wayland
  ];
in
pkgs.mkShell {
  buildInputs = run;
  shellHook = ''
    export LD_LIBRARY_PATH=${lib.makeLibraryPath run}
  '';
}