import React from "react";
import Selector from "../Selector/Selector";

const Settings = (props) => {
  return (
    <div>
      <Selector
        name="player 1"
        items={props.players}
        value={props.settings.players[0]}
        onChange={props.onPlayer1Change}
      />
      <Selector
        name="player 2"
        items={props.players}
        value={props.settings.players[1]}
        onChange={props.onPlayer2Change}
      />
      <Selector
        name="map size"
        items={props.mapSizes}
        value={props.settings.mapSize}
        onChange={props.onMapChange}
      />
      <button className="navButton" onClick={props.back}>
        Back
      </button>
    </div>
  );
};

export default Settings;
