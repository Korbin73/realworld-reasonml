let show = React.string;

let conduit_message = () =>
  <div>
    (show("An interactive learning project from "))
    <a href="https://thinkster.io"> (show("Thinkster")) </a>
    (show(". Code &amp; design licensed under MIT."))
  </div>;

[@react.component]
let make = () => {
    <footer>
      <div className="container">
        <a href="/" className="logo-font"> (show("conduit")) </a>
        <span className="attribution"> (conduit_message()) </span>
      </div>
    </footer>
};