type page = {
  name:string,
  content:string,
  choices: list(choice)
}
and choice = {
  name:string,
  page:page,
};

type book = {
  title:string,
  pages: array(page)
}

type choiceData = {
  name:string,
  pageName:string
}

type pageData = {
  name: string,
  content: string,
  choices: list(choiceData),
};

type bookData = {
  title:string,
  pages: list(pageData)
};

module Page = {
  type t = page;
  let pageName = (page) => page.name;
  let pageContent = (page) => page.content;
  let pageChoices = (page) => page.choices;
  let choiceByName = (choiceName) => {
    List.find(choice => choice.name == choiceName);
  };
};

module Choice = {
  type t = choice;
  let choiceName = (choice) => choice.name;
  let page = (choice) => {
    choice.page;
  };
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
      choices: json |> field("choices", list(parseChoice))
    }
  };

  let parseBook = (json) => {
    Json.Decode.{
      title: json |> field("title", string),
      pages: json |> field("pages", list(parsePage))
    }
  };
}

module Read  = {
  let file = (fileName) => {
   [|fileName|] -> Node.Path.join -> Node.Fs.readFileAsUtf8Sync;
  };

  let fileJson = (fileName) => fileName -> file -> Js.Json.string
};