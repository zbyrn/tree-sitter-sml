const root = require("path").join(__dirname, "..", "..", "grammars", "sml");

module.exports =
  typeof process.versions.bun === "string"
    // Support `bun build --compile` by being statically analyzable enough to find the .node file at build-time
    ? require(`../../prebuilds/${process.platform}-${process.arch}/tree-sitter-sml.node`)
    : require("node-gyp-build")(root);

try {
  module.exports.nodeTypeInfo = require("../../grammars/sml/src/node-types.json");
} catch (_) {}
