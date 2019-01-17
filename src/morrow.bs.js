// Generated by BUCKLESCRIPT VERSION 4.0.14, PLEASE EDIT WITH CARE
'use strict';

var Fs = require("fs");
var List = require("bs-platform/lib/js/list.js");
var Path = require("path");
var Json_decode = require("@glennsl/bs-json/src/Json_decode.bs.js");

function pageName(page) {
  return page[/* name */0];
}

function pageContent(page) {
  return page[/* content */1];
}

function pageChoices(page) {
  return page[/* choices */2];
}

function choiceByName(choiceName) {
  return (function (param) {
      return List.find((function (choice) {
                    return choice[/* name */0] === choiceName;
                  }), param);
    });
}

var Page = /* module */[
  /* pageName */pageName,
  /* pageContent */pageContent,
  /* pageChoices */pageChoices,
  /* choiceByName */choiceByName
];

function choiceName(choice) {
  return choice[/* name */0];
}

function page(choice) {
  return choice[/* page */1];
}

var Choice = /* module */[
  /* choiceName */choiceName,
  /* page */page
];

function parseChoice(json) {
  return /* record */[
          /* name */Json_decode.field("name", Json_decode.string, json),
          /* pageName */Json_decode.field("page", Json_decode.string, json)
        ];
}

function parsePage(json) {
  return /* record */[
          /* name */Json_decode.field("name", Json_decode.string, json),
          /* content */Json_decode.field("content", Json_decode.string, json),
          /* choices */Json_decode.field("choices", (function (param) {
                  return Json_decode.list(parseChoice, param);
                }), json)
        ];
}

function parseBook(json) {
  return /* record */[
          /* title */Json_decode.field("title", Json_decode.string, json),
          /* pages */Json_decode.field("pages", (function (param) {
                  return Json_decode.list(parsePage, param);
                }), json)
        ];
}

var Parser = /* module */[
  /* parseChoice */parseChoice,
  /* parsePage */parsePage,
  /* parseBook */parseBook
];

function file(fileName) {
  return Fs.readFileSync(Path.join(fileName), "utf8");
}

function fileJson(fileName) {
  return Fs.readFileSync(Path.join(fileName), "utf8");
}

var Read = /* module */[
  /* file */file,
  /* fileJson */fileJson
];

exports.Page = Page;
exports.Choice = Choice;
exports.Parser = Parser;
exports.Read = Read;
/* fs Not a pure module */
