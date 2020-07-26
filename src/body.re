open Models
let show = React.string

let defaultAuthor = {username: "", bio: None, image: None, following: false}

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
}

type route =
  | Home
  | Register
  | Login
  | CreateArticle
  | EditArticle
  | Article
  | Profile
  | Settings

type state = {
  currentArticle: article
}

type action =
  | SetCurrentArticle(article);

let articleCallback = (self, currentArticle) =>
  self.ReasonReact.send(SetCurrentArticle(currentArticle));

[@react.component]
let make = () => {
  let (_state, _dispatch) = React.useReducer((_state, action) => 
    switch action {
    | SetCurrentArticle(article) => {currentArticle: article}
    },
    {currentArticle: defaultArticle}
  )
  
    // let article = self.state.currentArticle;
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

    let url = ReasonReactRouter.useUrl();

    <div> 
      <Header /> 
      <div> {        
        switch url.hash {
        | "home" =>  <div>{React.string("Home by navigation")}</div>
        | "register" => <Register />
        | "login" => <div>{React.string("login")}</div>
        | "createarticle" => <div>{React.string("creating an article")}</div>
        | "editarticle" => <div>{React.string("Editing an article")}</div>
        | "article" => <div>{React.string("showing article")}</div>
        | "profile" => <div>{React.string("profile")}</div>
        | "settings" => <div>{React.string("settings")}</div>
        | _ => <div>{React.string("Home frome")}</div>
        };
      }
      </div> 
      <Footer /> 
    </div>;
  
}
