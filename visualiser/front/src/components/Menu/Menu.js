import React from "react";
import Score from "../Score/Score";
import css from "./Menu.module.css";

const Menu = (props) => {
  return (
    <div className={css.infoAndControls}>
      <Score players={props.players} score={props.score} />
      <div className={css.buttonWrapper}>
        <button onClick={props.play}>Play</button>
        <button onClick={props.pause}>Pause</button>
        <button onClick={props.reset}>Reset</button>
        <button className={css.stepButton} onClick={props.stepForward}>
          Step forward
        </button>
        <button className={css.stepButton} onClick={props.stepBackward}>
          Step backward
        </button>
      </div>
    </div>
  );
};

export default Menu;
