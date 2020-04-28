import React from "react";
import css from "./Menu.module.css";

const Menu = (props) => {
  return (
    <div className={css.infoAndControls}>
      {/* <Score /> */}
      <button onClick={props.play}>Play</button>
      <button onClick={props.pause}>Pause</button>
      <button onClick={props.reset}>Reset</button>
      <button onClick={props.stepForward}>Step forward</button>
      <button onClick={props.stepBackward}>Step backward</button>
    </div>
  );
};

export default Menu;
