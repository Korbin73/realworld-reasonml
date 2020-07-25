open Models;

type comment = {
  id: int,
  createdAt: string,
  updatedAt: string,
  body: string,
  author,
};

type commentList = {comments: list(comment)};

type state = {
  slug: string,
  commentList: list(comment),
  articleBody: string,
  isFollowing: bool,
};

let displayImage =
  fun
  | Some(image) => image
  | None => "";

type action =
  | AddComment
  | DeleteComment(int)
  | FollowUser(string)
  | UnFollowUser(string)
  | FetchComments(list(comment));

let show = React.string;
let component = ReasonReact.reducerComponent("Article");

let renderComment = (self, index, comment) =>
  <div className="card" key=(string_of_int(index))>
    <div className="card-block">
      <p className="card-text"> (show(comment.body)) </p>
    </div>
    <div className="card-footer">
      <a href="" className="comment-author">
        <img
          src=(displayImage(comment.author.image))
          className="comment-author-img"
        />
      </a>
      (show(" "))
      <a href="" className="comment-author">
        (show(comment.author.username))
      </a>
      <span className="date-posted">
        (show(Js.Date.fromString(comment.createdAt) |> Js.Date.toDateString))
      </span>
      <span className="mod-options">
        <i
          className="ion-trash-a"
          onClick=(_ => self.ReasonReact.send(DeleteComment(comment.id)))
        />
      </span>
    </div>
  </div>;

let deleteCommentRequest = (id, slug) =>
  JsonRequests.deleteCommentForArticle(
    slug,
    id,
    Effects.getTokenFromStorage(),
  )
  |> ignore;

let followUserRequest = username =>
  JsonRequests.followUser(username, Effects.getTokenFromStorage()) |> ignore;

let unFollowUserRequest = username =>
  JsonRequests.unFollowUser(username, Effects.getTokenFromStorage()) |> ignore;

let decodeAuthor = json =>
  Json.Decode.{
    username: json |> field("username", string),
    bio: json |> optional(field("bio", string)),
    image: json |> optional(field("image", string)),
    following: json |> field("following", bool),
  };

let decodeComment = json =>
  Json.Decode.{
    id: json |> field("id", int),
    createdAt: json |> field("createdAt", string),
    updatedAt: json |> field("updatedAt", string),
    body: json |> field("body", string),
    author: json |> field("author", decodeAuthor),
  };

let followUser = (event, self) =>
  self.ReasonReact.state.isFollowing ?
    self.ReasonReact.send(
      UnFollowUser(ReactEvent.Mouse.target(event)##value),
    ) :
    self.ReasonReact.send(FollowUser(ReactEvent.Mouse.target(event)##value));

let dangerousHtml: string => Js.t('a) = html => {"__html": html};

[@react.component]
let make = (~article) => {
  ...component,
  initialState: () => {
    slug: article.slug,
    commentList: [],
    articleBody: article.body,
    isFollowing: article.author.following,
  },
  reducer: (action, state) =>
    switch (action) {
    | AddComment => ReasonReact.NoUpdate
    | DeleteComment(commentId) =>
      let commentsWithout =
        List.filter(comment => comment.id != commentId, state.commentList);
      ReasonReact.UpdateWithSideEffects(
        {...state, commentList: commentsWithout},
        (_self => deleteCommentRequest(commentId, state.slug)),
      );
    | FetchComments(comments) =>
      ReasonReact.Update({...state, commentList: comments})
    | FollowUser(username) =>
      ReasonReact.UpdateWithSideEffects(
        {...state, isFollowing: true},
        (_self => followUserRequest(username)),
      )
    | UnFollowUser(username) =>
      ReasonReact.UpdateWithSideEffects(
        {...state, isFollowing: false},
        (_self => unFollowUserRequest(username)),
      )
    },
  didMount: self => {
    let reduceComments = (_status, jsonPayload) =>
      jsonPayload
      |> Js.Promise.then_(result => {
           let parsedComments = Js.Json.parseExn(result);
           let commentList =
             Json.Decode.{
               comments:
                 parsedComments |> field("comments", list(decodeComment)),
             };
           self.ReasonReact.send(FetchComments(commentList.comments));
           result |> Js.Promise.resolve;
         });

    JsonRequests.commentsForArticle(self.state.slug, reduceComments) |> ignore;
  },
  render: self =>
    <div className="article-page">
      <div className="banner">
        <div className="container">
          <h1> (show(article.title)) </h1>
          <div className="article-meta">
            <a href=""> <img src=(displayImage(article.author.image)) /> </a>
            <div className="info">
              <a href="" className="author">
                (show(article.author.username))
              </a>
              <span className="date">
                (
                  show(
                    Js.Date.fromString(article.createdAt)
                    |> Js.Date.toDateString,
                  )
                )
              </span>
            </div>
            <button
              className="btn btn-sm btn-outline-secondary"
              value=article.author.username
              onClick=(self.handle(followUser))>
              <i className="ion-plus-round" />
              (show(" "))
              (
                show(
                  (self.state.isFollowing ? "unfollow " : "follow ")
                  ++ article.author.username,
                )
              )
              <span className="counter"> (show("(10)")) </span>
            </button>
            (React.string("  "))
            <button className="btn btn-sm btn-outline-primary">
              <i className="ion-heart" />
              (React.string(" "))
              (show("Favorite Post"))
              <span className="counter"> (show("(0)")) </span>
            </button>
          </div>
        </div>
      </div>
      <div className="container page">
        <div className="row article-content">
          <div className="col-md-12">
            <div dangerouslySetInnerHTML=(dangerousHtml(article.body)) />
          </div>
        </div>
        <hr />
        <div className="article-actions">
          <div className="article-meta">
            <a href="profile.html">
              <img src=(displayImage(article.author.image)) />
            </a>
            <div className="info">
              <a href="" className="author">
                (show(article.author.username))
              </a>
              <span className="date">
                (
                  show(
                    Js.Date.fromString(article.createdAt)
                    |> Js.Date.toDateString,
                  )
                )
              </span>
            </div>
            <button
              className="btn btn-sm btn-outline-secondary"
              value=article.author.username
              onClick=(self.handle(followUser))>
              <i className="ion-plus-round" />
              (show(" "))
              (
                show(
                  (self.state.isFollowing ? "unfollow " : "follow ")
                  ++ article.author.username,
                )
              )
              <span className="counter"> (show("(0)")) </span>
            </button>
            (show(" "))
            <button className="btn btn-sm btn-outline-primary">
              <i className="ion-heart" />
              (React.string(" "))
              (show("Favorite Post"))
              <span className="counter"> (show("(0)")) </span>
            </button>
          </div>
        </div>
        <div className="row">
          <div className="col-xs-12 col-md-8 offset-md-2">
            <form className="card comment-form">
              <div className="card-block">
                <textarea
                  className="form-control"
                  placeholder="Write a comment..."
                  rows=3
                />
              </div>
              <div className="card-footer">
                <img
                  src="http://i.imgur.com/Qr71crq.jpg"
                  className="comment-author-img"
                />
                <button className="btn btn-sm btn-primary">
                  (show("Post Comment"))
                </button>
              </div>
            </form>
            (
              List.mapi(renderComment(self), self.state.commentList)
              |> Array.of_list
              |> React.array
            )
          </div>
        </div>
      </div>
    </div>,
};


/* Add markdown parser to display properly
 */
