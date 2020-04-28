import React from "react";
import "./Cell.css";

const Cell = (props) => {
  let classes = ["Cell", `${props.mapSize}`];
  if (props.letter === "x") {
    classes.push("xX");
  } else if (props.letter === "o") {
    classes.push("oO");
  } else if (props.letter !== ".") {
    classes.push(props.letter);
  }
  return <li className={classes.join(" ")}></li>;
};

export default Cell;
