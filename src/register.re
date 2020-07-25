open JsonRequests;
open Utils;

type action =
  | Login
  | Register((bool, list(string)))
  | NameUpdate(string)
  | EmailUpdate(string)
  | PasswordUpdate(string);

type state = {
  username: string,
  email: string,
  password: string,
  hasValidationError: bool,
  errorList: list(string),
};

module Encode = {
  let encodeUserCredentials = creds => {
    open! Json.Encode;
    object_([
      ("email", string(creds.email)),
      ("password", string(creds.password)),
      ("username", string(creds.username)),
    ]);
  };
  let user = r =>
    Json.Encode.(object_([("user", encodeUserCredentials(r))]));
};

let component = ReasonReact.reducerComponent("Register");

let show = React.string;

let register = (event, self) => {
  event->ReactEvent.Mouse.preventDefault;
  let jsonRequest = Encode.user(self.ReasonReact.state);
  let updateState = (_status, jsonPayload) =>
    jsonPayload
    |> Js.Promise.then_(json => {
         let newUser = parseNewUser(json);
         let updatedState =
           switch (newUser.errors) {
           | Some(_user) =>
             ReasonReact.Router.push("/home");
             {...self.ReasonReact.state, hasValidationError: false};
           | None => {
               ...self.ReasonReact.state,
               hasValidationError: true,
               errorList: newUser |> Convert.toErrorListFromResponse,
             }
           };
         self.ReasonReact.send(
           Register((
             updatedState.hasValidationError,
             updatedState.errorList,
           )),
         )
         |> Js.Promise.resolve;
       });
  JsonRequests.registerNewUser(updateState, jsonRequest) |> ignore;
  self.ReasonReact.send(Register((false, ["Hitting server."])));
};

let goToLogin = (event, _self) => navigateTo("/login", event);

let login = _event => Login;

let updateName = (event, {ReasonReact.send}) =>
  send(NameUpdate(ReactEvent.Form.target(event)##value));

let updateEmail = (event, {ReasonReact.send}) =>
  send(EmailUpdate(ReactEvent.Form.target(event)##value));

let updatePassword = (event, {ReasonReact.send}) =>
  send(PasswordUpdate(ReactEvent.Form.target(event)##value));

let errorDisplayList = state =>
  List.filter(
    errorMessage => String.length(errorMessage) > 0,
    state.errorList,
  )
  |> List.mapi((acc, errorMessage) =>
       <ul className="error-messages" key=(string_of_int(acc))>
         <li> (show(errorMessage)) </li>
       </ul>
     );

[@react.component]
let make = () => {
  ...component,
  initialState: () => {
    username: "",
    email: "",
    password: "",
    hasValidationError: false,
    errorList: [],
  },
  reducer: (action, state) =>
    switch (action) {
    | NameUpdate(value) => ReasonReact.Update({...state, username: value})
    | EmailUpdate(value) => ReasonReact.Update({...state, email: value})
    | PasswordUpdate(value) =>
      ReasonReact.Update({...state, password: value})
    | Login => ReasonReact.NoUpdate
    | Register((hasError, errorList)) =>
      ReasonReact.Update({...state, hasValidationError: hasError, errorList})
    },
  render: self => {
    let {ReasonReact.state} = self;
    <div className="auth-page">
      <div className="container page">
        <div className="row">
          <div className="col-md-6 offset-md-3 col-xs-12">
            <h1 className="text-xs-center"> (show("Sign up")) </h1>
            <p className="text-xs-center">
              <a href="#" onClick=(self.handle(goToLogin))>
                (show("Have an account?"))
              </a>
            </p>
            (
              if (state.hasValidationError) {
                Array.of_list(errorDisplayList(state)) |> React.array;
              } else {
                React.null;
              }
            )
            <form>
              <fieldset className="form-group">
                <input
                  type_="text"
                  className="form-control form-control-lg"
                  placeholder="Your Name"
                  value=state.username
                  onChange=(self.handle(updateName))
                />
              </fieldset>
              <fieldset className="form-group">
                <input
                  type_="text"
                  className="form-control form-control-lg"
                  placeholder="Email"
                  value=state.email
                  onChange=(self.handle(updateEmail))
                />
              </fieldset>
              <fieldset className="form-group">
                <input
                  type_="password"
                  className="form-control form-control-lg"
                  placeholder="Password"
                  value=state.password
                  onChange=(self.handle(updatePassword))
                />
              </fieldset>
              <button
                onClick=(self.handle(register))
                className="btn btn-lg btn-primary pull-xs-right">
                (show("Sign up"))
              </button>
            </form>
          </div>
        </div>
      </div>
    </div>;
  },
};

/* TODO: use the route to go the next home screen when registered successfully */
