import React from "react";
import Row from "../Row/Row";
import css from "./Field.module.css";

const Field = (props) => {
  let mapSize = "c00";
  if (props.field.length > 20 && props.field.length < 50) {
    mapSize = "c01";
  } else if (props.field.length > 49) {
    mapSize = "c02";
  }
  const data = props.field.map((row, index) => {
    return <Row key={index} rowIndex={index} mapSize={mapSize} row={row}></Row>;
  });
  return <div className={css.fieldWrapper}>{data}</div>;
};

export default Field;
