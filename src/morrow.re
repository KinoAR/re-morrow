type page = {
  name:string,
  content:string,
  choices: list(choice)
}
and choice = {
  name:string,
  page:string,
};

type book = {
  title:string,
  pages: list(page)
}

type choiceData = {
  name:string,
  pageName:string
}

type pageData = {
  name: string,
  content: string,
  choicesData: list(choiceData),
};

type bookData = {
  title:string,
  pagesData: list(pageData)
};

module Page = {
  type t = page;
  let pageName = (page:t) => page.name;
  let pageContent = (page:t) => page.content;
  let pageChoices = (page:t) => page.choices;
  let choiceByName = (choiceName) => {
    List.find((choice:choice) => choice.name == choiceName);
  };
};

module Choice = {
  type t = choice;
  let choiceName = (choice:choice) => choice.name;
  let page = (choice) => {
    choice.page;
  };
};

module type Book = {
  let book:book;
};

module MakeBook = (Item:Book) => {
  let book = Item.book;
  let title = Item.book.title;
  let length = Item.book.pages -> List.length
  let pageByName = (name) => {
    List.find(page => name == Page.pageName(page), book.pages);
  };

  let pageContents = (name) => name -> pageByName -> Page.pageContent;

  let takeChoice = (choice) => {
    pageByName(choice.page);
  };

  let printBook = () => {
    let book = Item.book;
    print_endline("Title: " ++ book.title);
    print_endline("Book Length: " ++ string_of_int(length));
    print_endline("Ratings: " ++ "Some Rating");
  }
};

module Parser = {
  let parseChoice = (json) => {
    Json.Decode.{
      name: json |> field("name", string),
      pageName: json |> field("page", string)
    }
  };

  let parsePage = (json) => {
    Json.Decode.{
      name: json |> field("name", string),
      content: json |> field("content", string),
      choicesData: json |> field("choices", list(parseChoice))
    }
  };

  let parseBook = (json) => {
    Json.Decode.{
      title: json |> field("title", string),
      pagesData: json |> field("pages", list(parsePage))
    }
  };
}

module Read  = {
  let file = (fileName) => {
   [|fileName|] -> Node.Path.join -> Node.Fs.readFileAsUtf8Sync;
  };

  let fileJson = (fileName) => fileName -> file -> Js.Json.string
};

let recreateBook = (data) => {
  {
    title: data.title,
    pages: List.map((pageData) => {
      name: pageData.name,
      content: pageData.content,
      choices: List.map((choiceData:choiceData) => {
        name:choiceData.name,
        page:  choiceData.pageName
      }, pageData.choicesData)
    }, data.pagesData)
  }
}