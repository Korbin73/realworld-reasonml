let navigateTo = (path, event) => {
  ReactEvent.Mouse.preventDefault(event);
  ReasonReact.Router.push("#" ++ path);
};
