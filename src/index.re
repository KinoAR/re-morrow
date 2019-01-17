let bookString = Morrow.Read.file("save-the-princess.json");
let exampleBook = bookString -> Json.parseOrRaise -> Morrow.Parser.parseBook -> Morrow.recreateBook;
module CreatedBook = {
  let book = exampleBook;
};
module CurrentBook = Morrow.MakeBook(CreatedBook);
print_endline(CurrentBook.title);
print_endline(CurrentBook.pageContents("introduction"))
CurrentBook.printBook()