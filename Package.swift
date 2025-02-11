// swift-tools-version:5.3

import Foundation
import PackageDescription

var sources = ["src/parser.c"]
if FileManager.default.fileExists(atPath: "src/scanner.c") {
    sources.append("src/scanner.c")
}

let package = Package(
    name: "TreeSitterSml",
    products: [
        .library(name: "TreeSitterSml", targets: ["TreeSitterSml"]),
    ],
    dependencies: [
        .package(url: "https://github.com/tree-sitter/swift-tree-sitter", from: "0.8.0"),
    ],
    targets: [
        .target(
            name: "TreeSitterSml",
            dependencies: [
                .product(name: "SwiftTreeSitter", package: "swift-tree-sitter")
            ],
            path: ".",
            sources: sources,
            resources: [
                .copy("queries")
            ],
            publicHeadersPath: "bindings/swift",
            cSettings: [.headerSearchPath("src")]
        ),
        .testTarget(
            name: "TreeSitterSmlTests",
            dependencies: [
                // "SwiftTreeSitter",
                "TreeSitterSml",
                .product(name: "SwiftTreeSitter", package: "swift-tree-sitter")
            ],
            path: "bindings/swift/TreeSitterSmlTests"
        ),
    ],
    cLanguageStandard: .c11
)
