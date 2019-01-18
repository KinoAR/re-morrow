open Express;
let bookString = Morrow.Read.file("save-the-princess.json");
let exampleBook = Morrow.recreateBookFromString(bookString);
module CreatedBook = {
  let book = exampleBook;
};
module CurrentBook = Morrow.MakeBook(CreatedBook);
print_endline(CurrentBook.title);
let startPage = CurrentBook.pageByName("introduction");
print_endline(Morrow.Page.pageContent(startPage));
CurrentBook.printChoices(startPage);
"next" -> Morrow.Page.choiceByName(startPage) -> CurrentBook.takeChoice
-> Morrow.Page.pageContent -> print_endline;

/*  Rest End Points */
let app =  Express.express();
let port = 3001;
let onListen = e =>
  switch (e) {
  | exception (Js.Exn.Error(e)) =>
    Js.log(e);
    Node.Process.exit(1);
  | _ => Js.log @@ "Listening at http://127.0.0.1:3001"
  };

let makeSuccessJson = () => {
  let json = Js.Dict.empty();
  Js.Dict.set(json, "success", Js.Json.boolean(true));
  Js.Json.object_(json);
};  

app -> Express.App.get(~path="/", Express.Middleware.from((next, req) => {
  Response.sendJson(makeSuccessJson());
  /* switch (Request.baseUrl(req)) {
  | "" => Response.sendJson(makeSuccessJson())
  | _ => next(Next.route)
  }; */
}))  
app -> Express.App.listen(~port, ~onListen, ())