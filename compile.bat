@echo off
for /r shaders/ %%i in (*.vert, *.frag) do glslc %%i -o %%i.spv
