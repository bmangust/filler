import React, { Component } from "react";
import css from "./App.module.css";
import Header from "../components/Header/Header";
import MainMenu from "../components/MainMenu/MainMenu";
import Footer from "../components/Footer/Footer";
import Game from "../components/Game/Game";

class App extends Component {
  state = {
    states: ["main", "game", "settings", "about"],
    // { state: "main" },
    // { state: "game" },
    // { state: "settings" },
    // { state: "about" },
    currentState: "main",
    gameState: {
      map: [],
      players: ["akraig", "hcao"],
      score: [0, 0],
      piece: [],
    },
  };

  componentDidMount() {
    console.log("[App] component did mount");
    const map = this._initMap(17, 15);
    this.setState({
      gameState: {
        map: map,
        players: ["akraig", "hcao"],
        score: [0, 0],
        piece: [],
      },
    });
  }

  _initMap(width, height) {
    const row = ".".repeat(width);
    const map = new Array(height).fill(row);
    return map;
  }

  changeCurrentState(nextState) {
    this.setState({ currentState: nextState });
  }

  render() {
    let main = (
      <MainMenu
        loadGame={() => this.changeCurrentState("game")}
        loadSettings={() => this.changeCurrentState("settings")}
        loadAbout={() => this.changeCurrentState("about")}
      />
    );
    if (this.state.currentState === "game") {
      main = (
        <Game
          gameState={this.state.gameState}
          back={() => this.changeCurrentState("main")}
        />
      );
      // } else if (this.state.currentState === "settings") {
      //   main = null;
      // } else if (this.state.currentState === "about") {
      //   main = null;
    }
    return (
      <div className={css.App}>
        <Header header="Welcome to FILLER CHAMPIONSHIP" />
        {main}
        <Footer />
      </div>
    );
  }
}

export default App;
