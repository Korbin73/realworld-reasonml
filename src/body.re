open Models;
// let show = ReasonReact.string;

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

type action =
  | SetCurrentArticle(article);

let articleCallback = (self, currentArticle) => {
  self.ReasonReact.send(SetCurrentArticle(currentArticle))
};

// let mapUrlToRoute = (url: ReasonReact.Router.url) => 
//   switch (url.path) {
//   | ["home"] => Home
//   | ["register"] => Register
//   | ["login"] => Login
//   | ["createarticle"] => CreateArticle
//   | ["editarticle"] => EditArticle
//   | ["article"] => Article
//   | ["profile"] => Profile
//   | ["settings"] => Settings
//   | _ => Login
//   };

type state = { 
  currentArticle: Models.article
};

[@react.component]
let make = () => {
  let (article, setArticle) = React.useState(_ => defaultArticle );
  let (state, dispatch) = React.useReducer(
    (state, action) => 
      switch action {
      | SetCurrentArticle(article) => {currentArticle: article}
      },
      {currentArticle: defaultArticle}
    );


  <>
    <div> 
      <Header/>
    </div>
  </>

  // reducer: (action, state) =>
  //   switch action {
  //   | SetCurrentArticle(article) => ReasonReact.Update({...state, currentArticle: article})
  //   | ChangeRoute(route) => ReasonReact.Update({...state, route: route})
  //   },

  // render: (self) => {
  //   /* let {ReasonReact.state, reduce} = self; */
  //   let article = self.state.currentArticle;
  //   let select_subpage = 
  //     switch self.state.route {
  //     | Home => <Home articleCallback=articleCallback(self) />
  //     | Register => <Register />
  //     | Login => <Login />
  //     | Settings => <Settings />
  //     | Article => <Article article />
  //     | CreateArticle => <CreateArticle />
  //     | EditArticle => <Article article />
  //     | Profile => <Profile articleCallback=articleCallback(self) />
  //     };
  //   <div> <Header /> <div> { select_subpage} </div> <Footer /> </div>
  // }
}