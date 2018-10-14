open Models;
let show = ReasonReact.string;

let defaultAuthor = {
  username: "",
  bio: None,
  image: None,
  following: false
};

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
  author: defaultAuthor
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
  route
};

type action =
  | SetCurrentArticle(article)
  | ChangeRoute(route);

let articleCallback = (self, currentArticle) => {
  self.ReasonReact.send(SetCurrentArticle(currentArticle))
};

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
/* Just like any other variant data can be carried around with variants with the routes */
let make = (_children) => {
  ...component,
  initialState: () => { currentArticle: defaultArticle, route: Home },
  reducer: (action, state) =>
    switch action {
    | SetCurrentArticle(article) => ReasonReact.Update({...state, currentArticle: article})
    | ChangeRoute(route) => ReasonReact.Update({...state, route: route})
    },
  didMount: self => {
    let watchId = ReasonReact.Router.watchUrl(url =>
      self.send(ChangeRoute(url |> mapUrlToRoute))
    );
    self.onUnmount(() => ReasonReact.Router.unwatchUrl(watchId));
  },
  render: (self) => {
    /* let {ReasonReact.state, reduce} = self; */
    let article = self.state.currentArticle;
    let select_subpage = 
      switch self.state.route {
      | Home => <Home articleCallback=articleCallback(self) />
      | Register => <Register />
      | Login => <Login />
      | Settings => <Settings />
      | Article => <Article article />
      | CreateArticle => <CreateArticle />
      | EditArticle => <Article article />
      | Profile => <Profile articleCallback=articleCallback(self) />
      };
    <div> <Header /> <div> { select_subpage} </div> <Footer /> </div>
  }
};
