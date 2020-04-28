import React from "react";
import css from "./Header.module.css";

const Header = (props) => {
  return <h1 className={css.Header}>{props.header}</h1>;
};

export default Header;
