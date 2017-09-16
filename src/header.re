let component = ReasonReact.statelessComponent "Header";
let show = ReasonReact.stringToElement;

let make ::router _children => { 
  ...component, /* spread the template's other defaults into here  */
  render: fun _self => {
    let goToRegistration event => {
      ReactEventRe.Mouse.preventDefault event;
      DirectorRe.setRoute router "/register";
    };
    <div> 
      <nav className="navbar navbar-light">
        <div className="container">
          <a className="navbar-brand" href="index.html"> (show "conduit") </a>
          <ul className="nav navbar-nav pull-xs-right">
          <li className="nav-item">
            <a className="nav-link active" href="#/"> (show "Home") </a>
          </li>
          <li className="nav-item">
            <a className="nav-link" href="#/article/create">
              <i className="ion-compose" /> (show " New Post") 
            </a>
          </li>
          <li className="nav-item">
            <a className="nav-link" href="#/settings">
                <i className="ion-gear-a" /> (show " Settings") 
            </a>
          </li>
          <li className="nav-item">
            <a className="nav-link" href="#" onClick={goToRegistration} > (show "Sign up") </a>
          </li>
        </ul>
        </div>
      </nav>
    </div>
  }
};