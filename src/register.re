open JsonRequests;
open Utils;

type state = {
  username: string,
  email: string,
  password: string,
  hasValidationError: bool,
  errorList: list(string)
};

type action =
  | Login
  | Register((bool, list(string)))
  | NameUpdate(string)
  | EmailUpdate(string)
  | PasswordUpdate(string);

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

let show = React.string;

let register = (dispatch, registrationState) => {
  // event->ReactEvent.Mouse.preventDefault;
  let jsonRequest = Encode.user(registrationState);
  let updateState = (_status, jsonPayload) =>
    jsonPayload
    |> Js.Promise.then_(json => {
         let newUser = parseNewUser(json);
         let updatedState =
           switch (newUser.errors) {
           | Some(_user) =>
             ReasonReact.Router.push("#home");
             {...registrationState, hasValidationError: false};
           | None => {
               ...registrationState,
               hasValidationError: true,
               errorList: newUser |> Convert.toErrorListFromResponse,
             }
           };
    
          Js.log(updatedState);
    
    // dispatch(Register((updatedState.hasValidationError,updatedState.errorList)),)
    //      |> Js.Promise.resolve;

       });
  
    JsonRequests.registerNewUser(updateState, jsonRequest) |> ignore;
    dispatch(Register((false, ["Hitting server."])));
  
};

let prototypeApiCall = (dispatch) => {

}

let goToLogin = navigateTo("#login");

let login = _event => Login;

let updateName = (dispatch, event) =>
  dispatch(NameUpdate(ReactEvent.Form.target(event)##value));

let updateEmail = (dispatch, event) =>
  dispatch(EmailUpdate(ReactEvent.Form.target(event)##value));

let updatePassword = (dispatch, event) =>
  dispatch(PasswordUpdate(ReactEvent.Form.target(event)##value));

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
  let (shouldSubmit, setShouldSubmit) = React.useState(_ => false);
  let initialState = {
    username: "",
    email: "",
    password: "",
    hasValidationError: false,
    errorList: []
  };

  let (state, dispatch) = React.useReducer((state, action) => 
    switch action {
    | Login => state
    | NameUpdate(name) => {...state, username: name}
    | EmailUpdate(email) => {...state, email: email}
    | PasswordUpdate(pass) => {...state, password: pass}
    | Register((hasError, errorList)) => {...state, hasValidationError: hasError, errorList}
    },
    initialState
  );
  
  React.useEffect1(() => {
    Js.log("Effect called from rerender")
    if (shouldSubmit) {
      Js.log("Call api endpoint")
      // This api endpoint call works. If the called needed to update the state then setting the state would be needed which 
      // would require a re-render.
      register(dispatch, state)
      // reset it back so it can be called again if the user hit the submit button
      
      setShouldSubmit(_ => false)
    };
    
    None;
  }, [|shouldSubmit|]);
 
  <div className="auth-page">
    <div className="container page">
      <div className="row">
        <div className="col-md-6 offset-md-3 col-xs-12">
          <h1 className="text-xs-center"> (show("Sign up")) </h1>
          <p className="text-xs-center">
            <a href="#" onClick={goToLogin}>
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
                onChange={updateName(dispatch)}
              />
            </fieldset>
            <fieldset className="form-group">
              <input
                type_="text"
                className="form-control form-control-lg"
                placeholder="Email"
                value=state.email
                onChange={updateEmail(dispatch)}
              />
            </fieldset>
            <fieldset className="form-group">
              <input
                type_="password"
                className="form-control form-control-lg"
                placeholder="Password"
                value=state.password
                onChange={updatePassword(dispatch)}
              />
            </fieldset>
            <button
              onClick={_ =>  setShouldSubmit(_ => true)}
              className="btn btn-lg btn-primary pull-xs-right">
              (show("Sign up"))
            </button>
          </form>
        </div>
      </div>
    </div>
  </div>
};

/* TODO: use the route to go the next home screen when registered successfully */
