open Utils;

let show = React.string;

let pointerStyle = () => ReactDOMRe.Style.make(~cursor="pointer", ());

let goToRegistration = navigateTo("register");
let goToHome = navigateTo("home");
let goToSettings = navigateTo("settings");
let goToCreateArticle = navigateTo("createarticle");

let displayUsername = () => {
  let (optionalName, _, _) = Effects.getUserFromStorage();
  switch (optionalName) {
  | Some(name) => name
  | None => "Username Missing"
  };
};

let displayByLogin = () =>
  switch (Effects.getTokenFromStorage()) {
  | Some(_token) =>
    <a
      className="nav-link"
      style=(pointerStyle())
      href="#"
      onClick={event => goToRegistration(event)}>
      (show(displayUsername()))
    </a>
  | None =>
    <a
      className="nav-link"
      style=(pointerStyle())
      href="#"
      onClick={event => goToRegistration(event)}>
      (show("Sign up"))
    </a>
  };

[@react.component]
let make = () => {
  /* spread the template's other defaults into here  */
    <div>
      <nav className="navbar navbar-light">
        <div className="container">
          <a className="navbar-brand" href="index.html">
            (show("conduit"))
          </a>
          <ul className="nav navbar-nav pull-xs-right">
            <li className="nav-item">
              <a
                className="nav-link active"
                style=(pointerStyle())
                href="#"
                onClick={goToHome}>
                (show("Home"))
              </a>
            </li>
            <li className="nav-item">
              <a
                className="nav-link"
                style=(pointerStyle())
                href="#"
                onClick={goToCreateArticle}>
                <i className="ion-compose" />
                (show(" New Post"))
              </a>
            </li>
            <li className="nav-item">
              <a
                className="nav-link"
                style=(pointerStyle())
                href="#"
                onClick={goToSettings}>
                <i className="ion-gear-a" />
                (show(" Settings"))
              </a>
            </li>
            <li className="nav-item"> {displayByLogin()} </li>
          </ul>
        </div>
      </nav>
    </div>
};


/* This really should be in a reducer component since we are doing a side effect here. */
