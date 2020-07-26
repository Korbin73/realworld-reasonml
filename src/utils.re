let navigateTo = (path, event) => {
  ReactEvent.Mouse.preventDefault(event);
  ReasonReactRouter.push("#" ++ path);
};