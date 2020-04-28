import React, { Fragment } from "react";
// import css from "./Game.module.css";
import Field from "../Field/Field";
import Menu from "../Menu/Menu";

const Game = (props) => {
  return (
    <div>
      <Fragment>
        <Field field={props.gameState.map} />
        <Menu />
      </Fragment>
      <button onClick={props.back}>Back</button>
    </div>
  );
};

export default Game;
