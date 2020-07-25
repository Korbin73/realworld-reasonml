// open Utils;

let show = ReasonReact.string;

let pointerStyle = () => ReactDOMRe.Style.make(~cursor="pointer", ());

let goToRegistration = (_event) => ReasonReactRouter.push("/register");
let goToHome = (event) => {
  ReactEvent.Synthetic.preventDefault(event);
};
let goToSettings = (_event) => ReasonReactRouter.push("/settings");
let goToCreateArticle = (_event) => ReasonReactRouter.push("/article/create");

let displayUsername = () => {
  let (optionalName, _, _) = Effects.getUserFromStorage();
  switch optionalName {
    | Some(name) => name
    | None => "Username Missing"
  };
};

/* This really should be in a reducer component since we are doing a side effect here. */
let displayByLogin = () => {  
  switch (Effects.getTokenFromStorage()) {
    | Some(_token) => {
      <a className="nav-link" style=(pointerStyle()) href="#" onClick={goToRegistration}>
        (show(displayUsername()))
      </a>
    }
    | None => {
      <a className="nav-link" style=(pointerStyle()) href="#" onClick={goToRegistration}>
      (show("Sign up"))
    </a>
    }
  };
};

[@react.component]
let make = () => {
  <div>
    <nav className="navbar navbar-light">
      <div className="container">
        <a className="navbar-brand" href="index.html"> (show("conduit")) </a>
        <ul className="nav navbar-nav pull-xs-right">
          <li className="nav-item">
            <a className="nav-link active" style=(pointerStyle()) href="#" onClick={goToHome}>
              (show("Home"))
            </a>
          </li>
          <li className="nav-item">
            <a className="nav-link" style=(pointerStyle()) href="#" onClick={goToCreateArticle}>
              <i className="ion-compose" />
              (show(" New Post"))
            </a>
          </li>
          <li className="nav-item">
            <a className="nav-link" style=(pointerStyle()) href="#" onClick={goToSettings}>
              <i className="ion-gear-a" />
              (show(" Settings"))
            </a>
          </li>
          <li className="nav-item">
            {displayByLogin()}
          </li>
        </ul>
      </div>
    </nav>
  </div>
};
