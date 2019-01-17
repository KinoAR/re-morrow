let bookString = Morrow.Read.file("save-the-princess.json");
let exampleBook = bookString -> Json.parseOrRaise -> Morrow.Parser.parseBook;
print_endline(exampleBook.title);
