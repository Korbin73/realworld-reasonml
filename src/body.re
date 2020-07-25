open Models;
let show = React.string;

let defaultAuthor = {username: "", bio: None, image: None, following: false};

let defaultArticle = {
  slug: "",
  title: "",
  description: "",
  body: "",
  tagList: [||],
  createdAt: "",
  updatedAt: "",
  favorited: false,
  favoritesCount: 0,
  author: defaultAuthor,
};

type route =
  | Home
  | Register
  | Login
  | CreateArticle
  | EditArticle
  | Article
  | Profile
  | Settings;

type state = {
  currentArticle: article,
  route,
};

type action =
  | SetCurrentArticle(article)
  | ChangeRoute(route);

let articleCallback = (self, currentArticle) =>
  self.ReasonReact.send(SetCurrentArticle(currentArticle));

let mapUrlToRoute = (url: ReasonReact.Router.url) =>
  switch (url.path) {
  | ["home"] => Home
  | ["register"] => Register
  | ["login"] => Login
  | ["createarticle"] => CreateArticle
  | ["editarticle"] => EditArticle
  | ["article"] => Article
  | ["profile"] => Profile
  | ["settings"] => Settings
  | _ => Login
  };

let component = ReasonReact.reducerComponent("Body");

[@react.component]
let make = () => {
  ...component,
  initialState: () => {currentArticle: defaultArticle, route: Home},
  reducer: (action, state) =>
    switch (action) {
    | SetCurrentArticle(article) =>
      ReasonReact.Update({...state, currentArticle: article})
    | ChangeRoute(route) => ReasonReact.Update({...state, route})
    },
  didMount: self => {
    let watchId =
      ReasonReact.Router.watchUrl(url =>
        self.send(ChangeRoute(url |> mapUrlToRoute))
      );
    self.onUnmount(() => ReasonReact.Router.unwatchUrl(watchId));
  },
  render: self => {
    let article = self.state.currentArticle;
    // let select_subpage =
    //   switch (self.state.route) {
    //   | Home => <Home articleCallback=(articleCallback(self)) />
    //   | Register => <Register />
    //   | Login => <Login />
    //   | Settings => <Settings />
    //   | Article => <Article article />
    //   | CreateArticle => <CreateArticle />
    //   | EditArticle => <Article article />
    //   | Profile => <Profile articleCallback=(articleCallback(self)) />
    //   };
    <div> <Header /> <div> <Settings /> </div> <Footer /> </div>;
  },
};
/**
 * This is a wrapper created to let this component be used from the new React api.
 * Please convert this component to a [@react.component] function and then remove this wrapping code.
 */
let make =
  ReasonReactCompat.wrapReasonReactForReact(
    ~component, (reactProps: {. "children": 'children}) =>
    make(reactProps##children)
  );
[@bs.obj]
external makeProps: (~children: 'children, unit) => {. "children": 'children} =
  "";

/* Just like any other variant data can be carried around with variants with the routes */

/* let {ReasonReact.state, reduce} = self; */
