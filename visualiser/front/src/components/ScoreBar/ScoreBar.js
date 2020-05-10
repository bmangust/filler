import React from "react";
import css from "./ScoreBar.module.css";

const ScoreBar = (props) => {
  const length = (props.value * 100) / props.maxValue;
  const style = {
    width: `${length}%`,
  };
  return (
    <div className={css.ScoreBar}>
      <div className={css.playerName}>{props.name}</div>
      <div className={css.playerScore}>
        <div className={`${css.bar} ${props.symbol}`} style={style}></div>
      </div>
    </div>
  );
};

export default ScoreBar;
