#!/bin/bash

# Create core structure
mkdir -p woflang/{core,ops,repl,glyphs,plugins,constants,docs,tests}

# Move refactored files into place
cp main.cpp woflang/
cp wof_interpreter.cpp woflang/
cp wof_interpreter.hpp woflang/
cp plugin_loader.cpp woflang/
cp repl_commands.cpp woflang/
cp CMakeLists.txt woflang/

# Touch stubs for known files
touch woflang/repl/wofreplrc_loader.cpp
touch woflang/repl/wof_keybind_autoload_patch.cpp
touch woflang/repl/repl_plugin_watch_support.cpp

touch woflang/glyphs/dynamic_glyph_loader.cpp

touch woflang/constants/load_modelica_constants.cpp
touch woflang/constants/load_physics_constants.cpp

touch woflang/ops/ops_control_loop.hpp

# Create doc files if needed
touch woflang/docs/README_TOTAL.md
touch woflang/docs/woflang_setup_guide.md
touch woflang/docs/file_list.md
touch woflang/docs/LICENSE

# Create a test file example
echo '⍺ 10 → loop body 🛑' > woflang/tests/test_list_ops.wof

echo "[done] WOFLANG project scaffolded into ./woflang"
