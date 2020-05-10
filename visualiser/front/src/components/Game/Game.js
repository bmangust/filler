import React from "react";
import css from "./Game.module.css";
import Field from "../Field/Field";
import Menu from "../Menu/Menu";

const Game = (props) => {
  return (
    <div>
      <div className={css.flexGame}>
        <Field field={props.gameState.map} />
        <Menu
          players={props.gameState.players}
          score={props.gameState.score}
          play={props.play}
          pause={props.pause}
          stop={props.stop}
          stepForward={props.stepForward}
          stepBackward={props.stepBackward}
        />
      </div>
      <button className="navButton" onClick={props.back}>
        Back
      </button>
    </div>
  );
};

export default Game;
