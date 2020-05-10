import React from "react";
import css from "./Score.module.css";
import ScoreBar from "../ScoreBar/ScoreBar";

const Score = (props) => {
  return (
    <div>
      <ScoreBar
        className={css.scoreWrapper}
        name={props.players[0]}
        value={props.score[1]}
        maxValue={props.score[0]}
        symbol="O"
      />
      <ScoreBar
        className={css.scoreWrapper}
        name={props.players[1]}
        value={props.score[2]}
        maxValue={props.score[0]}
        symbol="X"
      />
    </div>
  );
};

export default Score;
