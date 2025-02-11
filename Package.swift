// swift-tools-version:5.3
import PackageDescription

let package = Package(
    name: "TreeSitterSML",
    products: [
        .library(name: "TreeSitterSML", targets: ["TreeSitterSML"]),
    ],
    dependencies: [
        .package(url: "https://github.com/ChimeHQ/SwiftTreeSitter", from: "0.8.0"),
    ],
    targets: [
        .target(
            name: "TreeSitterSML",
            dependencies: [],
            path: ".",
            sources: [
                "src/parser.c",
                "src/scanner.c",
            ],
            resources: [
                .copy("queries")
            ],
            publicHeadersPath: "bindings/swift",
            cSettings: [.headerSearchPath("src")]
        ),
        .testTarget(
            name: "TreeSitterSMLTests",
            dependencies: [
                "SwiftTreeSitter",
                "TreeSitterSML",
            ],
            path: "bindings/swift/TreeSitterSMLTests"
        )
    ],
    cLanguageStandard: .c11
)
