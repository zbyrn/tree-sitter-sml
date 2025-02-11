import XCTest
import SwiftTreeSitter
import TreeSitterSml

final class TreeSitterSmlTests: XCTestCase {
    func testCanLoadGrammar() throws {
        let parser = Parser()
        let language = Language(language: tree_sitter_sml())
        XCTAssertNoThrow(try parser.setLanguage(language),
                         "Error loading Sml grammar")
    }
}
