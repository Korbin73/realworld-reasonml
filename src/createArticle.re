let show = ReasonReact.string;

type state = {
  title: string,
  description: string,
  articleBody: string,
  rawTags: string
};

type action =
  | ArticleSubmitted
  | UpdateTitle(string)
  | UpdateDescription(string)
  | UpdateBody(string)
  | UpdateTags(string);

let parseTags = (enteredTags) => Js.String.split(",", enteredTags);

module Encode = {
  let newArticle = (articleDetails: state) => {
    Json.Encode.(object_([
      ("title", string(articleDetails.title)),
      ("description", string(articleDetails.description)),
      ("body", string(articleDetails.articleBody)),
      ("tagList", parseTags(articleDetails.rawTags) |> Json.Encode.stringArray)
    ]));
  };
};

let submissionResponse = (_status, payload) => {
  payload |> Js.Promise.then_((result) => Js.log(result) |> Js.Promise.resolve)
};  

let submitNewArticle = (event, self) => {
  ReactEvent.Mouse.preventDefault(event);
  JsonRequests.submitNewArticle(submissionResponse, Encode.newArticle(self.ReasonReact.state) , Effects.getTokenFromStorage()) |> ignore;
  self.ReasonReact.send(ArticleSubmitted);
};

let updateTitle = (event, self) =>
  self.ReasonReact.send(UpdateTitle(ReactEvent.Form.target(event)##value));
let updateDescription = (event, self) =>
  self.ReasonReact.send(UpdateDescription(ReactEvent.Form.target(event)##value));
let updateBody = (event, self) =>
  self.ReasonReact.send(UpdateBody(ReactEvent.Form.target(event)##value));
let updateTags = (event, self) =>
  self.ReasonReact.send(UpdateTags(ReactEvent.Form.target(event)##value));

/* TODO: Add validation for body and title to be required */

let component = ReasonReact.reducerComponent("CreateArticle");
let make = (_children) => {
  ...component,
  initialState: () => {title:"",description: "", articleBody: "", rawTags: ""},
  reducer: (action, state) =>
    switch action {
    | ArticleSubmitted => ReasonReact.SideEffects((_self) => {
      ReasonReact.Router.push("/home")
    })
    | UpdateTitle(title) => ReasonReact.Update({...state, title: title})
    | UpdateDescription(description) => ReasonReact.Update({...state, description: description})
    | UpdateBody(body) => ReasonReact.Update({...state, articleBody: body})
    | UpdateTags(tags) => ReasonReact.Update({...state, rawTags: tags})
  },
  render: (self) =>
    <div className="editor-page">
      <div className="container page">
        <div className="row">
          <div className="col-md-10 offset-md-1 col-xs-12">
            <form>
              <fieldset>
                <fieldset className="form-group">
                  <input
                    type_="text"
                    className="form-control form-control-lg"
                    placeholder="Article Title"
                    value=(self.state.title)
                    onChange=(self.handle(updateTitle))
                  />
                </fieldset>
                <fieldset className="form-group">
                  <input
                    type_="text"
                    className="form-control"
                    placeholder="What's this article about?"
                    value=(self.state.description)
                    onChange=(self.handle(updateDescription))
                  />
                </fieldset>
                <fieldset className="form-group">
                  <textarea
                    className="form-control"
                    rows=8
                    placeholder="Write your article (in markdown)"
                    value=(self.state.articleBody)
                    onChange=(self.handle(updateBody))
                  />
                </fieldset>
                <fieldset className="form-group">
                  <input 
                    type_="text" 
                    className="form-control" 
                    placeholder="Enter tags" 
                    value=(self.state.rawTags) 
                    onChange=(self.handle(updateTags))
                  />
                  <div className="tag-list" />
                </fieldset>
                <button className="btn btn-lg pull-xs-right btn-primary" type_="button" onClick=(self.handle(submitNewArticle))>
                  (show("Publish Article"))
                </button>
              </fieldset>
            </form>
          </div>
        </div>
      </div>
    </div>
};
