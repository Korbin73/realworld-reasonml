let show = React.string;

type state = {
  image: string,
  name: string,
  bio: string,
  email: string,
  password: string,
};

type action =
  | UpdateEmail(string)
  | UpdatePassword(string)
  | UpdateBio(string)
  | UpdateImage(string)
  | UpdateName(string)
  | SettingsFetched(state)
  | SettingsUpdated;

module Encode = {
  let userSettings = (settings: state) =>
    Json.Encode.(
      object_([
        ("email", string(settings.email)),
        ("password", string(settings.password)),
        ("image", string(settings.image)),
        ("username", string(settings.name)),
        ("bio", string(settings.bio)),
      ])
    );

  let user = (settings: state) =>
    Json.Encode.(object_([("user", userSettings(settings))]));

  let token = currentUser => Json.Encode.[("token", string(currentUser))];
};

// let updateSettings = (event, state) => {
//   event->ReactEvent.Mouse.preventDefault;
//   let responseCatch = (_status, payload) => {
//     ReasonReact.Router.push("/profile");
//     payload
//     |> Js.Promise.then_(result => {
//          Js.log(result);
//          result |> Js.Promise.resolve;
//        })
//     |> ignore;
//   };
//   JsonRequests.updateUser(
//     responseCatch,
//     Encode.user(state),
//     Effects.getTokenFromStorage(),
//   )
//   |> ignore;
// };

let getField =
  fun
  | Some(field) => field
  | None => "";

//let component = ReasonReact.reducerComponent("Settings");

[@react.component]
let make = () => {
  let initialState = {image: "", name: "", bio: "", email: "", password: ""};
  let (state, dispatch) = React.useReducer((state, action) => 
    switch action {
    | UpdateEmail(email) => {...state, email}
    | UpdatePassword(password) => {...state, password}
    | UpdateBio(bio) => {...state, bio}
    | UpdateImage(image) => {...state, image}
    | UpdateName(name) => {...state, name}
    | SettingsUpdated => state
    | SettingsFetched(updatedSettings) => { 
        ...state, 
        email: updatedSettings.email, 
        name: updatedSettings.name,
        bio: updatedSettings.bio,
        image: updatedSettings.image
      }
    },
    initialState
  );
  // React.useEffect1(() => {}, state);
  // didMount: self => {
  //   let reduceCurrentUser = (_status, jsonPayload) =>
  //     jsonPayload
  //     |> Js.Promise.then_(result => {
  //          let parsedUser = JsonRequests.parseNewUser(result);

  //          self.send(
  //            SettingsFetched({
  //              image: getField(parsedUser.user.image),
  //              name: parsedUser.user.username,
  //              bio: getField(parsedUser.user.bio),
  //              email: parsedUser.user.email,
  //              password: "",
  //            }),
  //          );
  //          parsedUser.user |> Js.Promise.resolve;
  //        });

  //   let displayResult = result => {
  //     if (result == "401") {
  //       ReasonReact.Router.push("/login");
  //     };

  //     let usersToken =
  //       JsonRequests.getUserGraph(result) |> JsonRequests.parseUser;
  //     JsonRequests.getCurrentUser(reduceCurrentUser, Some(usersToken.token))
  //     |> ignore;

  //     result |> Js.Promise.resolve;
  //   };

  //   let reduceUser = (_status, jsonPayload) =>
  //     jsonPayload |> Js.Promise.then_(displayResult);

  //   JsonRequests.getCurrentUser(reduceUser, Effects.getTokenFromStorage())
  //   |> ignore;
  // },
  
    <div className="settings-page">
      <div className="container page">
        <div className="row">
          <div className="col-md-6 offset-md-3 col-xs-12">
            <h1 className="text-xs-center"> (show("Your Settings")) </h1>
            <form>
              <fieldset>
                <fieldset className="form-group">
                  <input
                    className="form-control"
                    type_="text"
                    placeholder="URL of profile picture"
                    value=state.image
                    onChange={event => dispatch(UpdateImage(ReactEvent.Form.target(event)##value))}
                  />
                </fieldset>
                <fieldset className="form-group">
                  <input
                    className="form-control form-control-lg"
                    type_="text"
                    placeholder="Your Name"
                    value=state.name
                    onChange={event => dispatch(UpdateName(ReactEvent.Form.target(event)##value))}
                  />
                </fieldset>
                <fieldset className="form-group">
                  <textarea
                    className="form-control form-control-lg"
                    rows=8
                    placeholder="Short bio about you"
                    value=state.bio
                    onChange={event => dispatch(UpdateBio(ReactEvent.Form.target(event)##value))}
                  />
                </fieldset>
                <fieldset className="form-group">
                  <input
                    className="form-control form-control-lg"
                    type_="text"
                    placeholder="Email"
                    value=state.email
                    onChange={event => dispatch(UpdateEmail(ReactEvent.Form.target(event)##value))}
                  />
                </fieldset>
                <fieldset className="form-group">
                  <input
                    className="form-control form-control-lg"
                    type_="password"
                    placeholder="Password"
                    value=state.password
                    onChange={event => dispatch(UpdatePassword(ReactEvent.Form.target(event)##value))}
                  />
                </fieldset>
                <button
                  className="btn btn-lg btn-primary pull-xs-right"
                  onClick={_ => ()}>
                  (show("Update Settings"))
                </button>
              </fieldset>
            </form>
          </div>
        </div>
      </div>
    </div>
};