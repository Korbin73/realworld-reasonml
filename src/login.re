let component = ReasonReact.statelessComponent "Login";
let show = ReasonReact.stringToElement;

type state = {
  email: string,
  password: string,
  hasValidationError: bool,
  errorList: list string  
};

type action =
  | Login (bool, list string)
  | EmailUpdate string
  | PasswordUpdate string
  | LoginPending;

let goToRegister router event => {
  ReactEventRe.Mouse.preventDefault event;
  DirectorRe.setRoute router "/register";
};

let updateEmail event => EmailUpdate (ReactDOMRe.domElementToObj (ReactEventRe.Form.target event))##value; 
let updatePassword event => PasswordUpdate (ReactDOMRe.domElementToObj (ReactEventRe.Form.target event))##value; 

let loginUser route {ReasonReact.state: state, reduce} event => {
  ReactEventRe.Mouse.preventDefault event;
  
  LoginPending
};
let component = ReasonReact.reducerComponent "Login";
let make ::router _children => {
  {
  ...component,  
  initialState: fun () => {email: "", password: "", hasValidationError: false, errorList: []},
  reducer: fun action state => {
    switch action {
      | EmailUpdate value => ReasonReact.Update {...state, email: value}
      | PasswordUpdate value => ReasonReact.Update {...state, password: value}
      | Login (hasError, errorList) => ReasonReact.Update {...state, hasValidationError: hasError, errorList: errorList }
      | LoginPending => ReasonReact.NoUpdate
  }},       
  render: fun self => {
    let {ReasonReact.state: state, reduce} = self;
    {
    <div className="auth-page">
      <div className="container page">
        <div className="row">
          <div className="col-md-6 offset-md-3 col-xs-12">
            <h1 className="text-xs-center"> (show "Sign in") </h1>
            <p className="text-xs-center"> <a href="#" onClick={goToRegister router}> (show "Need an account?") </a> </p>            
            <form>
              <fieldset className="form-group">
                <input
                  _type="text"
                  className="form-control form-control-lg"
                  placeholder="Email"
                  value=state.email
                  onChange=(reduce updateEmail)
                />
              </fieldset>
              <fieldset className="form-group">
                <input
                  _type="password"
                  className="form-control form-control-lg"
                  placeholder="Password"
                  value=state.password
                  onChange=(reduce updatePassword)
                />
              </fieldset>
              <button onClick=(reduce (loginUser router self)) className="btn btn-lg btn-primary pull-xs-right"> (show "Sign in") </button>
            </form>
          </div>
        </div>
      </div>
    </div>}
    }
  }
};