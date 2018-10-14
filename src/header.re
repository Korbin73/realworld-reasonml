open Utils;

let component = ReasonReact.statelessComponent("Header");

let show = ReasonReact.string;

let pointerStyle = () => ReactDOMRe.Style.make(~cursor="pointer", ());

let goToRegistration = (event, _self) => navigateTo("/register", event);
let goToHome = (event, _self) => navigateTo("/home",event);
let goToSettings = (event, _self) => navigateTo("/settings", event);
let goToCreateArticle = (event, _self) => navigateTo("/article/create", event);

let displayUsername = () => {
  let (optionalName, _, _) = Effects.getUserFromStorage();
  switch optionalName {
    | Some(name) => name
    | None => "Username Missing"
  };
};

/* This really should be in a reducer component since we are doing a side effect here. */
let displayByLogin = (self) => {  
  switch (Effects.getTokenFromStorage()) {
    | Some(_token) => {
      <a className="nav-link" style=(pointerStyle()) href="#" onClick={self.ReasonReact.handle(goToRegistration)}>
        (show(displayUsername()))
      </a>
    }
    | None => {
      <a className="nav-link" style=(pointerStyle()) href="#" onClick={self.ReasonReact.handle(goToRegistration)}>
      (show("Sign up"))
    </a>
    }
  };
};

let make = ( _children) => {
  ...component, /* spread the template's other defaults into here  */
  render: (self) =>
    <div>
      <nav className="navbar navbar-light">
        <div className="container">
          <a className="navbar-brand" href="index.html"> (show("conduit")) </a>
          <ul className="nav navbar-nav pull-xs-right">
            <li className="nav-item">
              <a className="nav-link active" style=(pointerStyle()) href="#" onClick=(self.ReasonReact.handle(goToHome))>
                (show("Home"))
              </a>
            </li>
            <li className="nav-item">
              <a className="nav-link" style=(pointerStyle()) href="#" onClick={self.ReasonReact.handle(goToCreateArticle)}>
                <i className="ion-compose" />
                (show(" New Post"))
              </a>
            </li>
            <li className="nav-item">
              <a className="nav-link" style=(pointerStyle()) href="#" onClick={self.ReasonReact.handle(goToSettings)}>
                <i className="ion-gear-a" />
                (show(" Settings"))
              </a>
            </li>
            <li className="nav-item">
              {displayByLogin(self)}
            </li>
          </ul>
        </div>
      </nav>
    </div>
};
