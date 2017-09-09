// Generated by BUCKLESCRIPT VERSION 1.8.2, PLEASE EDIT WITH CARE
'use strict';

var React       = require("react");
var ReasonReact = require("reason-react/lib/js/src/reasonReact.js");

var component = ReasonReact.statelessComponent("Footer");

function show(prim) {
  return prim;
}

function conduit_message() {
  return React.createElement("div", undefined, "An interactive learning project from ", React.createElement("a", {
                  href: "https://thinkster.io"
                }, "Thinkster"), ". Code &amp; design licensed under MIT.");
}

function make() {
  var newrecord = component.slice();
  newrecord[/* render */9] = (function () {
      return React.createElement("footer", undefined, React.createElement("div", {
                      className: "container"
                    }, React.createElement("a", {
                          className: "logo-font",
                          href: "/"
                        }, "conduit"), React.createElement("span", {
                          className: "attribution"
                        }, conduit_message(/* () */0))));
    });
  return newrecord;
}

exports.component       = component;
exports.show            = show;
exports.conduit_message = conduit_message;
exports.make            = make;
/* component Not a pure module */