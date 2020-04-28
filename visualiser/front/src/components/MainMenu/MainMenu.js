import React from "react";
import css from "./MainMenu.module.css";

const MainMenu = (props) => {
  return (
    <div>
      <button className={css.MainMenuItem} onClick={props.loadGame}>
        Game
      </button>
      <button className={css.MainMenuItem} onClick={props.loadSettings}>
        Settings
      </button>
      <button className={css.MainMenuItem} onClick={props.loadAbout}>
        About
      </button>
    </div>
  );
};

export default MainMenu;
