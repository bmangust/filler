import React, { Component } from "react";
import css from "./App.module.css";
import Header from "../../components/Header/Header";
import MainMenu from "../../components/MainMenu/MainMenu";
import Footer from "../../components/Footer/Footer";
import Game from "../../components/Game/Game";
import Settings from "../../components/Settings/Settings";

class App extends Component {
  state = {
    states: ["main", "game", "settings", "about"],
    // { state: "main" },
    // { state: "game" },
    // { state: "settings" },
    // { state: "about" },
    currentState: "game",
    settings: {
      players: [],
      mapSize: "",
    },
    gameState: {
      map: [],
      players: [],
      score: [],
      piece: [],
    },
    players: [
      "abanlin",
      "akraig",
      "carli",
      "champely",
      "grati",
      "hcao",
      "lcharvol",
      "superjeannot",
      "zweng",
    ],
    mapSizes: ["small", "medium", "big"],
  };

  constructor(props) {
    super(props);
    const map = this._initMap(17, 15);
    const players = ["akraig", "lcharvol"];
    const score = [100, 20, 10];
    this.state.settings = {
      players: players,
      mapSize: "small",
    };

    this.state.gameState = {
      map: map,
      players: players,
      score: score,
      piece: [],
    };
  }

  // componentDidMount() {
  //   console.log("[App] component did mount");
  //   const gs = { ...this.state.gameState };
  //   gs.map =
  //   this.setState({
  //     gameState: gs,
  //   });
  // }

  _initMap(width, height) {
    const row = ".".repeat(width);
    const map = new Array(height).fill(row);
    return map;
  }

  saveSelector = (e) => {
    const settings = { ...this.state.settings };
    const players = [...settings.players];
    const { name, value } = e.target;
    if (name === "player1") {
      players[0] = value;
    } else if (name === "player2") {
      players[1] = value;
    } else if (name === "mapsize") {
      settings.mapSize = value;
    }
    settings.players = players;
    this.setState({ settings: settings });
  };

  back = () => this.changeCurrentState("main");

  changeCurrentState(nextState) {
    this.setState({ currentState: nextState });
  }

  render() {
    let header = "Welcome to FILLER CHAMPIONSHIP";
    let main = (
      <MainMenu
        loadGame={() => this.changeCurrentState("game")}
        loadSettings={() => this.changeCurrentState("settings")}
        loadAbout={() => this.changeCurrentState("about")}
      />
    );
    if (this.state.currentState === "game") {
      main = <Game gameState={this.state.gameState} back={this.back} />;
    } else if (this.state.currentState === "settings") {
      header = "Settings";
      main = (
        <Settings
          players={this.state.players}
          mapSizes={this.state.mapSizes}
          settings={this.state.settings}
          onPlayer1Change={this.saveSelector}
          onPlayer2Change={this.saveSelector}
          onMapChange={this.saveSelector}
          back={this.back}
        />
      );
      // } else if (this.state.currentState === "about") {
      //   main = null;
    }
    return (
      <div className={css.App}>
        <Header header={header} />
        {main}
        <Footer />
      </div>
    );
  }
}

export default App;
