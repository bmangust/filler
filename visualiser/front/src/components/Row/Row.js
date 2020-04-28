import React from "react";
import Cell from "../Cell/Cell";
import css from "./Row.module.css";

const Row = (props) => {
  return (
    <ul className={css.Row}>
      {props.row.split("").map((letter, index) => {
        return (
          <Cell
            letter={letter}
            mapSize={props.mapSize}
            key={`${props.rowIndex}${index}`}
          ></Cell>
        );
      })}
    </ul>
  );
};

export default Row;
